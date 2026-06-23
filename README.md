#include <stdio.h>
#include <stdlib.h>

typedef struct TNode {
    int data;
    struct TNode* left;
    struct TNode* right;
} TNode;

int chercherMax(TNode* root) {
    int max_val = -1; // Unique point de sortie initialisé à -1 pour le cas NULL

    if (root != NULL) {
        if (root->right == NULL) {
            max_val = root->data; // Cas de base : plus de fils droit
        } else {
            max_val = chercherMax(root->right); // Appel récursif à droite
        }
    }

    return max_val; // Unique return
}
