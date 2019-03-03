%{
  #include <stdio.h>
  #include <string.h>
  #include "y.tab.h"
%}

NUMBER [0-9]+
OPERATORS [*\-+/\n&\|\(\)\^]

%%
{NUMBER} {
  yylval = atoi(yytext);
  return INTEGER;
}
{OPERATORS} {
  return *yytext;
}
%%

int yywrap() {
  return 1;
}
