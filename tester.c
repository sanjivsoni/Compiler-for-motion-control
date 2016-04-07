#include <stdio.h>
#include "symbolTable.h"

extern int yylex();
extern yylineno;
extern char* yytext;

int main(void)
{
  int ntoken,vtoken;
  ntoken = yylex();

  while(ntoken)
  {
    printf("%d\n", ntoken);
    ntoken = yylex();
  }

  return 0;
}
