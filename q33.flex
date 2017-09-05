%{
#include<stdio.h>
int spechar=0,a=0,b=0,c=0,d=0;
%}

%%

[a-zA-Z] {a++;}
[ ] {b++;}
\n {c++;}
\t {d++;}
. {spechar++; ECHO;}

%%

yywrap(){
return 1;
}

main(){
yyin=fopen("ip3.txt","r");
yylex();
if(spechar!=0)
	printf("\nSpecial characters are present in the string\n");
else
	printf("No special characters are present in the string\n");
printf("%d %d %d %d no. of special characters= %d",a,b,c,d,spechar);
}
