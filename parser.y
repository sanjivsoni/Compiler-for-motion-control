%{
#include "declaration.h"
#include<stdio.h>
int yylex();
void yyerror(char *s);
extern yylineno;
%}

%union {    int digit;
            char name;
            char* id;
        }

%start ASSIGNMENT

%token <digit> INTEGER
%token ROWS
%token COLUMNS
%token COLON
%token START
%token END
%token OBSTACLE
%token COMMENT
%token ERROR
%token<id> POINT


%type <id> HURDLES HURDLE ASSIGNMENT

%%

ASSIGNMENT      :   INTEGER     {printf(" R -> I \n");}
                ;

%%

int main(void)
{
    return yyparse();
}
void yyerror(char *s)
{
  fprintf(stderr, "line %d: %s\n", yylineno, s);
}
