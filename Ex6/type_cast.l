%{
	#include "y.tab.h"
	#include <stdlib.h>
%}

NUMBER [0-9]+
NUMBERF [0-9]*\.[0-9]{1,3}
NUMBERD [0-9]*\.[0-9]{4,}
CHAR \'.\'
OPERATOR [-+*/\(\)\n]

%%

{NUMBER} { yylval = atoi(yytext); return INTEGER; }
{NUMBERF} {return FLOATING;}
{NUMBERD} {return DOUBLE;}
{CHAR} {return CHARACTER;}
{OPERATOR} { return *yytext; }

%%

int yywrap(void){
	return 1;
}