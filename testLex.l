%{

#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
#define YY_DECL extern "C" int yylex()

#include "testParser.tab.h"
%}

%%
=                       return EQUALS;
rows                    return ROWS;
columns               return COLUMNS;
obstacle              return OBSTACLE;
start                 return START;
end                   return END;


[0-9]+                  {
                            yylval.stringValue = strdup(yytext);
                            return NUMBER;
                        }

\(                     {
                            yylval.charValue = '(';
                            return LBRACKET;
                        }

\)                      {
                            yylval.charValue = '(';
                            return RBRACKET;
                        }

,                       {
                            yylval.charValue = ',';
                            return COMMA;
                        }

\n                      {
                          yylineno++;
                        }

[ \t]                 ;
.                       {    printf("Syntax error : Unexpected char \n");
                             exit(0);
                        }


%%
void yyerror(char *str)
{
    printf("Parse Error: \n%s\n",str);
}

int yywrap(void)
{
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
