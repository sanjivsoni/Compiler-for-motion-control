%{

  #include<stdio.h>
  #include<stdlib.h>
  #include<string>
  #include"functions.h"
  using namespace std;

  // Stuff from flex that bison needs to know about
  extern "C" int yylex();
  extern "C" int yyparse();
  extern "C" FILE *yyin;
  extern int yylineno;



  void yyerror(const char*s);

%}

// define termminal symbols.
%token ROWS COLUMNS EQUALS START END OBSTACLE NUMBER COMMA OPAREN CPAREN

// bison gets next token from flex as 'yystype'
// Each type of token flex could return
// yacc will typedef 'yystype' as union instead of int(default)
%union
{
    int intValue;
    char charValue;
    char* stringValue;
}


// Associate each of the terminal tokens with one of union fields.
%type <stringValue> NUMBER ROWS COLUMNS START END
%type <charValue> OPAREN CPAREN COMMA

// Define the starting production
%start PARSETREE


%%
// First rule is the hishest in rule



PARSETREE           :   LINE                                      {printf("LS -> L\n");}

LINE                :   DEFINE_LIMIT ASSIGN_OBSTACLE ASSIGN_COORDINATE                 {printf("L -> AI\n");}
                    ;

DEFINE_LIMIT        :   ASSIGN_ROW ASSIGN_COLUMN
                    |   ASSIGN_COLUMN ASSIGN_ROW


ASSIGN_ROW          :   ROWS EQUALS NUMBER                       {printf("rows");rows = $3;}
                    ;

ASSIGN_COLUMN       :   COLUMNS EQUALS NUMBER                    {printf("columns");columns = $3;}
                    ;


ASSIGN_OBSTACLE     :   OBSTACLE EQUALS HINDERENCES
                    |  /* Obstacles Absent */
                    ;

HINDERENCES         :   HINDERENCES HINDERENCE                      {printf("HS -> HS H\n");}
                    |   HINDERENCE                                  {printf("HS -> H\n");}
                    ;

HINDERENCE          :   COORDINATE                                  {printf("H -> C\n");storeObstacles(coordinateX,coordinateY);}
                    ;

COORDINATE          :   OPAREN NUMBER COMMA NUMBER CPAREN           {printf("C -> (%s,%s)\n",$2,$4);coordinateX = $2; coordinateY = $4; }
                    ;

ASSIGN_COORDINATE   : ASSIGN_START ASSIGN_END
                    | ASSIGN_END ASSIGN_START
                    ;

ASSIGN_START        :  START EQUALS COORDINATE                     {printf("AC -> S=C\n");}
                    ;

ASSIGN_END          :  END EQUALS COORDINATE                       {printf("AC -> E=C\n");}
                    ;

%%

void yyerror(const char* s)
{
    printf("\nParse Error in line %d Message: %s\n",yylineno,s);
}

int main(int argc, char**argv)
{

    if(argc != 2)
    {
        printf("\nIncorrect usage. Try ./a.out filename\n");
        exit(0);
    }

    FILE* file = fopen(argv[1],"r");
    if(file == NULL)
    {
        printf("Cannot open %s \n",argv[1]);
        exit(0);
    }

    yyin = file;

    do{
        yyparse();
    }while(!feof((yyin)));

    printf("\nNo. of lines are %d", yylineno);
    createSparse();
    displayMatrix();

    fclose(file);
}
