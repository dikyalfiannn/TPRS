#ifndef AVL_H
#define AVL_H

#include "../common/dokter.h"
#include <string>
using namespace std;

struct NodeAVL {
    Dokter* dataDokter;
    string nama; 
    NodeAVL *left, *right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(NodeAVL* node) {
    if(node == NULL) return 0;
    return node->height;
}

int getBalance(NodeAVL* node) {
    if(node == NULL) return 0;
    return height(node->left) - height(node->right);
}

NodeAVL* newNode(Dokter* d) {
    NodeAVL* node = new NodeAVL;
    node->dataDokter = d;
    node->nama = d->nama; 
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

NodeAVL* rotateRight(NodeAVL* y) {
    NodeAVL* x = y->left;
    NodeAVL* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    
    return x;
}

NodeAVL* rotateLeft(NodeAVL* x) {
    NodeAVL* y = x->right;
    NodeAVL* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    return y;
}

NodeAVL* insert(NodeAVL* node, Dokter* d) {
    if(node == NULL) return newNode(d);
    
    if(d->nama < node->nama) {
        node->left = insert(node->left, d);
    } else if(d->nama > node->nama) {
        node->right = insert(node->right, d);
    } else {
        return node;
    }
    
    node->height = 1 + max(height(node->left), height(node->right));
    
    int balance = getBalance(node);
    
    if(balance > 1 && d->nama < node->left->nama) {
        return rotateRight(node);
    }
    
    if(balance < -1 && d->nama > node->right->nama) {
        return rotateLeft(node);
    }
    
    if(balance > 1 && d->nama > node->left->nama) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    if(balance < -1 && d->nama < node->right->nama) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}

void tampilkanSorted(NodeAVL* root) {
    if(root != NULL) {
        tampilkanSorted(root->left);
        cout << "- " << root->dataDokter->nama 
             << " (Spesialisasi: " << root->dataDokter->spesialisasi << ")\n";
        tampilkanSorted(root->right);
    }
}

Dokter* cariDokterByNama(NodeAVL* root, string nama) {
    if(root == NULL) return NULL;
    
    if(nama == root->nama) {
        return root->dataDokter;
    }
    
    if(nama < root->nama) {
        return cariDokterByNama(root->left, nama);
    } else {
        return cariDokterByNama(root->right, nama);
    }
}

NodeAVL* buildAVLFromArray(Dokter dokterList[], int jumlah) {
    NodeAVL* root = NULL;
    for(int i = 0; i < jumlah; i++) {
        root = insert(root, &dokterList[i]);
    }
    return root;
}

#endif
