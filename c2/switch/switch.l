%{
#include "y.tab.h"
%}

%%
[ \t\n]        /* Skip whitespaces */

"switch"        return SWITCH;
"case"          return CASE;
"break"         return BREAK;
"default"       return DEFAULT;
[0-9]+          return NUM;
[a-zA-Z][a-zA-Z0-9]*    return ID;
"<="            return LE;
">="            return GE;
"=="            return EQ;
"!="            return NE;
"||"            return OR;
"&&"            return AND;
.               return yytext[0];
%%

int yywrap() {
    return 1;
}
