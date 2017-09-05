%{
#include<stdio.h>
#include<string.h>
void yyerror(char *err);

int bcount=0,i=0,len;
%}

%union{
char *ipstr;
}

%start line

%token <ipstr> STR

%type <ipstr> exp


%%

line : exp 	{
				len=strlen($1);
				while(i<len && bcount>=0)
				{
					if($1[i]=='(')
						bcount++;
					else if($1[i]==')')
						bcount--;
					i++;
				}
				if(bcount==0)
					printf("%s is balanced string\n",$1);
				else
					printf("%s is not a balanced string\nunmatched parentheses= %d",$1,bcount);
			}
	  ;
exp   : STR {
				$$=$1;
			}
	  ;
			
%%

void yyerror(char *err)
{
	printf("%s\n",err);
}

main()
{
	yyparse();
}