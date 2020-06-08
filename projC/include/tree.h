#ifndef tree_h
#define tree_h
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct Node AVL;


int height(struct Node *N);
int max(int a, int b);
struct Node* initAVL ();
int numNode(AVL* nodo);
struct Node* newNode(char* key,void* a);
struct Node *rightRotate(struct Node *y);
struct Node *leftRotate(struct Node *x);
int getBalance(struct Node *N);
struct Node* insert(struct Node* node, char* key, void* equals);
AVL* searchAVLTMP(AVL* node, char* key);
int searchAVL (struct Node* node, char* key);
char* getKey(AVL* a);
void* getEquals(AVL* a);
AVL* getLeft (AVL* a);
AVL* getRight (AVL* a);

#endif
