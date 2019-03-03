%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
int yyparse();
void yyerror(char *);
FILE *yyin;
%}
%token DT
%token ID
%token ASGN

%token CON
%token SC
%token COM
%token WHILE
%token ROP
%token IF
%token OB
%token CB
%token FOR
%token OP
%token CP
%token OPER
%token INC
%start program
%%
program:
Declaration program
| Assignment SC program
| Condition program
| Loop program
|
;
Declaration:
DT Assignment Propogate
| DT ID Propogate
;
Assignment:
ID ASGN CON
;
Propogate:
SC
| COM ID Propogate
| COM Assignment Propogate
;
Condition:
IF OP Expression ROP Expression CP OB program CB
| IF OP Expression CP OB program CB
;
Expression:
ID
| CON
| Expression OPER Expression
| '(' Expression ')'
Loop:
FOR OP LoopA LoopB LoopC CP OB program CB
| WHILE OP LoopD CP OB program CB
;
LoopA:
Declaration
| Assignment SC

| SC
;
LoopB:
Expression SC
| Expression ROP Expression SC
| SC
;
LoopC:
ID INC
|
;
LoopD:
Expression
| Expression ROP Expression
;
%%
int main(int argc,char* argv[]){
FILE *file;
file = fopen(argv[1],"r");
yyin = file;
yyparse();
printf("Syntax Correct\n\n");
return 0;
}
void yyerror(char *s){
fprintf(stderr,"%s\n",s);
exit(0);
}