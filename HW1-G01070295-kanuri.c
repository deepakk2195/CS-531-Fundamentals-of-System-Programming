/*CS-531 homework-1 Deepak Kanuri  G01070295*/
#include<stdio.h>
#include<string.h>
int check(char str[10][26],char buf[26], int k)/*This function checks the presently entered string with the previous strings for duplicates.*/
{
 int i,cmp;
 for(i=0;i<k;i++)
 {
  cmp=strcmp(str[i],buf);
  if(cmp==0)
   return 0;
 }
 return 1;
}
void printing(char str[10][26])/*This function prints the strings in ascending or descending order and tells which has higher and lower ASCII values*/
{
 char ch,choice[10];int i;
 printf("\nEnter 'A' to print strings in ascending order or 'D' for descending order");
 dk:fgets(choice,sizeof(choice),stdin);
    if(strncmp(choice,"A",1)==0)
     ch='A';
    else if(strncmp(choice,"D",1)==0)
     ch='D';
    else
    {
     printf("\nplease enter only 'A' or 'D'");
     goto dk;
    }
 switch(ch)
 {
   case 'A':for(i=0;i<10;i++)
             printf("\n%s",str[i]);
            break;
   case 'D':for(i=9;i>=0;i--)
             printf("\n%s",str[i]);
            break;
   default:printf("\nplease enter 'A' or 'D'");
           goto dk; 
 }
 printf("\nThe string with lowest ASCII value is %s\n and string with highest ASCII value is %s \n",str[0],str[9]);
}
int main(void)
{
 char st[10][26],buff[100];
 int i,j,cmp;
 printf("\nEnter 10 character strings:");
 for(i=0;i<10;i++)
 {
   printf("\nenter a string of max size 25 %d:",i);
   fgets(buff,sizeof(buff),stdin);
   if(strlen(buff)<27&&strlen(buff)>1)/*checking if the entered string is between the size of 1 and 25*/
   {
     for(j=0;j<strlen(buff);j++)
      if(buff[j]<127&&buff[j]>32)/*checking if the entered characters is readable*/
      {
        cmp=1;
        break;
      }
      if(cmp)
         if(check(st,buff,i))/*checking for duplicate stings*/
           strcpy(st[i],buff);
         else
         {
           printf("\nERROR-Duplicate string-Please reenter");
           i--;
         }
      else
      {
       printf("ERROR-readable characters-Please Reenter");
       i--;
      }
   }
   else
   {
    printf("ERROR-size of string should be between 1 and 25-Please Reenter");
    i--;
   } 
}
for(i=0;i<9;i++)/*bubble sort the string*/
 {
  for(j=i+1;j<10;j++)
   {
     cmp=strcmp(st[i],st[j]);memset(buff,0,sizeof(buff));
   if(cmp>0)
    {
      strcpy(buff,st[i]);
      strcpy(st[i],st[j]);
      strcpy(st[j],buff);
    }
   }
 }
   printing(st);
}
