%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>	

  int yylex();
  void yyerror(char*);

  struct node {
    char cur;
    int val;
    struct node *left, *right;
  };
  
  typedef struct node node;

  node *root;
  node *node_arr[100000];
  int node_ptr = 0;

  node* create(node *x, int s) {
    x = (node*)malloc(sizeof(node));
    x->val = s;
    x->cur = '@';
    x->left = x->right = NULL;
    return x;
  }

  node* assgn(node *x, node *left, node *right, char v) {
    x = (node*)malloc(sizeof(node));
    int lv = left->val, rv = right->val;
    x->cur = v;
    x->left = left;
    x->right = right;
    switch(v) {
      case '+': x->val = lv + rv; break;
      case '-': x->val = lv - rv; break;
      case '*': x->val = lv * rv; break;
      case '/': x->val = lv / rv; break;
      case '^': x->val = pow(lv, rv); break;
    }
    return x;
  }

  void inorder(node *cur) {
    if(cur == NULL) return ;
    inorder(cur->left);
    if(cur->cur == '@') printf("%d ", cur->val);
    else printf("%c ", cur->cur);
    inorder(cur->right);
  }

  void preorder(node *cur) {
    if(cur == NULL) return ;
    if(cur->cur == '@') printf("%d ", cur->val);
    else printf("%c ", cur->cur);
    preorder(cur->left);
    preorder(cur->right);
  }

  void postorder(node *cur) {
    if(cur == NULL) return ;
    postorder(cur->left);
    postorder(cur->right);
    if(cur->cur == '@') printf("%d ", cur->val);
    else printf("%c ", cur->cur);
  }
%} 

%token OP
%token INTEGER
%left '+' '-'
%left '/' '*' '^'
%left '&' '|' 


%%
  program:
    program expr '\n' {
      root = node_arr[$2];
      printf("INORDER: ");
      inorder(root);
      printf("\n");
      printf("PREORDER: ");
      preorder(root);
      printf("\n");
      printf("POSTORDER: ");
      postorder(root);
      printf("\n");
      printf("%d\n", root->val);
    }
    |
    ;
  expr:
    INTEGER {
      node *x;
      node_arr[node_ptr] = create(node_arr[node_ptr], $1);
      $$ = node_ptr;
      node_ptr++;  
    }
    | expr '+' expr {
      node_arr[node_ptr] = assgn(node_arr[node_ptr], node_arr[$1], node_arr[$3], '+');
      $$ = node_ptr;
      node_ptr++;  
    }
    | expr '-' expr {
      node *x;
      node_arr[node_ptr] = assgn(x,node_arr[$1],node_arr[$3],'-');
      $$ = node_ptr;
      node_ptr++;  
    }
    | expr '^' expr {
      node* x;
      node_arr[node_ptr] = assgn(x,node_arr[$1],node_arr[$3],'^');
      $$ = node_ptr;
      node_ptr++;
    }
    | expr '/' expr {
      node* x;
      x = assgn(x,node_arr[$1],node_arr[$3],'/');
      node_arr[node_ptr] = x;
      $$ = node_ptr;
      node_ptr++;
    }
    | expr '*' expr {
      node* x;
      x = assgn(x,node_arr[$1],node_arr[$3],'*');
      node_arr[node_ptr] = x;
      $$ = node_ptr;
      node_ptr++;
    }
    | '(' expr ')' {$$ = $2;}
    ;

%%

void yyerror(char* msg) {
  fprintf(stderr, "%s\n", msg);
}

int main() {
  yyparse();
  return 0;
}