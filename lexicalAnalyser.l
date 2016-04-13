%{
#include "parser.tab.h"
%}

%%
:                       return COLON;
"rows"                  return ROWS;
"columns"               return COLUMNS;
"obstacle"              return OBSTACLE;
"start"                 return START;
"end"                   return END;
[0-9]+                  {yylval.digit = atoi(yytext);return INTEGER;}
\([0-9]+,[0-9]+\)       {yylval.id = yytext;return POINT;}
#.*$                    return COMMENT;
[ \t\n]                   ;
.                       return ERROR;

%%
int yywrap(void)
{
  return 1;
}
