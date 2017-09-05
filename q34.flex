%{
    #include <stdio.h>
    #include<string.h>
%}

/* cannot use space inside {} as {3,_5} */

%%
[a-zA-Z]+   {if(yyleng>=3 && yyleng <=5) printf("%s\n",yytext);printf("Strind between 3-5 chars");}
.|\n        /* do nothing */
%%

int main()
{
	 yyin=fopen("ip4.txt", "r");
    yylex();
    fclose(yyin);
    return 0;
}
int yywrap()
{
return 1;
}
