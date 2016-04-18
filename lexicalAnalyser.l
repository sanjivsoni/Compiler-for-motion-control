%{

#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;

// Take tokens from parser.tab.h
#define YY_DECL extern "C" int yylex()
#include "parser.tab.h"

%}

%%
=           return EQUALS;
rows        return ROWS;
columns     return COLUMNS;
obstacles   return OBSTACLES;
start       return START;
end         return END;

[-]?[0-9]+      {
                yylval.stringValue = strdup(yytext);
                return NUMBER;
            }

\(          {
                yylval.charValue = '(';
                return OPAREN;
            }

\)          {
                yylval.charValue = ')';
                return CPAREN;
            }
,           {
                yylval.charValue = ',';
                return COMMA;
            }

\n*\Z       {
                 printf("\nError: Blank Input File");
                 exit(0);
            }

\n          {
                yylineno++;
            }

[ \t]       ;

.           {    printf("\nSyntax error in line %d : Unexpected char %s \n",yylineno,yytext);
                 exit(0);
            }


%%
void yyerror(char *str)
{
    printf("Parse Error: \n%s\n",str);
}

int yywrap(void) {
    return 1;
}

/*
int main(void)
{
    int token;
    while ((token = yylex()) != 0)
        printf("Token: %d (%s)\n", token, yytext);
    return 0;
}
*/
