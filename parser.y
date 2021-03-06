%{

  #pragma once
  #include<stdio.h>
  #include<stdlib.h>
  #include<string>
  #include<vector>
  #include<time.h>

  using namespace std;

  #define KNRM  "\x1B[0m"
  #define KRED  "\x1B[31m"
  #define KGRN  "\x1B[32m"
  #define KYEL  "\x1B[33m"
  #define KBLU  "\x1B[34m"
  #define KMAG  "\x1B[35m"
  #define KCYN  "\x1B[36m"
  #define KWHT  "\x1B[37m"

  #include "maze.cpp"

  // Stuff from flex that bison needs to know about
  extern "C" int yylex();
  extern "C" int yyparse();
  extern "C" FILE *yyin;
  extern int yylineno;

  void yySemanticError(const char*s);
  void yyerror(const char*s);
  void yywarning(const char* s);

  int rows = -1, columns = -1;
  int startX = -1, startY = -1, endX = -1, endY = -1;
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

LINE                :   DEFINE_LIMIT ASSIGN_COORDINATE ASSIGN_OBSTACLES
                        {
                            printf("%sSuccessful Parsing\n%s",KGRN,KWHT);
                        }

                    ;

DEFINE_LIMIT        :   ASSIGN_ROW ASSIGN_COLUMN
                    |   ASSIGN_COLUMN ASSIGN_ROW

                    ;


ASSIGN_ROW          :   ROWS EQUALS NUMBER
                        {
                            rows = atoi($3);
                            if(rows <= 0 )
                            {
                                yySemanticError("Invalid Row value. Expected positive value.");
                            }
                        }
                    ;

ASSIGN_COLUMN       :   COLUMNS EQUALS NUMBER
                        {
                            columns = atoi($3);
                            if(columns <= 0 )
                            {
                                yySemanticError(" Invalid Column value. Expected positive value.");
                            }
                        }
                    ;


ASSIGN_OBSTACLES    :   OBSTACLES EQUALS HINDERANCES
                    |  /* Obstacles Absent (Ebsilon Production) */
                    ;

HINDERANCES         :   HINDERANCES HINDERANCE

                    |   HINDERANCE
                    ;

HINDERANCE          :   COORDINATE
                        {
                            if( x > rows || y > columns )
                            {
                                yySemanticError(" Obstacle Coordinate out of bounds.");
                            }

                            if( x == startX && y == startY )
                            {
                                yySemanticError("Obstacle Coordinate can't be same as Start.");
                            }
                            if( x == endX && y == endY )
                            {
                                yySemanticError("Obstacle Coordinate can't be same as End.");
                            }
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
                            if( x > rows || y > columns )
                            {
                                yySemanticError(" Start Coordinate out of bounds");
                            }
                            
                            startX = x;
                            startY = y;
                            
                            if( startX == endX && startY == endY )
                            {
                                yySemanticError(" Start Coordinate can't be same as End.");
                            }
                        }
                    ;

ASSIGN_END          :   END EQUALS COORDINATE
                        {
                            if( x > rows || y > columns )
                            {
                                yySemanticError("End Coordinate out of bounds");

                            }
                            
                            endX = x;
                            endY = y;
                            
                            if( startX == endX && startY == endY )
                            {
                                yySemanticError(" End Coordinate can't be same as start.");
                            }
                        }
                    ;

%%

void yySemanticError(const char* s)
{
    printf("\n%sSemantic Error%s : Line %s%d%s.\n%sMessage:%s %s\n",KRED,KWHT,KBLU,yylineno,KWHT,KRED,KGRN,s);
    exit(0);
}

void yyerror(const char* s)
{
    printf("\n%sError%s : Line %s%d%s.\n%sMessage:%s %s\n",KRED,KWHT,KBLU,yylineno,KWHT,KRED,KGRN,s);
    exit(0);
}



void yywarning(const char* s)
{
    printf("\n%sWarning%s : Line %s%d%s.\n%sMessage:%s %s\n",KYEL,KWHT,KBLU,yylineno,KWHT,KRED,KGRN,s);
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
    maze.setStartPoint(startX, startY);
    maze.setEndPoint(endX, endY);
    
    if(!obstacleY.empty())
    {
        maze.setObstacleFromVector(obstacleX, obstacleY);
    }
   
    maze.traverseBreadthFirst();

    time = clock() - time;
    printf("Running Time = %s%fs%s\n",((float)time)/CLOCKS_PER_SEC,KGRN,KWHT);
    printf("Lines of Code = %s%d%s\n", KGRN, yylineno, KWHT);

    fclose(file);
}
