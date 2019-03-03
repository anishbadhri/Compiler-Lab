%{
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
struct symbol_table{
	string id;
	string type;
	int add;
	string value;
	symbol_table(string i,string t,int a,string v){id=i; type = t;add = a;value = v;}
};
map <string,int> type_size;

int cur_addr = 1000;
string last_id = "";
string last_data_type = "";
int state = 0;
vector<symbol_table> v;
%}
datatype int|float|char|double 
keyword {datatype}|for|if|void|else|printf|scanf
id [a-zA-Z_][_a-zA-Z0-9]*
digit [0-9]
delim [\s\t\n]
%%
\,|\; {if(last_id != ""){v.push_back(symbol_table(last_id,last_data_type,cur_addr,""));cur_addr += type_size[last_data_type];last_id = ""; state = 0;}printf("SP ");}
\{|\}|\,|\"|\'|\(|\)|\;|\: {printf("SP ");}
\/\*(.|\n)*\*\/	{printf("M_COMMENT ");} 
\/\/.* {printf("S_COMMENT ");}
{datatype} {printf("DT "); state = 1;last_data_type = string(yytext);}
{keyword} { printf("KW "); }
\+|\-|\*|\/|\% { printf("OP "); }
{id} { printf("ID "); if(state==1) { state = 2; last_id = string(yytext);}}
#.* { printf("PPD "); }
\(.*\) { printf("FC "); }
= {printf("ASSIGN "); if(state==2){state = 3;}}
== {printf("EQ");}
\< {printf("LT");}
\> {printf("GT");}
\<\> {printf("NE");}
\<= {printf("LE");}
\>= {printf("GE");}
{digit}*\.{digit}+ {printf("FLOAT_CONST "); if(state==3){state=0;v.push_back(symbol_table(last_id,last_data_type,cur_addr,string(yytext)));cur_addr += type_size[last_data_type]; last_id = "";} }
{digit}+ {printf("NUM_CONST "); if(state==3){state=0;v.push_back(symbol_table(last_id,last_data_type,cur_addr,string(yytext)));cur_addr += type_size[last_data_type]; last_id = "";}}
\'.\'	{printf("CHAR_CONST "); if(state==3){state=0;v.push_back(symbol_table(last_id,last_data_type,cur_addr,string(yytext)));cur_addr += type_size[last_data_type]; last_id = "";}}
\".*\" {printf("STRING_CONST "); if(state==3){state=0;v.push_back(symbol_table(last_id,last_data_type,cur_addr,string(yytext)));cur_addr += type_size[last_data_type]; last_id = "";}}
.	{printf(" ");}
%%
int main(int argc, char** argv){
	FILE *file;
	file = fopen("file.txt","r");
	if(!file)
		exit(0);
	type_size["int"] = type_size["float"] = 4;
	type_size["char"] = 1;
	type_size["double"] = sizeof(double);
	yyin = file;
	yylex();
	printf("\nID\tTYP\tADDR\tVAL\n");
	for(int i=0;i<v.size();i++){
		printf("%s\t%s\t%d\t%s\n",v[i].id.c_str(),v[i].type.c_str(),v[i].add,v[i].value.c_str());
	}
}