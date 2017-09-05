%{

#include "y.tab.h"
%}

%%
[0-9]+ { 
          yylval.num=atoi(yytext);
          return INT;
       }
[+*] return *yytext;
. 	
%%
int yywrap()
{
return 1;
}
