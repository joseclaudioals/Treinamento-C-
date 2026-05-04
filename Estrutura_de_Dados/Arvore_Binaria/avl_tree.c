#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct Node {
    int key;
    int height;
    struct Node *left, *right, *parent;
}Node;

int height(const Node* a);
int balance(const Node* a, const Node* b);
Node* ll_rotation(Node* y);
Node* rr_rotation(Node* y);
Node* lr_rotation(Node* y);
Node* rl_rotation(Node* y);

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    Node* root = NULL;


    root = NULL;
    return 0;
}

Node* insert(Node* root, Node* parent, int value) {
    if (root==NULL) {
        Node* node = malloc(sizeof(Node));
        if (node == NULL)
            exit(1);

        node->key = value;
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
        node->parent = parent;

        return node;
    }

    if (value < root->key)
        root->left = insert(root->left, root->parent, value);
    else if (value > root->key)
        root->right = insert(root->right, root->parent, value);
    else
        return root;

    root->parent = parent;
    root->height = max(height(root->left), height(root->right)) +1;

    int bf = balance(root->left, root->right);

    if (bf > 1 && value < root->left->key)
        return ll_rotation(root);
    if (bf < -1 && value > root->right->key)
        return rr_rotation(root);
    if (bf < -1 && value > root->left->key)
        return lr_rotation(root);
    if (bf > 1 && value < root->right->key)
        return rl_rotation(root);

    return root;
}

Node* ll_rotation(Node* y) {
    Node* x = y->left;
    Node* sub_tree = x->right;

    x->right = y;
    y->left = sub_tree;

    if (y->parent != NULL) {
        if (y->parent->left == y)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    y->parent = x;

    if (sub_tree!=NULL)
        sub_tree->parent = y;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* rr_rotation(Node* y) {
    Node* x = y->right;
    Node* sub_tree = x->left;

    x->left = y;
    y->right = sub_tree;

    if (y->parent != NULL) {
        if (y->parent->left == y)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    y->parent = x;

    if (sub_tree!=NULL)
        sub_tree->parent = y;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* lr_rotation(Node* y) {
    y->left = rr_rotation(y->left);
    return ll_rotation(y);
}

Node* rl_rotation(Node* y) {
    y->right = ll_rotation(y->right);
    return rr_rotation((y));
}

int height(const Node* a) {
    if (a==NULL) return 0;
    return a->height;
}

int balance(const Node* a, const Node* b) {
    return height(a) - height(b);
}