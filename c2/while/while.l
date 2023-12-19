%{
#include "y.tab.h"
%}

%%
while WHILE ;
[0-9]+ NUMBER;
[a-zA-Z_][a-zA-Z_0-9]* ID;
. *yytext;
\n return 0;
%%

int yywrap(){
return 0;
}
