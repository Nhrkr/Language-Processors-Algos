%{
    #include <stdio.h>

    int vowels = 0, consonants = 0;
%}

%%
[aeiouAEIOU]       vowels++;
[a-zA-Z]   consonants++;
.|\n        /* Do nothing */
%%

int main()
{
	
    printf("Getting the string from file\n");
   yyin=fopen("ip1.txt", "r");
    yylex();
    printf("Number of vowels: %d\n", vowels);
    printf("Number of consonants: %d\n", consonants);
    fclose(yyin);
    return 0;
}

int yywrap()
{
return 1;
}
