%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//extern int yylex();
void yyerror(char *err);

int i,flag=0,len;
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
				for(i=0;i<len/2&&flag==0;i++)
				{
					if($1[i]!=$1[len-i-1])
						flag=1;
				}
				if(flag==0)
					printf("\n%s is palindrome\n",$1);
				else
					printf("\n%s is not a palindrome\n",$1);

			}
	  ;
exp   : STR {
				$$=$1;
			}
	  ;

%%

void yyerror(char * err)
{
	fprintf(stderr,"%s\n",err);
	exit(1);	
}

main()
{
	yyparse();
}