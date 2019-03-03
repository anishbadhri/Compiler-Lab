%{
	#include "y.tab.h"
	#include <stdlib.h>
%}

NUMBER [0-9]+
NUMBERF [0-9]*\.[0-9]+
CHAR \'.\'
OPERATOR [-+*/\(\)\n]

%%

{NUMBER} { yylval = atoi(yytext); return INTEGER; }
{NUMBERF} {return FLOATING;}
{CHAR} {return CHARACTER;}
{OPERATOR} { return *yytext; }

%%

int yywrap(void){
	return 1;
}