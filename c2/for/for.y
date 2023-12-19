%{
    #include<stdio.h>
    int flag=0;
    int yylex();
    void yyerror();
%}

%token NUMBER FOR ID TYPE INC DEC
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%
for : FOR'('stmt';'stmt';'stmt')''{'body'}';
stmt: TYPE' 'assign | assign | expr |;
assign: ID'='expr;
body: stmt';'body | ;


expr : factor'+'factor
     | factor'-'factor
     | factor'*'factor
     | factor'/'factor
     | factor'<'factor
     | factor'>'factor
     | factor INC
     | factor DEC
     | factor
     ;



factor : '('expr')' 
       | NUMBER
       | ID
       ;


%%

void main()

{
    printf("\n ----> Tom George CS7B Roll 59 <----\n");
    printf("\nEnter for statement :\n");
    yyparse();
    if(flag==0)
        printf("\nEntered expression is Valid\n\n");
}

void yyerror()

{
    printf("\nEntered expression is Invalid\n\n");
    flag=1;

}
