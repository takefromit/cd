%{
#include <stdio.h>
#include <string.h>
%}

%%
^.*tomg.* {
    
    printf("Contains first 4 characters of name as substring\n");
}

.* {
    printf("Doesn't contain first 4 characters of name as substring: %s\n", yytext);
}
%%

int yywrap() {}
int main() {
    printf("Tom George C7B Roll no 59\n");
    printf("Enter strings:\n");
    yylex();

    return 0;
}
