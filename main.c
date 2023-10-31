#include <stdio.h>
#include <stdlib.h>

// ??????? JP - João Pedro ???????
// Definição da estrutura do noh da arvore B
typedef struct BTreeNode {
    int keys[31];            // Armazena até 31 chaves
    struct BTreeNode* children[32]; // Até 32 filhos
    int key_count;           // Contagem de chaves no nó
    int leaf;                // Indica se o nó é uma folha
} BNode;

void insertNonFull(BNode* node, int key);
void splitChild(BNode* parent, int index, BNode* child);

struct BTree {
    struct BTreeNode *root; // Ponteiro para o nó raiz
    int t; // Ordem da Árvore B
};

// Função para criar um novo nó
BNode* createNode(int leaf) {
    BNode* newNode = (BNode*)malloc(sizeof(BNode));
    if (newNode) {
        newNode->key_count = 0;
        newNode->leaf = leaf;
        for (int i = 0; i < 32; i++) {
            newNode->keys[i] = 0;
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

// Função para inserir uma chave na árvore B
void insert(struct BTree* tree, int key) {
    BNode* root = tree->root;
    if (root->key_count == 31) {
        // Se o nó raiz estiver cheio, crie um novo nó para se tornar a nova raiz
        BNode* newRoot = createNode(0);
        newRoot->children[0] = root;
        splitChild(newRoot, 0, root);
        tree->root = newRoot;
        insertNonFull(newRoot, key);
    } else {
        insertNonFull(root, key);
    }
}

// Função para inserir uma chave em um nó não cheio
void insertNonFull(BNode* node, int key) {
    int i = node->key_count - 1;
    if (node->leaf) {
        // Inserir a chave em ordem decrescente
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->key_count++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->key_count == 31) {
            // Se o filho estiver cheio, divida-o
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Função para dividir um nó
void splitChild(BNode* parent, int index, BNode* child) {
    BNode* newChild = createNode(child->leaf);
    parent->key_count++;
    for (int i = parent->key_count - 1; i > index; i--) {
        parent->keys[i] = parent->keys[i - 1];
        parent->children[i + 1] = parent->children[i];
    }
    parent->keys[index] = child->keys[15]; // Mova a chave mediana para o pai
    parent->children[index + 1] = newChild;
    child->key_count = 15; // Atualize o número de chaves no nó original
    for (int i = 0; i < 15; i++) {
        newChild->keys[i] = child->keys[i + 16]; // Copie as chaves restantes para o novo nó
        child->keys[i + 16] = 0;
    }
    if (!child->leaf) {
        for (int i = 0; i < 16; i++) {
            newChild->children[i] = child->children[i + 16]; // Copie os filhos restantes
            child->children[i + 16] = NULL;
        }
    }
}

// ??????? GB - Gabriel Berle ???????


// ??????? Leo - Leonardo B. de S. ???????


// ??????? Gui - Guilherme Costa ???????


int main(){

}