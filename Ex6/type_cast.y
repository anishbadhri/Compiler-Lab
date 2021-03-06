%{
	#include <stdio.h>
	#include <math.h>
	int yylex(void);
	void yyerror(char *);
%}

%token INTEGER
%token FLOATING
%token CHARACTER
%token DOUBLE
%left '+' '-'
%left '*' '/' '^'
%left '&' '|'

%%
program:
	program iexpr '\n' {printf("Integer\n");}
	| program fexpr '\n' {printf("Float\n");}
	| program cexpr '\n' {printf("Character\n");}
	| program dexpr '\n' {printf("Double\n");}
	|
	;
op:
	'+'
	| '-'
	| '*'
	| '/'
	;
iexpr:
	INTEGER
	| iexpr op iexpr
	| '(' iexpr ')' 
	;
fexpr:
	FLOATING
	| iexpr op fexpr
	| fexpr op iexpr
	| fexpr op fexpr
	| '(' fexpr ')'
	;
dexpr:
	DOUBLE
	| dexpr op dexpr
	| iexpr op dexpr
	| dexpr op iexpr
	| dexpr op fexpr
	| fexpr op dexpr
	| '(' dexpr ')'
	;
cexpr:
	CHARACTER
	| cexpr op cexpr
	| '(' cexpr ')'
	;
%%
void yyerror(char *s){
	printf("%s\n",s);
}
int main(){
	yyparse();
	return 0;
}