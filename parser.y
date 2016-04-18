%{

  #include<stdio.h>
  #include<stdlib.h>
  #include<string>
  #include<vector>
  #include<time.h>
  using namespace std;

  #include "maze.cpp"

  // Stuff from flex that bison needs to know about
  extern "C" int yylex();
  extern "C" int yyparse();
  extern "C" FILE *yyin;
  extern int yylineno;

  void yyerror(const char*s);

  int rows, columns;
  int startX, startY, endX, endY;
  vector<int> obstacleX;
  vector<int> obstacleY;
  int x = 0, y = 0;

%}

// define termminal symbols.
%token ROWS COLUMNS EQUALS START END OBSTACLES NUMBER COMMA OPAREN CPAREN

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
// Precedence is Top to Bottom High to low.

PARSETREE           :   LINE
                    ;

LINE                :   DEFINE_LIMIT ASSIGN_OBSTACLES ASSIGN_COORDINATE
                    ;

DEFINE_LIMIT        :   ASSIGN_ROW ASSIGN_COLUMN
                    |   ASSIGN_COLUMN ASSIGN_ROW
;


ASSIGN_ROW          :   ROWS EQUALS NUMBER
                        {rows = atoi($3);}
                    ;

ASSIGN_COLUMN       :   COLUMNS EQUALS NUMBER
                        {columns = atoi($3);}
                    ;


ASSIGN_OBSTACLES     :   OBSTACLES EQUALS HINDERANCES
                    |  /* Obstacles Absent */
                    ;

HINDERANCES         :   HINDERANCES HINDERANCE

                    |   HINDERANCE
                    ;

HINDERANCE          :   COORDINATE
                        {
                            obstacleX.push_back(x);
                            obstacleY.push_back(y);
                        }
                    ;

COORDINATE          :   OPAREN NUMBER COMMA NUMBER CPAREN
                        {
                            x = atoi($2);
                            y = atoi($4);
                        }
                    ;

ASSIGN_COORDINATE   :   ASSIGN_START ASSIGN_END
                    |   ASSIGN_END ASSIGN_START
                    ;

ASSIGN_START        :   START EQUALS COORDINATE
                        {
                            startX = x;
                            startY = y;
                        }
                    ;

ASSIGN_END          :   END EQUALS COORDINATE
                        {
                            endX = x;
                            endY = y;
                        }
                    ;

%%

void yyerror(const char* s)
{
    printf("\nParse Error in line %d Message: %s\n",yylineno,s);
    exit(0);
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

    clock_t time = clock();

    Maze maze = Maze(rows, columns);
    maze.setObstacleFromVector(obstacleX, obstacleY);
    maze.setStartPoint(startX, startY);
    maze.setEndPoint(endX, endY);

    maze.traverseBreadthFirst();

    time = clock() - time;
    printf("\nRunning Time = %fs\n",((float)time)/CLOCKS_PER_SEC);
    printf("\nLines of Code = %d\n", yylineno);

    fclose(file);
}
