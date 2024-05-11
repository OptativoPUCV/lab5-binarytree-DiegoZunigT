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
        } else /*if(tree->lower_than(aux->pair->key, key))*/ {
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


void removeNode(TreeMap * tree, TreeNode* node) 
{
    TreeNode *aux;
    if(node->parent) aux = node->parent;
    else aux = node->right;
    if(!node->left && !node->right) {
        if(is_equal(tree, aux->left->pair->key, node->pair->key)) {
            aux->left = NULL;
        } else {
            aux->right = NULL;
        }
    } else if((!node->left && node->right) || (node->left && !node->right)) {
        if(is_equal(tree, aux->left->pair->key, node->pair->key)) {
            if(node->left) node = node->left;
            else node = node->right;
            aux->left = node;
            node->parent = aux;
        } else {
            if(node->left) node = node->left;
            else node = node->right;
            aux->right = node;
            node->parent = aux;
        }
    } else {
        while(aux) {
            if(aux->left) aux = aux->left;
            else break;
        }
        if(node->left) {
            node->left->parent = aux;
            aux->left = node->left;
        }
        node->right->parent = aux;
        aux->right = node->right;
        //node = aux;
        tree->root = aux;
    }
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
    //Pair *pair = searchTreeMap(tree, key);
    //if(pair) return pair;
    TreeNode *aux = tree->root;
    TreeNode *temp = aux;
    printf("%s - %s\n", (char *) temp->pair->key, (char *)key);
    while(aux) {
        temp = aux;
        if(is_equal(tree, aux->pair->key, key)) {
            tree->current = aux;
            return tree->current->pair;
        } else if(tree->lower_than(key, aux->pair->key)) {
            aux = aux->left;
        } else /*if(tree->lower_than(aux->pair->key, key))*/ {
            aux = aux->right;
        }
    }
    printf("%s - %s\n", (char *) temp->pair->key, (char *)key);
    if(is_equal(tree, temp->pair->key, key)) printf("Es igual");
    if(temp == tree->root || temp->right) {
        temp = minimum(temp->right);
        tree->current = temp;
        return tree->current->pair;
    } else if(temp->right == NULL) {
        TreeNode *node = temp;
        while(temp->parent) {
            node = temp;
            temp = temp->parent;
            if(temp->left == node) {
                tree->current = temp;
                return tree->current->pair;
            } 
        }
        return NULL;
    }
    return NULL;
    return temp->pair;
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
