#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <map>
#include <vector>

using namespace std;

int rd = 2000;
string file;
string line;

struct func {
  string name;
  vector<string> next;
  int np;
  int radd;
  vector<string> ptypes;
  func(){}
  func(string nme, vector<string> p) {
    name = nme;
    np = p.size();
    ptypes = p;
    radd = rd;
    rd += 10 * np;
  }

  void print() {
    cout << "Return address: ";
    cout << radd << endl;
    cout << "Number of parameters: ";
    cout << np << endl;
    cout << "Parameter type: ";
    for(int i = 0; i < ptypes.size(); ++i) {
      cout << ptypes[i];
      if(i != ptypes.size() - 1) cout << ", ";
    }
    cout << endl;
    cout << endl;
  }
};

map<string, func> mp;
int sp = 500;
stack<string> sys;

void printStack() {
  stack<string> tmp = sys;
  cout << "STACK DETAILS:\n\n"; 
  while(tmp.size()) {
    string cur = tmp.top(); 
    tmp.pop();
    mp[cur].print();
  }
  cout << "STACK POINTER -> " << sp + sys.size() * sizeof(func) << endl;
}

void dfs(string cur) {
  sys.push(cur);
  cout << "ENTER: " << cur << endl;
  printStack();
  for(auto x: mp[cur].next) {
    dfs(x);
  }
  cout << "EXIT: " << sys.top() << endl << endl;
  sys.pop();
  printStack();
}

int main() {
	cin >> file;
	ifstream f(file.c_str());
  bool proto = false;
  while(getline(f, line)) {
    if(line.back() != ';' && !proto) {
      proto = true;
      continue;
    }
    if(line.find("main()") != string::npos) break;
    if(proto) {
      for(auto s: mp) {
        func r = s.second;
        if(line.find(r.name) != string::npos) {
          while(getline(f, line)) {
            if(line[0] == '}') break;
            for(auto x: mp) {
              func v = x.second;
              if(v.name != r.name) 
                if(line.find(v.name) != string::npos) {
                  mp[r.name].next.emplace_back(v.name);
                }
            }
          }
          break;
        }
      }
    } else {
      int i = 0;
      while(line[i] != ' ') ++i;
      ++i;
      string name;
      while(line[i] != '(') name += line[i], ++i;
      ++i;
      vector<string> params;
      while(line[i] != ')') {
        string now;
        while(line[i] != ',' && line[i] != ')') now += line[i], ++i;
        if(line[i] == ',') ++i;
        params.emplace_back(now);
      }
      func cur(name, params);
      mp[name] = cur;
    }
  }
  vector<string> calls;
  while(getline(f, line)) {
    for(auto s: mp) {
      func r = s.second;
      if(line.find(r.name) != string::npos) {
        calls.emplace_back(r.name);
      }
    }
  }
  for(auto c: calls) {
    dfs(c);
  }
}