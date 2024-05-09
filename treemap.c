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
    /*if((!tree) || (!tree->root)) {
        tree->root = node;
        tree->current = node;
        return;
    }*/
    TreeNode *aux = tree->root;
    while(aux) {
        if(is_equal(tree, aux->pair->key, key)) return;
        if(tree->lower_than(key, aux->pair->key)) {
            if(aux->left) aux = aux->left;
            else {
                aux->left = node;
                node->parent = aux;
                tree->current = node;
                return;
            }
        } else {
            if(aux->right) aux = aux->right;
            else {
                aux->right = node;
                node->parent = aux;
                tree->current = node;
                return;
            }
        }
    }
    
}

TreeNode * minimum(TreeNode * x)
{
    TreeNode *aux = x;
    while(aux->left) {
        aux = aux->left;
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
    TreeNode *aux = tree->root;
    while(aux) {
        if(is_equal(tree, aux->pair->key, key)) {
            tree->current = aux;
            return tree->current->pair;
        } else if(tree->lower_than(key, aux->pair->key)) {
            aux = aux->left;
        } else /*if(tree->lower_than(aux->pair->key, key))*/ {
            aux = aux->right;
        }
    }
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
    if(tree == NULL) return NULL;
    TreeNode *next = tree->current;
    if(next == tree->root || next->right) {
        next = minimum(next->right);
        tree->current = next;
        return tree->current->pair;
    } else if(next->right == NULL) {
        TreeNode *temp = next;
        while(next->parent) {
            temp = next;
            next = next->parent;
            if(next->left == temp) {
                tree->current = next;
                return tree->current->pair;
            } 
        }
        return NULL;
    }
    return NULL;
}
