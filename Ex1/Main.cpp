#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<sstream>
#include<map>
using namespace std;
struct var_info{
	string type;
	string value;
	int address;
};
set<string> keywords;
map<string,var_info> sym;
set<char> sp;
int starting_address = 1000;
map<string,int> size_mapping;
string arith_op="+-*/%";
map<string,int> m;
bool in_comm = 0;
int symbol_state = 0;
void init(){
	keywords.insert("int");
	keywords.insert("char");
	keywords.insert("float");
	keywords.insert("double");
	size_mapping["int"] = sizeof(int);
	size_mapping["char"] = sizeof(char);
	size_mapping["float"] = sizeof(float);
	size_mapping["double"] = sizeof(double);
	sp.insert('{');
	sp.insert('}');
	sp.insert(',');
	sp.insert(';');
}
void parse(string s){
	int state = 0;
	string cur_type = "";
	string last_id = "";
	bool assign_bool = 0;
	for(int i=0;i<s.length();i++){
		if(in_comm){
			while(i+1<s.length()){
				if(s[i]=='*' && s[i+1]=='/'){
					cout<<"M_COMMENT ";
					in_comm = 0;
					break;
				}
				i++;
			}
			if(!in_comm){
				i++;
			}
			continue;
		}
		//COMMENTS
		if(s[i]=='/' && s[i+1]=='/'){
			cout<<"S_COMMENT\n";
			return;
		}
		if(s[i]=='/' && s[i+1]=='*'){
			in_comm = 1;
			continue;
		}
		if(s[i]==' '){
			state = 0;
			continue;
		}
		if(state==0 && s[i]=='#'){
			//PREPROCESSOR DIRECTIVE REGEX
			state = 1;
			if(s.substr(1,7)=="include" || s.substr(1,6) == "define" || s.substr(1,6) == "pragma"){
				int it = 7;
				if(s.substr(1,7)=="include")
					it = 8;
				state = 2;
				if(s[it]=='<')
					state = 3;
				else if(s[it]=='"')
					state = 4;
				it = s.length() - 1;
				while(s[it]==' ')
					it--;
				if((state==3 && s[it]=='>') || (state==4 && s[it]=='"')){
					cout<<"PPD\n";
					return;
				}
				else{
					cout<<"Error\n";
					return;
				}
			}
		}
		if(state==0){
			//SPECIAL CHARACTER CHECK
			if(sp.find(s[i])!=sp.end()){
				cout<<"SP ";
				continue;
			}
			//KEYWORD CHECK
			stringstream ss(s.substr(i,s.length()-i));
			string st; ss>>st;
			if(keywords.find(st)!=keywords.end()){
				cur_type = st;
				cout<<"KW ";
				i += st.length()-1;;
				continue;
			}
			//IDENTIFIER AND FUNCTION CHECK
			int pos = i;
			if(isalpha(s[i])){
				i++;
				while(isdigit(s[i]) || isalpha(s[i])){
					i++;
				}
				if(s[i]=='('){
					int it = i;
					while(s[it]!=')' && it<s.length())
						it++;
					if(it == s.length())
						cout<<"Error ";
					else
						cout<<"FC ";
					continue;
				}
				else{
					string var_name = s.substr(pos,i-pos);
					i--;
					cout<<"ID ";
					last_id = var_name;
					if(cur_type != ""){
						sym[var_name].type = cur_type;
						sym[var_name].address = starting_address;
						starting_address += size_mapping[cur_type];
					}
					symbol_state = 1;
					continue;
				}
			}
			//OPERATOR CHECK
			if(s[i]=='<'){
				if(s[i+1]=='='){
					cout<<"LE ";
					i++;
					continue;
				}
				else if(s[i+1]=='>'){
					cout<<"NE ";
					i++;
					continue;
				}
				else{
					cout<<"LT ";
					continue;
				}
			}
			else if(s[i]=='>'){
				if(s[i+1]=='='){
					cout<<"GE ";
					i++;
					continue;
				}
				else{
					cout<<"GT ";
					continue;
				}
			}
			else if(s[i]=='='){
				if(s[i+1]=='='){
					cout<<"EQ ";
					i++;
					continue;
				}
				cout<<"ASSIGN ";
				assign_bool = 1;
				continue;
			}
			else if(arith_op.find(s[i])!=string::npos){
				if(s[i+1]=='='){
					i++;
					cout<<"ASSIGN ";
					assign_bool = 1;
					continue;
				}
				cout<<"ARITH_OP ";
				continue;
			}
			//CONSTANT CHECK
			if(s[i]=='.'){
				i++;
				if(isdigit(s[i])){
					while(isdigit(s[i]))
						i++;
					i--;
					cout<<"FLOAT_CONST ";

					continue;
				}
				cout<<"Error ";
				continue;
			}
			if(isdigit(s[i])){
				int pos = i;
				while(i<s.length() && isdigit(s[i]))
					i++;
				if(s[i]=='.'){
					i++;
					if(isdigit(s[i])){
						while(isdigit(s[i]))
							i++;
						if(assign_bool){
							sym[last_id].value = s.substr(pos,i-pos);
							assign_bool = 0;
						}
						i--;
						cout<<"FLOAT_CONST ";
						continue;
					}
					cout<<"Error ";
					continue;
				}
				if(assign_bool){
					sym[last_id].value = s.substr(pos,i-pos);
					assign_bool = 0;
				}
				i--;
				cout<<"NUM_CONST ";
				continue;
			}
			if(s[i]=='\''){
				int pos = i;
				if(i+2<s.length() && s[i+2] == '\''){
					if(assign_bool){
						sym[last_id].value = s.substr(pos,3);
						assign_bool = 0;
					}
					i += 2;
					cout<<"CHAR_CONST ";
					continue;
				}
			}
			if(s[i]=='"'){
				int pos = i;
				i++;
				while(i<s.length() && s[i]!='"')
					i++;
				if(s[i]=='"'){
					if(assign_bool){
						sym[last_id].value = s.substr(pos,i-pos+1);
						assign_bool = 0;
					}
					cout<<"STRING_CONST ";
					continue;
				}
			}
		}
	}
	cout<<endl;
}
int main(){
	ifstream f("file.txt");
	string s;
	init();
	while(getline(f,s)){
		parse(s);
	}

	cout<<"\n\n\nSymbol Table\n";
	cout<<"Var\tType\tAddress\tValue\n";
	for(auto i:sym){
		cout<<i.first<<"\t"<<i.second.type<<"\t"<<i.second.address<<"\t"<<i.second.value<<endl;
	}
	return 0;
}