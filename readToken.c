#include<stdio.h>
#include "symbolTable.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

char *names[] = {NULL, "rows", "columns", "map", "colon", "path_available", "door", "stone", "start", "openbracket", "closebracket", "comma", "end", "integer"} 

int main()
{
    int nameToken, valueToken;

    nameToken = yylex();

    while(nameToken)
    {
        if(nameToken == COMMENT)
            continue;

        if(yylex() != COLON)
        {
            printf("Syntax Error in line %d, Expected a : but found %s",yylineno,yytext);
            return 0;
        }

        valueToken = yylex()

        switch(nameToken)
        {
            case ROWS:
            case COLUMNS:
                if(valueToken != IDENTIFIER)
                {
                    printf("Syntax Error in line %d, Expected an integer but found %s",yylineno,yytext);
                    return 1;
                }
                printf("%s is set to %s\n",names[nameToken], yytext);
                break;

            case 

            case 

        }

    }
}