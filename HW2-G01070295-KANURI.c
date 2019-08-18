/*G010170295  Deepak Kanuri       CS-531         Assignment-2 Tuesday's class*/
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>


typedef void (*sighandler_t)(int);/*typedef'ing the return value of signal as sighandler_t*/


void SIGHND(int sno)/*signal handler for SIGQUIT signal*/
{
 if(sno==SIGQUIT)
  printf("received SIGQUIT signal\n");
}

int cs531_system(char *s)/*Our user-defined system function*/
{
 int status,pid,w,tty;
 sighandler_t i,q;

 char *progname;

 fflush(stdout);/*clearing the buffer of the output*/
 tty=open("/dev/tty",2);/*opening the control terminal*/
 if(tty==-1)
 {
  fprintf(stderr,"%s cant open/dev/tty\n",progname);
  return -1;
 }

 //if(signal(SIGQUIT,SIGHND)==SIG_ERR)
   //printf("CAN NOT CATCH sigquit SIGNAL\n");

 


 if((pid=fork())==0)/*creating child and in child process*/
 {
  
  close(0);dup(tty);/*closing the standard input and duping it to the control terminal */
  close(1);dup(tty);/*closing the standard output and duping it to the control terminal */
  close(2);dup(tty);/*closing the standard error and duping it to the control terminal */
  close(tty);
  
  execlp("sh","sh","-c",s,(char*)0);/*executing the command given in command prompt*/
  exit(127);
 }
 close(tty);
  i=(sighandler_t)signal(SIGINT,SIG_IGN);/*ignoring the SIGINT signal and catching its state in 'i'*/ 
  q=(sighandler_t)signal(SIGQUIT,SIG_IGN);/*ignoring the SIGQUIT signal and catching its state in 'q'*/
 while((w=wait(&status))!=pid&&w!=-1);/*parent waiting for the child to finish*/
 
if(signal(SIGQUIT,SIGHND)==SIG_ERR)/*handling the signal SIGQUIT*/
   printf("CAN NOT CATCH sigquit SIGNAL\n");
 
 sleep(10);/*making the parent wait for 10 seconds*/
 
 

 if(WIFEXITED(status))/*catching the exited status*/
  printf("exited,status=%d\n",WEXITSTATUS(status));

 else if(WIFSIGNALED(status))/*acknowledging the SIGKILL command*/
  printf("killed by signal %d\n",WTERMSIG(status));
 
 else if(WIFSTOPPED(status))/*acknowledging the SIGQUIT command*/
   printf("stopped by signal %d\n",WSTOPSIG(status));

 else if(WIFCONTINUED(status))
   printf("continued\n");
  
 if(w==-1)
   status=-1; 

  signal(SIGINT,i);/*reinstating the previous SIGINT status*/ 
  signal(SIGQUIT,q);/*reinstating the previous SIGQUIT status*/
    
  return status;/*returning the status of our user-defined system function*/ 
}

int main(int argc,char * argv[])
{
 int status;
 status=cs531_system(argv[1]);
 return status;
}

