%{
#include "y.tab.h"
%}

%%

[a-zA-Z0-9()]+ {yylval.ipstr=yytext; return STR;}
. {yyerror("Invalid input");}

%%

int yywrap(){
return 1;
}
