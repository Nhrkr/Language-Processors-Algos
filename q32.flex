%{
    #include <stdio.h>

    int positive = 0;
    int negative = 0;
    int positive_fraction = 0;
    int negative_fraction = 0;
%}

%%
[0-9]+   positive++;
-[0-9]+   negative++;
[0-9]+\.[0-9]+ positive_fraction++;
-[0-9]+\.[0-9]+ negative_fraction++;
.|\n                /* do nothing */
%%

int main()
{
	 yyin=fopen("ip2.txt", "r");
    yylex();
    printf("Number of positive integers: %d\n", positive);
    printf("Number of negative integers: %d\n", negative);
    printf("Number of positive fractions: %d\n", positive_fraction);
    printf("Number of negative fractions: %d\n", negative_fraction);
    fclose(yyin);
    return 0;
}

int yywrap()
{
return 1;
}
