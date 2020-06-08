/**
* @brief    Ficheiro que contem funções utilizadas na construção da AVL utilizada e em todas as funcionalidades por esta suportadas.
* @file     tree.c
*/
#include "tree.h"


struct Node {
    char* key;
    struct Node *left;
    struct Node *right;
    int height;
    void* equals;
};


/**
* @brief              Função que calcula a altura de um nodo
* @param [N]          Apontador para o nodo
* @return             Altura de um nodo
*/
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}


/**
* @brief              Função que devolve o máximo de dois inteiros
* @param [a]          Um dos inteiros para comparação
* @param [b]          Um dos inteiros para comparação
* @return             Máximo entre dois inteiros
*/
int max(int a, int b)
{
    return (a > b)? a : b;
}


/**
* @brief              Inicializa uma AVL
* @return             Retorna a AVL inicializada
*/
struct Node* initAVL (){
  AVL* a = malloc(sizeof(AVL));
  a->key = NULL;
  a->left = NULL;
  a->height = 0;
  a->right = NULL;
  a->equals = NULL;
  return a;
}


/**
* @brief              Função que devolve o número de nodos da árvore
* @param [nodo]       Nodo é um apontador do tipo AVL
* @return             Numero de nodos da árvore
*/
int numNode(AVL* nodo){
  if (nodo){
    return 1 + numNode(nodo->left) + numNode(nodo->right);
  }
  else return 0;
}

/**
* @brief              Funcao que cria um novo nodo
* @param [key]        Char* utilizado para a key da arvore
* @param [equals]     Parametro void que será inserido no equals da AVL
* @return             Retorna o novo nodo
*/

struct Node* newNode(char* key,void* a)
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->equals = a;

    return(node);
}

/**
* @brief              Função que efetua uma rotação da árvore para a direita
* @param [y]          Apontador para o nodo
* @return             Árvore após ser rodada para a direita
*/
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}


/**
* @brief              Função que efetua uma rotação da árvore para a esquerda
* @param [x]          Apontador para o nodo
* @return             Árvore após ser rodada para a esquerda
*/
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}


/**
* @brief              Função que vê se a arvore é balanceada
* @param [N]          Apontador para o nodo
* @return             Árvore balanceada
*/
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


/**
* @brief              Função que insere um elemento na árvore
* @param [node]       Node é um apontador para a struct
* @param [key]        Key é um apontador de um char
* @param [equals]     Equals é um apontador de um void
* @return             Apontador para a estrutura após ter sido inserido o valor
*/
struct Node* insert(struct Node* node, char* key, void* equals)
{

    if (node == NULL)
        return(newNode(key,equals));

    if ((strcmp(key, node->key)) < 0)
        node->left  = insert(node->left, key,equals);
    else if (strcmp(key, node->key) > 0)
        node->right = insert(node->right, key,equals);

    node->height = 1 + max(height(node->left),
                           height(node->right));



    int balance = getBalance(node);

    if (balance > 1 && strcmp(key, node->left->key) < 0)
        return rightRotate(node);

    if (balance < -1 && strcmp(key, node->right->key) >= 0)
        return leftRotate(node);

    if (balance > 1 && strcmp(key, node->left->key) >= 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && strcmp(key, node->right->key) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVL* searchAVLTMP (AVL* node, char* key){

    if(node == NULL)
        return 0;
    if(strcmp(node->key,key) == 0){
        return node;
    }
    if(strcmp(node->key,key) < 0)
        return searchAVLTMP(node->right,key);
    else
        return searchAVLTMP(node->left,key);

}

/**}
* @brief               Função que procura um elemento na árvore
* @param [node]        Nodo é um apontador do tipo AVL
* @param [key]         Key é um apontador de um char
* @return              Resultado da procura, retornando 0 caso essa procura falhe
*/
int searchAVL (AVL* node, char* key){

    if(node == NULL)
        return 0;
    if(strcmp(node->key,key) == 0)
        return 1;
    if(strcmp(node->key,key) < 0)
        return searchAVL(node->right,key);
    else
        return searchAVL(node->left,key);

}


/**
* @brief               Função que devolve a key de a
* @param [a]           a é um apontador do tipo AVL
* @return              Key de a
*/
char* getKey(AVL* a){
  return a->key;
}

/**
* @brief               Função que devolve o equals de a
* @param [a]           a é um apontador do tipo AVL
* @return              Equals de a
*/
void* getEquals(AVL* a){
  return (void*)a->equals;
}

/**
* @brief               Função que devolve a esquerda de a
* @param [a]           a é um apontador do tipo AVL
* @return              Esquerda de a
*/
AVL* getLeft (AVL* a){
  return a->left;
}

/**
* @brief               Função que devolve a direita de a
* @param [a]           a é um apontador do tipo AVL
* @return              Direita de a
*/
AVL* getRight (AVL* a){
  return a->right;
}
