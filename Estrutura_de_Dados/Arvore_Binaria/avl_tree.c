#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct Node {
    int key;
    int height;
    struct Node *left, *right, *parent;
}Node;

int height(const Node* a);
int balance(const Node* a);
Node* insert(Node* root, Node* parent, int value);
Node* ll_rotation(Node* y);
Node* rr_rotation(Node* y);
Node* lr_rotation(Node* y);
Node* rl_rotation(Node* y);
Node* min_key(Node* root);
Node* max_key(Node* root);
Node* search(Node* root, int value);
Node* sucessor(const Node* root);
Node* predecessor(const Node* root);
Node* delete_node(Node* root, int value);
void print_tree(const Node* root, int s);
void destroy_tree(Node* root);

int main(void) {
    Node* root = NULL;
    int valores[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(valores) / sizeof(valores[0]);

    printf("--- Inserindo valores ---\n");
    for (int i = 0; i < n; i++) {
        root = insert(root, NULL, valores[i]);
    }

    print_tree(root, 0);

    printf("\n--- Removendo o 30 ---\n");
    root = delete_node(root, 30);
    print_tree(root, 0);

    printf("\n--- Removendo a raiz (25) ---\n");
    root = delete_node(root, 25);
    print_tree(root, 0);

    destroy_tree(root);
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
        root->left = insert(root->left, root, value);
    else if (value > root->key)
        root->right = insert(root->right, root, value);
    else
        return root;

    root->parent = parent;
    root->height = max(height(root->left), height(root->right)) +1;

    int bf = balance(root);

    if (bf > 1 && value < root->left->key)
        return ll_rotation(root);
    if (bf < -1 && value > root->right->key)
        return rr_rotation(root);
    if (bf > 1 && value > root->left->key)
        return lr_rotation(root);
    if (bf < -1 && value < root->right->key)
        return rl_rotation(root);

    return root;
}

Node* ll_rotation(Node* y) {
    Node* x = y->left;
    Node* sub_tree = x->right;

    x->right = y;
    y->left = sub_tree;

    x->parent = y->parent;

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

    x->parent = y->parent;

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

int balance(const Node* a) {
    return height(a->left) - height(a->right);
}

void destroy_tree(Node* root) {
    if (root!=NULL) {
        destroy_tree(root->left);
        destroy_tree(root->right);
        free(root);
    }
}

Node* min_key(Node* root) {
    if (root==NULL)
        return NULL;

    while (root->left!=NULL) root = root->left;

    return root;
}

Node* max_key(Node* root) {
    if (root==NULL)
        return NULL;

    while (root->right!=NULL) root = root->right;

    return root;
}

Node* search(Node* root, int value) {
    if (root == NULL || root->key == value)
        return root;

    if (value<root->key)
        return search(root->left, value);
    else
        return search(root->right, value);
}

void print_tree(const Node* root, int s) {
    if (root != NULL) {
        print_tree(root->left, s+5);
        for (int i=0; i<s; i++) printf(" ");
        printf("%i \n", root->key);
        print_tree(root->right, s+5);
    }
}

Node* sucessor(const Node* root) {
    if (root->right != NULL)
        return min_key(root->right);

    Node* parent = root->parent;
    while ( parent != NULL && parent->right == root) {
        root = parent;
        parent = parent->parent;
    }

    return parent;
}

Node* predecessor(const Node* root) {
    if (root->left != NULL)
        return max_key(root->left);

    Node* parent = root->parent;
    while ( parent != NULL && parent->left == root) {
        root = parent;
        parent = parent->parent;
    }

    return parent;
}

Node* delete_node(Node* root, int value) {
    if (root==NULL)
        return root;
    if (value < root->key)
        root->left = delete_node(root->left, value);
    else if (value > root->key)
        root->right = delete_node(root->right, value);
    else {
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;

            //o node era uma folha
            if (temp==NULL) {
                temp = root;
                root = NULL;
            }else {
                root->key = temp->key;
                root->left = temp->left;
                root->right = temp->right;

                if (root->left != NULL) root->left->parent = root;
                if (root->right != NULL) root->right->parent = root;
            }
            free(temp);
        }else {
            Node* temp = sucessor(root);
            root->key = temp->key;
            root->right = delete_node(root->right, temp->key); // deletamos o sucessor
        }
    }
    if (root == NULL) return root;

    root->height = max(height(root->left), height(root->right)) + 1;
    int bf = balance(root);

    if (bf > 1) {
        if (balance(root->left) >= 0)
            return ll_rotation(root);
        else {
            return lr_rotation(root);
        }
    }
    if (bf < -1) {
        if (balance(root->right) <= 0)
            return rr_rotation(root);
        else {
            return rl_rotation(root);
        }
    }
    return root;
}
