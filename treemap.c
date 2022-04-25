#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

  TreeMap * tree = (TreeMap*) malloc(sizeof(TreeMap));

  tree->root = NULL;
  tree->lower_than = lower_than;
  
  return tree;
}


void insertTreeMap(TreeMap * tree, void* key, void * value){
  
  TreeNode* aux = tree->root;
  
  if(tree->root == NULL){
    aux = createTreeNode(key,value);
    tree->root = aux;
    tree->current = aux;
  } 
  
  while(aux != NULL){
    tree->current = aux;
    if(tree->lower_than(key, aux->pair->key) == 1){
      aux = aux->left;
    }
    else if(tree->lower_than(key, aux->pair->key) == 0){
      aux = aux->right;
    }
    else{
      break;
    }
  }
    
  if(aux == NULL){
    aux = createTreeNode(key,value);
    aux->parent = tree->current;
    if(tree->lower_than(key,aux->parent->pair->key) == 1){
      aux->parent->left = aux;
    }
    else{
      aux->parent->right = aux;
    }
    tree->current = aux;
  }

}

TreeNode * minimum(TreeNode * x){
  if(x == NULL) return x;

  while(!x){
    x = x->left;
  }
  return x->parent;
}

void removeNode(TreeMap * tree, TreeNode* node) {
  if(tree->root == NULL) return;
  
  if(node->parent->left==node){
    if(node->left==NULL || node->right==NULL){
      if(node->left!=NULL){
        node->left->parent = node->parent;
        node->parent->left = node->left;
        node=NULL;
      }
      else if(node->right!=NULL){
        node->right->parent = node->parent;
        node->parent->left = node->right;
        node=NULL;        
      }
      else{
        node->parent->left=node->left;
        node=NULL;
      }  
    }
    else{
      TreeNode* hijo = node->right;
      hijo = minimum(hijo);
      node->parent->left = hijo;
      hijo->parent = node->parent;
      hijo->right=node->right;
    }
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}

Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
