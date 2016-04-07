#include<stdio.h>
#include<stdlib.h>
#include "symbolTable.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

char *names[] = {NULL, "rows", "columns", "map", "colon", "path_available", "door", "stone", "start", "openbracket", "closebracket", "comma", "end", "integer"}; 
int map[20][20];

int main()
{
    int nameToken, valueToken, mapToken, rows, columns, pointX, pointY,newLineToken;

    nameToken = yylex();

    while(nameToken)
    {
        printf("%d\n",nameToken);

        if(nameToken == COMMENT)
            continue;

        if(yylex() != COLON)
        {
            printf("Syntax Error in line %d, Expected a : but found %s",yylineno,yytext);
            return 0;
        }

        

        switch(nameToken)
        {
            case ROWS:
                valueToken = yylex();
                if(valueToken != INTEGER)
                {
                    printf("Syntax Error in line %d, Expected an integer but found %s",yylineno,yytext);
                    return 1;
                }
                printf("%s is set to %s\n",names[nameToken], yytext);
                rows = atoi(yytext);
                break;

            case COLUMNS:
                valueToken = yylex();
                if(valueToken != INTEGER)
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
                        valueToken = yylex();
                        printf("%d\n",valueToken);

                        switch(valueToken){
                            case PATH_AVAILABLE:
                                map[i][j] = PATH_AVAILABLE;
                                break;
                            case DOOR:
                                map[i][j] = DOOR;
                                break;
                            case STONE:
                                map[i][j] = STONE;
                                break;
                        }
                    }
                    // Read EOL
                    yylex();
                }
                break;
            
            case START:
                valueToken = yylex();
                if(valueToken == POINT)
                {
                    printf("Start is set to %s\n", yytext);
                }
                else
                {
                    printf("Syntax Error expecting Coordinate found %s",yytext);
                    return 0;

                }
                break;

            case END:
                valueToken = yylex();
                if(valueToken == POINT)
                {
                    printf("End is set to %s\n", yytext);
                }
                else
                {
                    printf("Syntax Error expecting Coordinate found %s",yytext);
                    return 0;

                }
                break;

        }
        newLineToken = yylex();

        if(newLineToken == NEWLINE || newLineToken == ENDOFFILE)
        {
            printf("%d\n",newLineToken);
            while((nameToken=yylex())==NEWLINE);
        }
        else
        {
            printf("Syntax error at line %d",yylineno);
        }

    }
}