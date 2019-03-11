#include <iostream>
#include <vector>
#include <assert.h>
#include <regex>
using namespace std;
vector<vector<string> > B;
vector<pair<string,int> > allString;
int GEN[10007];
int KILL[10007];
int IN[10007],OUT[10007];

string to_bin(int n){
	string s = "";
	while(n>0){
		s += (n%2) + '0';
		n/=2;
	}
	while(s.length() < B.size())
		s = s + '0';
	return s;
}
vector<int> Pred[10000];
int main(){
	int cnt = 0;
	string s;
	vector<string> tmp;
	while(getline(cin,s)){
		if(s=="LINKSTART")
			break;
		if(s==""){
			B.push_back(tmp);
			tmp.clear();
			continue;
		}
		tmp.push_back(s);
		allString.push_back(make_pair(s,B.size()));
	}
	int a,b;
	while(cin>>a>>b){
		assert(a>=0 && b>=0 && a<B.size() && b<B.size());
		Pred[b].push_back(a);
	}
	for(int i=0;i<allString.size();i++){
		GEN[allString[i].second] |= 1<<i;
		regex idreg("[a-zA-Z_][a-zA-Z_0-9]*"); smatch s1;
		regex_search(allString[i].first,s1,idreg);
		string id = allString[i].first.substr(s1.position(),s1.length());
		for(int j=0;j<allString.size();j++){
			if(allString[j].second == allString[i].second) continue;
			regex_search(allString[j].first,s1,idreg);
			string id2 = allString[j].first.substr(s1.position(),s1.length());
			if(id == id2){
				KILL[allString[i].second] |= (1<<j);
			}
		}
	}
	cout<<"GEN & KILL"<<endl;
	for(int i=0;i<B.size();i++)
		cout<<to_bin(GEN[i])<<" "<<to_bin(KILL[i])<<endl;
	for(int i=0;i<B.size();i++){
		IN[i] = 0;
		OUT[i] = GEN[i];
	}
	cout<<endl<<endl;
	cout<<"IN & OUT"<<endl;
	bool bt = 1;
	while(bt){
		bt = 0;
		for(int i=0;i<B.size();i++)
			cout<<to_bin(IN[i])<<" "<<to_bin(OUT[i])<<endl;
		cout<<endl<<endl;
		for(int i=0;i<B.size();i++){
			int newin = 0;
			for(auto j:Pred[i]){
				newin |= OUT[j];
			}
			if(newin != IN[i])
				bt = 1;
			IN[i] = newin;
			OUT[i] = (IN[i] & (~KILL[i])) | GEN[i];
		}
	}
}