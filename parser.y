%{


  #include<stdio.h>
  #include<stdlib.h>
  #include<string>
  using namespace std;

  // Stuff from flex that bison needs to know about
  extern "C" int yylex();
  extern "C" int yyparse();
  extern "C" FILE *yyin;
  extern int yylineno;

  void yyerror(const char*s);

%}

// define termminal symbols.
%token ROWS COLUMNS EQUALS START END OBSTACLE NUMBER COORDINATE

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
%type <stringValue> NUMBER COORDINATE ROWS COLUMNS START END

// Define the starting production
%start PARSETREE


%%
// First rule is the hishest level rule


PARSETREE           :   LINES                                       {printf("P -> LS");}
                    ;

LINES               :   LINES LINE                                  {printf("LS -> LS L\n");}
                    |   LINE                                        {printf("LS -> L\n");}

LINE                :   ASSIGN_INT                                  {printf("L -> AI\n");}
                    |   ASSIGN_COORDINATE                           {printf("L -> AC\n");}
                    |   ASSIGN_OBSTACLE                             {printf("L -> AO\n");}
                    ;

ASSIGN_INT          :   ROWS EQUALS NUMBER                          {printf("AI -> R=N %s  %s \n",$1,$3);}
                    |   COLUMNS EQUALS NUMBER                       {printf("AI -> C=N\n");}
                    ;

ASSIGN_COORDINATE   :   START EQUALS COORDINATE                     {printf("AC -> S=C\n");}
                    |   END EQUALS COORDINATE                       {printf("AC -> E=C\n");}
                    ;

ASSIGN_OBSTACLE     :   OBSTACLE EQUALS HINDERENCES                 {printf("AO -> O=HS\n");}
                    ;

HINDERENCES         :   HINDERENCES HINDERENCE                      {printf("HS -> HS H\n");}
                    |   HINDERENCE                                  {printf("HS -> H\n");}

HINDERENCE          :   COORDINATE                                  {printf("H -> C\n");}



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

    fclose(file);
}
