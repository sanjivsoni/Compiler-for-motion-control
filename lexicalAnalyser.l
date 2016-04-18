%{

#include<stdio.h>
#include<string>
#include<iostream>

#define LKNRM  "\x1B[0m"
#define LKRED  "\x1B[31m"
#define LKGRN  "\x1B[32m"
#define LKYEL  "\x1B[33m"
#define LKBLU  "\x1B[34m"
#define LKMAG  "\x1B[35m"
#define LKCYN  "\x1B[36m"
#define LKWHT  "\x1B[37m"

using namespace std;

// Take tokens from parser.tab.h
#define YY_DECL extern "C" int yylex()
#include "parser.tab.h"

void yyerror( char* s);

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

\n          {
                yylineno++;
            }

[ \t]       ;

.           {
                yyerror("Unexpected char");
            }


%%
void yyerror( char* s)
{
    printf("\n%sSyntax Error%s : Line %s%d%s.\n%sMessage:%s %s '%s'.\n",LKRED,LKWHT,LKBLU,yylineno,LKWHT,LKRED,LKYEL,s,yytext);
    exit(0);
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
