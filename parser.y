%{
#include "declaration.h"
%}

%union { int digit, char name, char* id }

%start EXPRESSION

%token <digit> INTEGER 
%token ROWS
%token COLUMNS
%token COLON
%token START 
%token END
%token OBSTACLE

%type <id> HURDLES, HURDLE, POINT, ASSIGNMENT

%%

EXPRESSION      :   HURDLES                 {printf(" E -> HS \n");}
                |   ASSIGNMENT              {printf(" E -> A \n");}
                ;


HURDLES         :   HURDLES HURDLE          {printf(" HS -> HS H \n")}
                |   HURDLE                  {printf("HS -> H \n")}
                ;


HURDLE          :   POINT                   {printf(" H -> P \n")}
                ;


POINT           :   '('INTEGER','INTEGER')' {printf(" P -> (i,i) \n"))}
                ;

    
ASSIGNMENT      :   START   ':' POINT       {printf(" S -> P \n")}
                |   END     ':' POINT       {printf(" E -> P \n")};
                |   ROWS    ':' INTEGER     {printf(" R -> I \n")}
                |   COLUMNS ':' INTEGER     {printf(" C -> I \n")};
                ;

%%