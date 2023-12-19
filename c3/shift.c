#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char input[100];
char stack[100];
int top=0;
int len=0;

void print_details(int,char[]);
void checkForReduction(int);
void main()
{ int i=0;
  printf("Enter the string to be reduced\n");
  scanf("%s",input);
  len=strlen(input);
  printf("Stack\t\tInput\t\tAction\n");
  for(i=0;i<len;i++)
    {
      print_details(i,"Shift");
      stack[top]=input[i];
      checkForReduction(i);
      top++;
    }
  top--;
  if(top==0 && stack[0]=='S')
  {
    printf("String is accepted\n");
  }
 else{
   printf("String regected\n");
 }
  
}
void checkForReduction(int i)
{
  int flag=1;
  while(flag)
    {
      flag=0;
      if(top >= 2 && stack[top-2]=='S' && stack[top-1]=='+' && stack[top]=='S')
      {
        print_details(i+1,"Reduced");
        stack[top-2]='S';
        top=top-2;
        flag=1;
      }
      else if( top >= 2 && stack[top-2]=='S' && stack[top-1]=='-' && stack[top]=='S')
      {
        print_details(i+1,"Reduced");
        stack[top-2]='S';
        top=top-2;
        flag=1;
      }
      else if(top >= 2 && stack[top-2]=='(' && stack[top-1]=='S' && stack[top]==')')
      {
        print_details(i+1,"Reduced");
        stack[top-2]='S';
        top=top-2;
        flag=1;
        
      }
      else if(stack[top]=='i'){
        print_details(i+1,"Reduce");
        stack[top]='S';
        flag=1;
      }
      
    }
  
}

void print_details(int i,char action[])
{
  for(int j=0;j<=top;j++)
    {
      printf("%c",stack[j]);
    }
  printf("\t\t");
  for(int k=i;k<len;k++)
    {
      printf("%c",input[k]);
    
    }
  printf("\t\t");
  printf("%s",action);
  printf("\n");
}