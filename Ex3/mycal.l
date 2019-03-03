%{
	#include "y.tab.h"
	#include <stdlib.h>
%}

NUMBER [0-9]+
OPERATOR [-+*/\^\(\)\&\|\n]

%%

{NUMBER} { yylval = atoi(yytext); return INTEGER; }
{OPERATOR} { return *yytext; }

%%

int yywrap(void){
	return 1;
}