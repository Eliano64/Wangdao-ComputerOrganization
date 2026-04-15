#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  struct node *left;
  struct node *right;
  int val;
} node;

typedef node *tree;

typedef struct {
  node *r;
  int stage; // 在insert中每一个（子）函数有两个递归点，同时进入一个递归点：>val
             // 或<val;
  //  stage = 0/1/2 表示未进入递归 进入/退出递归<val 进入/退出递归>val
} _insertFrame;

node * insert(int v, node *root) {
  if (root == 0) {
    node *n = (node *)malloc(sizeof(node));
    n->val = v;
    n->left = 0;
    n->right = 0;
    return n;
  }
  _insertFrame stack[128];
  int top = -1;
  stack[++top] = (_insertFrame){root, 0};
  while (top != -1) {
    _insertFrame *cur = &stack[top];
    if (cur->r == 0) {
      --top;
      cur = &stack[top];
      node *n = (node *)malloc(sizeof(node));
      n->val = v;
      n->left = 0;
      n->right = 0;
      if (cur->stage == 1) {
        cur->r->left = n;
      }
      if (cur->stage == 2) {
        cur->r->right = n;
      }
      continue;
    }
    if (cur->stage == 0) {
      if (v < cur->r->val) {
        cur->stage = 1;
        stack[++top] = (_insertFrame){cur->r->left, 0};
      } else if (v > cur->r->val) {
        cur->stage = 2;
        stack[++top] = (_insertFrame){cur->r->right, 0};
      }
      continue;
    }
    if (cur->stage != 0) {
      --top;
      continue;
    }
  }
  return root;
}

typedef struct{
    node *r;
    int stage; //两递归点： left, right
    //= 0/1/2 未进入 结束了left但没有未进入right 结束了right
}_inorderFrame;

void inorder(node *root){
    if(root==0){
        return;
    }
    //inorder(root->left);
    //printf("%d->",root->val);
    //inorder(root->right);
    _inorderFrame stack[128];
    int top = -1;
    stack[++top] = (_inorderFrame){root,0};
    while(top!=-1){
        _inorderFrame *f = &stack[top];
        if(f->r==0){
            --top;
            continue;
        }
        if(f->stage==0){
            f->stage = 1;
            stack[++top] = (_inorderFrame){f->r->left,0};
            continue;
        }
        if(f->stage==1){
           printf("%d->",f->r->val);
            f->stage = 2;
            stack[++top] = (_inorderFrame){f->r->right,0};
            continue;
        }
        if(f->stage==2){
            --top;
            continue;
        }
    }
}

int main() {
  tree t = (node *)malloc(sizeof(node));
  t->val = 5;
  t->left=0;
  t->right=0;
  for(int i = 0; i< 5; ++i){
    insert(i,t);
    insert(i+6,t);
  }
  inorder(t);
}