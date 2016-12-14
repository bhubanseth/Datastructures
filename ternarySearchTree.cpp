#include<iostream>
#include <stdlib.h>
using namespace std;

#define LESSER -1
#define HIGHER 1
#define EQUAL 0

struct Node {
  char data;
  bool isEnd;

  struct Node *left,*eq,*right;
};

struct Node *newNode(char data) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->isEnd = false;
  newNode->left = newNode->eq = newNode->right = NULL;
  return newNode;
}

int compareData(char character, char nodeChar) {
  if (character < nodeChar) {
    return LESSER;
  } else if (character > nodeChar) {
    return HIGHER;
  }
  return EQUAL;
}

void insertWord(struct Node **root, char *word) {
  if ((*root)==NULL) {
    (*root) = newNode(*word);
  }
  int comparison = compareData(*word, (*root)->data);
  if (comparison == EQUAL) {
    if (*(word + 1)=='\0') {
      (*root)->isEnd = true;
      return;
    }
    return insertWord(&((*root)->eq), word + 1); 
  }
  return insertWord(comparison == LESSER? &((*root)->left): &((*root)->right), word);
}

void print(struct Node *root, int level) {
  if (root==NULL)
    return;
  cout<<"Level = "<<level<<endl;
  cout<<root<<","<<root->data<<","<<root->isEnd<<","<<root->left<<","<<root->eq<<","<<root->right<<endl;
  print(root->left, level+1);
  print(root->eq, level+1);
  print(root->right, level+1);
}

bool search(struct Node *root, char *word) {
  if (root==NULL)
    return false;
  int comparison = compareData(*word, root->data);
  if (comparison == 0) {
    if (*(word+1)=='\0')
      return root->isEnd;
    return search(root->eq, word + 1);
  }
  return search(comparison == LESSER? root->left : root->right, word);
}

int main() {
  struct Node *ternerySearchTree = NULL;
  char word1[] = "Bhubon";
  char word2[] = "Bhuban";
  char word3[] = "Bhawan";
  char word4[] = "Bhubane";

  insertWord(&ternerySearchTree, word1);
  insertWord(&ternerySearchTree, word2);
  insertWord(&ternerySearchTree, word3);
  print(ternerySearchTree, 0);
  cout<<search(ternerySearchTree, word2)<<endl;
  cout<<search(ternerySearchTree, word4)<<endl;
  return 0;
}

