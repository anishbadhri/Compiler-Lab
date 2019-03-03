%{
	#include <stdio.h>
	#include <math.h>
	int yylex(void);
	void yyerror(char *);
%}

%token INTEGER
%left '+' '-'
%left '*' '/' '^'
%left '&' '|'

%%
program:
	program expr '\n' {printf("%d\n",$2);}
	|
	;
expr:
	INTEGER {$$=$1; }
	| expr '+' expr {$$=$1+$3;}
	| expr '-' expr {$$=$1-$3;}
	| expr '*' expr {$$=$1*$3;} 
	| expr '/' expr {$$=$1/$3;} 
	| expr '^' expr {$$=pow($1,$3);} 
	| expr '&' expr {$$=$1&$2;}
	| expr '|' expr {$$=$1|$2;}
	| '(' expr ')' {$$=$2;}
	;
%%
void yyerror(char *s){
	printf("%s\n",s);
}
int main(){
	yyparse();
	return 0;
}