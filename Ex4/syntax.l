%{
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
int yywrap();
%}
datatype "int"|"float"|"char"|"double"|"void"
identify [a-zA-Z_][a-zA-Z_0-9]*
CON ([0-9]+)|([0-9]*\.[0-9]+)
%%
while {return WHILE;}
for {return FOR;}
if {return IF;}
{datatype} {return DT;}
{identify} {return ID;}
= {return ASGN;}
\+\+ {return INC;}
\-\- {return INC;}
(\<|\>)(=)? {return ROP;}
\!= {return ROP;}
== {return ROP;}
{CON} {return CON;}
; {return SC;}
, {return COM;}
[\+\-\*\/\%] {return OPER;}
\( {return OP;}
\) {return CP;}
\{ {return OB;}
\} {return CB;}
%%
int yywrap(){
return 1;
}