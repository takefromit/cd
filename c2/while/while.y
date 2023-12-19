%{
#include<stdio.h>
int flag=0;
int yylex();
void yyerror();
%}

%token WHILE NUMBER ID EQL
%right '='
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%
while:WHILE '(' stmt ')' '{' body '}' ;

stmt:assign | expr ;

body: stmt ';' body | ;

assign: ID EQL expr;

expr:factor '+' factor
    |factor '-' factor
    |factor '*' factor
    |factor '/' factor
    |factor '<' factor
    |factor '>' factor
    |factor
;
factor: '('expr')'
      | NUMBER
      | ID
;
         
%%

void main()
{
 printf("Enter the statement:\n");
 yyparse();
 if(flag==0)
    printf("\n Entered expresssion is Valid \n\n");
}

void yyerror()
{
 printf("\n Entere expression is invalid \n\n");
 flag=1;
}     





