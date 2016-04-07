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
[(][0-9]*[,][0-9]*[)]   return POINT;
[0-9]*                  return INTEGER;
[#][.][\n]              return COMMENT;
[ \t]                   ;
[\n]                    return NEWLINE;
.                       printf("Unexpected Character\n");

%%
int yywrap(void)
{
  return 1;
}
