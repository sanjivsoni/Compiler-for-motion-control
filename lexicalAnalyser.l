%{
#include "symbolTable.h"
%}

%%
:                       return COLON;
"rows"                  return ROWS;
"columns"               return COLUMNS;
"map"                   return MAP;
"start"                 return START;
"end"                   return END;
"clear"                 return PATH_AVAILABLE;
"stone"                 return STONE;
"door"                  return DOOR;
[\([0-9]+,[0-9]+\)]*    return OBSTACLE;s
[0-9]+                  return INTEGER;
\([0-9]+,[0-9]+\)       return POINT;
#.*$                    return COMMENT;
[ \t]                   ;
[\n]                    return NEWLINE;
[\Z]                    return ENDOFFILE;
.                       return UNEXPECTED_CHARACTER;

%%
int yywrap(void)
{
  return 1;
}
