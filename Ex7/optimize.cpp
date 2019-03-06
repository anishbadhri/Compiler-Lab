#include <bits/stdc++.h>
using namespace std;
vector<string> vs;
void constantFolding(){
	//Code Optimize
	for(auto& i:vs){
		regex x1("[0-9]+ *[-+*/] *[0-9]+");
		regex x2("\\( *[0-9]+ *\\)");
		while(1){
			smatch m1,m2;
			if(regex_search(i,m1,x1)){
				int split_on = m1.position();
				string s = i.substr(split_on,m1.length());
				int it = 0;
				string sint1 = "",sint2="";
				while(s[it]>='0' && s[it]<='9'){
					sint1 += s[it];
					it++;
				}
				char c;
				while(s[it]==' ')
					it++;
				c = s[it];
				while(!(s[it]>='0' && s[it]<='9'))
					it++;
				while(s[it]>='0' && s[it]<='9'){
					sint2 += s[it];
					it++;
				}
				int int1 = atoi(sint1.c_str()),int2 = atoi(sint2.c_str());
				// cout<<int1<<" "<<c<<" "<<int2<<endl;
				int ans;
				switch(c){
					case '+': ans = int1 + int2; break;
					case '-': ans = int1 - int2; break;
					case '*': ans = int1 * int2; break;
					case '/': ans = int1 / int2; break;
				}
				i.replace(split_on,m1.length(),to_string(ans));
			}
			else if(regex_search(i,m2,x2)){
				int split_on = m2.position();
				string s = i.substr(split_on,m2.length());
				string rep = "";int it = 0;
				while(!(s[it]>='0' && s[it]<='9'))
					it++;
				while(s[it]>='0' && s[it]<='9'){
					rep += s[it];
					it++;
				}
				i.replace(split_on,m2.length(),rep);
			}
			else
				break;
		}
	}
}
void algebraicIdentities(){
	//Algebraic Identities
	for(auto& i:vs){
		regex id("[a-zA-Z_][a-zA-Z_0-9]*");
		regex x11("[a-zA-Z_][a-zA-Z_0-9]* *[+] *0");
		regex x12("0 *[+] *[a-zA-Z_][a-zA-Z_0-9]*");
		regex x21("[a-zA-Z_][a-zA-Z_0-9]* *[*] *1");
		regex x22("1 *[*] *[a-zA-Z_][a-zA-Z_0-9]*");
		smatch s11,s12,s21,s22;
		if(regex_search(i,s11,x11)){
			int split_on = s11.position();
			string s = i.substr(split_on,s11.length());
			smatch t; regex_search(s,t,id);
			string new_id = s.substr(t.position(),t.length());
			i.replace(split_on,s11.length(),new_id);
		}
		else if(regex_search(i,s12,x12)){
			int split_on = s12.position();
			string s = i.substr(split_on,s12.length());
			smatch t; regex_search(s,t,id);
			string new_id = s.substr(t.position(),t.length());
			i.replace(split_on,s12.length(),new_id);
		}
		if(regex_search(i,s21,x21)){
			int split_on = s21.position();
			string s = i.substr(split_on,s21.length());
			smatch t; regex_search(s,t,id);
			string new_id = s.substr(t.position(),t.length());
			i.replace(split_on,s21.length(),new_id);
		}
		else if(regex_search(i,s22,x22)){
			int split_on = s22.position();
			string s = i.substr(split_on,s22.length());
			smatch t; regex_search(s,t,id);
			string new_id = s.substr(t.position(),t.length());
			i.replace(split_on,s22.length(),new_id);
		}
	}
}
void strengthReduction(){
	for(auto &i:vs){
		regex id("[a-zA-Z_][a-zA-Z_0-9]*");
		regex pow_id("\\([a-zA-Z_][a-zA-Z_0-9]*");
		regex mul2_1("[a-zA-Z_][a-zA-Z_0-9]* *[*] *2");
		regex mul2_2("2 *[*] *[a-zA-Z_][a-zA-Z_0-9]*");
		regex div2_1("[a-zA-Z_][a-zA-Z_0-9]* *[/] *2");
		regex pow2("pow\\(\\s*[a-zA-Z_][a-zA-Z_0-9]*\\s*\\,\\s*2\\s*\\)");
		smatch m_1,m_2;
		if(regex_search(i,m_1,mul2_1)){
			string s = i.substr(m_1.position(),m_1.length());
			smatch tmp;
			regex_search(s,tmp,id);
			string new_id = s.substr(tmp.position(),tmp.length());
			i.replace(m_1.position(),m_1.length(),new_id + "<<1");
		}
		else if(regex_search(i,m_2,mul2_2)){
			string s = i.substr(m_2.position(),m_2.length());
			smatch tmp;
			regex_search(s,tmp,id);
			string new_id = s.substr(tmp.position(),tmp.length());
			i.replace(m_2.position(),m_2.length(),new_id + "<<1");
		}
		else if(regex_search(i,m_1,div2_1)){
			string s = i.substr(m_1.position(),m_1.length());
			smatch tmp;
			regex_search(s,tmp,id);
			string new_id = s.substr(tmp.position(),tmp.length());
			i.replace(m_1.position(),m_1.length(),new_id + ">>1");
		}
		else if(regex_search(i,m_1,pow2)){
			string s = i.substr(m_1.position(),m_1.length());
			smatch tmp;
			regex_search(s,tmp,pow_id);
			string new_id = s.substr(tmp.position() + 1,tmp.length() - 1);
			i.replace(m_1.position(),m_1.length(),new_id + "*" + new_id);	
		}
	}
}
void deadcodeElimination(){
	int i = 0;
	regex jmp_stmt("goto [0-9]+");
	regex num("[0-9]+");
	for(;i<vs.size();i++){
		smatch tmp;
		if(regex_search(vs[i],tmp,jmp_stmt)){
			string s = vs[i].substr(tmp.position(),tmp.length());
			smatch tmp2;
			regex_search(s,tmp2,num);
			string s2 = s.substr(tmp2.position(),tmp2.length());
			int pos = atoi(s2.c_str());
			i = pos-2;
		}
		else
			cout<<vs[i]<<endl;
	}
}
int main(){
	string s;
	while(getline(cin,s))
		vs.push_back(s);
	constantFolding();
	algebraicIdentities();
	strengthReduction();
	deadcodeElimination();
}