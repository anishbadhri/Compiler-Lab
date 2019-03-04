#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <set>

using namespace std;

class node {
  public:
    string name;
    vector<string> others;
    string op;
    int unary;
    node *left, *right;
    node(){
      unary = 0;
      left = right = nullptr;
    }
    node(string name){
      unary = 0;
      left = right = nullptr;
      this->name = name;
    }
};

map<string, node*> nodes;
map<string, string> rhs_to_lhs;
map<node*, bool> visit;
set<node*> potential;

bool isop(char x) {
  return (x == '+') || (x == '-') || (x == '/') || (x == '*') || (x == '[');
}

node* create(string name) {
  if(nodes.find(name) == nodes.end()) {
    node *terminal = new node(name);
    terminal->unary = -1;
    nodes[name] = terminal;
    return terminal;
  } else {
    if(potential.count(nodes[name])) {
      potential.erase(nodes[name]);
    }
    return nodes[name];
  }
}

void dfs(node* cur) {
  if(visit.count(cur)) return ;
  visit[cur] = 1;
  cout << cur->name << " ";
  for(auto x: cur->others) {
    cout << x << " ";
  }
  cout << '\t';
  if(cur->unary == -1) return ;
  if(!cur->unary) {
    dfs(cur->left);
  } else {
    dfs(cur->left); dfs(cur->right);
  }
}


int main() {
  ifstream is("input.txt");
  string line;
  while(getline(is, line)) {
    string lhs, op1, op2;
    string op;
    int i = 0;
    while(i < line.size() && line[i] != '=') {
      lhs += line[i]; 
      ++i;
    }
    ++i;
    string rhs = string(line.begin() + i, line.end());
    if(nodes.count(lhs)) {
      nodes[rhs]->others.push_back(lhs);
      continue;
    }
    if(rhs_to_lhs.count(rhs)) {
      node *already = nodes[rhs_to_lhs[rhs]];
      cout << lhs << " " << already->name << endl;
      already->others.push_back(lhs);
      nodes[lhs] = already;
      continue;
    }
    while(i < line.size() && !isop(line[i])) {
      op1 += line[i];
      ++i;
    }
    op = line[i]; ++i;
    if(op[0] == '[') {
      while(i < line.size() && line[i] != ']') {
        op2 += line[i];
        ++i;
      }
      op += ']';
    } else {
      if(i < line.size()) {
        op2 = string(line.begin() + i, line.end());
      }
    }
    node *res = new node(lhs);
    if(op == "") {
      res->unary = 1;
      res->left = create(op1);
    } else if(op1 == "") {
      res->op = op;
      res->unary = 1;
      res->left = create(op2);
    } else {
      res->op = op;
      res->left = create(op1);
      res->right = create(op2);
    }
    nodes[lhs] = res;
    potential.insert(res);
    rhs_to_lhs[rhs] = lhs;
  }
  for(auto x: nodes) {
    node* n = x.second;
    cout << n->name << " ";
    for(auto r: n->others) cout << r << " ";
    if(n->left) cout << "LEFT: "<< n->left->name << " ";
    if(n->right) cout << "RIGHT: " << n->right->name << " ";
    cout << endl;
  }
}