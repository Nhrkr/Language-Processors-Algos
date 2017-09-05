%{
#include "y.tab.h"
%}

%%

[a-zA-Z]+ {yylval.ipstr=yytext; return STR;}
. {yyerror("Enter characters only");}

%%

int yywrap(){
return 1;
}