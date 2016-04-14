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
  int matrix[20][20];
  char *rows, *columns;

  void createSparse(char* i,char* j);

  void yyerror(const char*s);

%}

// define termminal symbols.
%token ROWS COLUMNS EQUALS START END OBSTACLE NUMBER COORDINATE LBRACKET RBRACKET COMMA

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
%type <stringValue>  NUMBER COORDINATE ROWS COLUMNS START END
%type <charValue> LBRACKET RBRACKET COMMA


// Define the starting production
%start PARSETREE


%%
// First rule is the hishest level rule


PARSETREE           :   LINES                                       {printf("P -> LS");}
                    ;

LINES               :   LINES LINE                                  {printf("LS -> LS L\n");}
                    |   LINE                                        {printf("LS -> L\n");};

LINE                :   ASSIGN_INT                                  {printf("L -> AI\n");}
                    |   ASSIGN_COORDINATE                           {printf("L -> AC\n");}
                    |   ASSIGN_OBSTACLE                             {printf("L -> AO\n");}
                    ;

ASSIGN_INT          :   ROWS EQUALS NUMBER                          {printf("AI -> R=N %s  %s \n",$1,$3);rows=$3;}
                    |   COLUMNS EQUALS NUMBER                       {printf("AI -> C=N\n");columns=$3;}
                    ;

ASSIGN_COORDINATE   :   START EQUALS HINDERENCE             {printf("AC -> S=C\n");}
                    |   END EQUALS HINDERENCE                    {printf("AC -> E=C\n");}
                    ;

ASSIGN_OBSTACLE     :   OBSTACLE EQUALS HINDERENCES                 {printf("AO -> O=HS\n");}
                    ;

HINDERENCES         :   HINDERENCES HINDERENCE                      {printf("HS -> HS H\n");}
                    |   HINDERENCE                                  {printf("HS -> H\n");};

HINDERENCE          :  LBRACKET NUMBER COMMA NUMBER RBRACKET                          {printf("H -> C\n");createSparse($2,$4);};



%%
void createSparse(char* rowNo,char* colNO)
{

  int i,j;
  int row = atoi(rowNo);
  int column = atoi(colNO);
  //printf("r = %d, c=%d",r,c);
  for(i=0;i<20;++i)
  {
    for(j=0;j<20;++j)
    {
      if(i==row && j==column)
        matrix[i][j] = 1;
    }
  }

}

void createEmptyMatrix()
{
    int i,j;

    for(i=0;i<20;++i)
    {
      for(j=0;j<20;++j)
        {
          matrix[i][j] = 0;
        }
    }
}


void displayMatrix()
{
  int i,j;
  printf("\nThe matrix is");
  for(i=0;i<20;++i)
  {
    printf("\n");
    for(j=0;j<20;++j)
      {
        printf("%d\t",matrix[i][j]);
      }
  }
}


void yyerror(const char* s)
{
    printf("Parse Error Message: %s\n",s);
}

int main(int argc, char**argv)
{
    createEmptyMatrix();              //This function initialises matrix with 0
    if(argc != 2)
    {
        printf("Incorrect usage. Try ./a.out filename\n");
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
    displayMatrix();


    fclose(file);
}
