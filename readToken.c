#include<stdio.h>
#include<stdlib.h>
#include "symbolTable.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

char *names[] = {NULL, "rows", "columns", "map", "colon", "path_available", "door", "stone", "start", "openbracket", "closebracket", "comma", "end", "integer"}; 
int map[20][20];

void printTokens(int token)
{
    if(token == ROWS)
        printf("rows\n");
    else if(token == COLUMNS)
        printf("columns\n");
    else if(token == MAP)
        printf("map\n");
    else if(token == COLON)
        printf("colon\n");
    else if(token == PATH_AVAILABLE)
        printf("path_available\n");
    else if(token == DOOR)
        printf("door\n");
    else if(token == STONE)
        printf("stone\n");
    else if(token == START)
        printf("start\n");
    else if(token == OPENBRACKET)
        printf("(\n");
    else if(token == CLOSEBRACKET)
        printf(")\n");
    else if(token == END)
        printf("end\n");
    else if(token == INTEGER)
        printf("int\n");
    else
        printf("Unknown Token found\n");
}

int foundCommentToken(int token)
{
    if(token == COMMENT)
        return 1;
    else
        return 0;
}

int foundColonToken(int token)
{
    if(token == COLON)
    {
        return 1;
    }
    else
    {
        printf("Syntax Error in line %d, Expected a : but found %s",yylineno,yytext);
        return 0;
    }
}

int getRowTokenValue(int token)
{
    if(token != INTEGER)
    {
        printf("Syntax Error in line %d, Expected an integer but found %s",yylineno,yytext);
        return -1;
    }
    else
    {
        printf("%s : %s\n",names[token], yytext);
        return(atoi(yytext));
    }
}

int getColumnTokenValue(int token)
{
    if(token != INTEGER)
    {
        printf("Syntax Error in line %d, Expected an integer but found %s",yylineno,yytext);
        return -1;
    }
    else
    {
        printf("%s : %s\n",names[token], yytext);
        return(atoi(yytext));
    }
}

int setMapTokens(int i, int j, int value)
{
    if(value == PATH_AVAILABLE)
    {
        map[i][j] = PATH_AVAILABLE;
        return 1;
    }
    else if(value == DOOR)
    {
        map[i][j] = DOOR;
        return 1;
    }
    else if(value == STONE)
    {
        map[i][j] = STONE;
        return 1;
    }
    else
    {
        printf("Syntax Error in line %d, not expected map value %s",yylineno,yytext);
        return 0;
    }
    return 1;
}

int readMapTokens(int rows, int columns)
{
    int i = 0, j = 0, valueToken;

    for(i = 0; i < rows ; i++)
    {
        for(j = 0; j < columns; j++)
        {
            valueToken = yylex();
            if(!setMapTokens(i,j,valueToken))
                return -1;
        }
        if(yylex() != NEWLINE)
        {
            printf("Syntax Error line %d, expecting \n found %s",yylineno,yytext);
            return -1;
        }
    }
    return 1;
}

int foundStartToken(int token, int type)
{
    if(token == POINT && type == START)
    {
        printf("Start : %s\n", yytext);
    }
    else if(token == POINT && type == END)
    {
        printf("End : %s\n", yytext);
    }

    else
    {
        printf("Syntax Error expecting Coordinate found %s",yytext);
        return 0;

    }
    return 1;
}

int readTokens()
{
    int nameToken, valueToken, mapToken, rows, columns, pointX, pointY,newLineToken;

    nameToken = yylex();

    while(nameToken)
    {
        printTokens(nameToken);

        valueToken = yylex();

        if(foundCommentToken(valueToken))
            continue;

        if(!foundColonToken(valueToken))
            break;

        switch(nameToken)
        {
            case ROWS:
                valueToken = yylex();
                if((rows = getRowTokenValue(valueToken)) == -1)
                    break;
                //printf("rows : %d\n",rows);
                break;

            case COLUMNS:
                valueToken = yylex();
                if((columns = getRowTokenValue(valueToken)) == -1)
                    break;
                //printf("columns : %d\n",rows);
                break;

            case MAP:
                readMapTokens(rows,columns);
                break;
            
            case START:
                valueToken = yylex();
                if(!foundStartToken(valueToken, START))
                    break;
                break;

            case END:
                valueToken = yylex();
                if(!foundStartToken(valueToken, END))
                    break;
                break;
        
        }

        newLineToken = yylex();

        if(newLineToken == NEWLINE || newLineToken == ENDOFFILE)
        {
            //printf("%d\n",newLineToken);
            while((nameToken=yylex())==NEWLINE);
        }
        else
        {
            printf("Syntax error at line %d",yylineno);
        }

    }
    return 1;

}

int main()
{
    readTokens();
    
}