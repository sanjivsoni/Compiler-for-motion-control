%{
#include "declaration.h"
%}

%union {    int digit;
            char name;
            char* id;
        }

%start EXPRESSION

%token <digit> INTEGER 
%token ROWS
%token COLUMNS
%token COLON
%token START 
%token END
%token OBSTACLE
%token COMMENT
%token ERROR
%token POINT

%type <id> HURDLES, HURDLE, ASSIGNMENT

%%

EXPRESSION      :   HURDLES                 {printf(" E -> HS \n");}
                |   ASSIGNMENT              {printf(" E -> A \n");}
                ;


HURDLES         :   HURDLES HURDLE          {printf(" HS -> HS H \n")}
                |   HURDLE                  {printf("HS -> H \n")}
                ;


HURDLE          :   POINT                   {printf(" H -> P \n")}
                ;

    
ASSIGNMENT      :   START   ':' POINT       {printf(" S -> P \n")}
                |   END     ':' POINT       {printf(" E -> P \n")};
                |   ROWS    ':' INTEGER     {printf(" R -> I \n")}
                |   COLUMNS ':' INTEGER     {printf(" C -> I \n")};
                ;

%%