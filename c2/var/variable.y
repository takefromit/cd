%{

    #include<stdio.h>
    int valid=1;

%}

%token digit letter

%%

start : letter alphanum
alphanum :     letter alphanum | digit alphanum | ;

%%

int yyerror()

{
    printf("\nIts not a identifier!\n");
    valid=0;
    return 0;

}

int main()

{
    printf("\nTom George cs7B 59");
    printf("\nEnter the variable to check:\n ");
    yyparse();
    if(valid)
    {
        printf("\nIt is a identifier!\n");
    }

}


