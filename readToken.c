#include<stdio.h>
#include "symbolTable.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

char *names[] = {NULL, "rows", "columns", "map", "colon", "path_available", "door", "stone", "start", "openbracket", "closebracket", "comma", "end", "integer"} 
int map[20][20];

int main()
{
    int nameToken, valueToken, mapToken, rows, columns;

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
                if(valueToken != IDENTIFIER)
                {
                    printf("Syntax Error in line %d, Expected an integer but found %s",yylineno,yytext);
                    return 1;
                }
                printf("%s is set to %s\n",names[nameToken], yytext);
                rows = atoi(yytext);
                break;

            case COLUMNS:
                if(valueToken != IDENTIFIER)
                {
                    printf("Syntax Error in line %d, Expected an integer but found %s",yylineno,yytext);
                    return 1;
                }
                printf("%s is set to %s\n",names[nameToken], yytext);
                columns = atoi(yytext);
                break;

            case MAP:
                for(int i = 0; i < rows; i++)
                {
                    for(int j = 0; j < columns; j++)
                    {
                        
                        case CLEAR:
                            map[i][j] = CLEAR;
                        case DOOR:
                            map[i][j] = DOOR;
                        case STONE:
                            map[i][j] = STONE;
                        mapToken = yylex()
                    }
                }
            
            case START:
                if(valueToken == POINT)
                {
                    char point[10];
                    point = yylex()
                }
                else
                {
                    printf("Start is set to %s\n", point);
                    return 0;

                }

            case END:
                if(valueToken == POINT)
                {
                    char point[10];
                    point = yylex() 
                }
                else
                {
                    printf("Start is set to %s\n", point);
                    return 0;
                }

        }
        nameToken = yylex();
    }
}