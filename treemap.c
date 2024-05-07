#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
    TreeMap *newMap = (TreeMap *) malloc (sizeof(TreeMap));
    if(!newMap) exit(EXIT_FAILURE);
    newMap->root = NULL;
    newMap->current = NULL;
    newMap->lower_than = lower_than;
    return newMap;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    TreeNode *node = createTreeNode(key, value);
    if((!tree) || (!tree->root)) {
        tree->root = node;
        tree->current = node;
    }
    TreeNode *aux = tree->root;
    while(true) {
        if(aux->pair->key == key) return;
        if(aux->pair->key > key) {
            if(aux->left) aux = aux->left;
            else {
                aux->left = node;
                tree->current = node;
            }
        } else {
            if(aux->right) aux = aux->right;
            else {
                aux->right = node;
                tree->current = node;
            }
        }
    }
    /*while(true) {
        if(aux->pair->key == key) return;
        if(aux->left && aux->left->pair->key <= key && aux->pair->key ) {
            if(aux->right) aux = aux->right;
            else aux->right = node;
        } else  {
            if(aux->left) aux = aux->left;
            else aux->left = node;
        }
    }*/
}

TreeNode * minimum(TreeNode * x)
{
    TreeNode *aux = x;
    while(true) {
        if(aux->left) aux = aux->left;
        else break;
    }
    return aux;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{
    //TreeNode *aux = tree->root;
    
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) 
{
    TreeNode *aux = minimum(tree->root);
    tree->current = aux;
    return tree->current->pair;
}

Pair * nextTreeMap(TreeMap * tree) 
{
    //TreeNode *nextAux = tree->current;
    
    return NULL;
}
