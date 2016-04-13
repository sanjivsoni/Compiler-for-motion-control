%{
#include "symbolTable.h"
%}

%%
:                       return COLON;
"rows"                  return ROWS;
"columns"               return COLUMNS;
"obstacle"              return OBSTACLE;
"start"                 return START;
"end"                   return END;
[0-9]+                  {yyval.digit = atoi(yytext);return INTEGER;}
\([0-9]+,[0-9]+\)       return POINT;
#.*$                    return COMMENT;
[ \t\n]                   ;
[\Z]                    return ENDOFFILE;
.                       return UNEXPECTED_CHARACTER;

%%
int yywrap(void)
{
  return 1;
}
