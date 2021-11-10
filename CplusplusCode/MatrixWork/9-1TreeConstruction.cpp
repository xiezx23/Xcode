#include <bits/stdc++.h>

using namespace std;

typedef struct node{
    int val;
    node* left = nullptr;
    node* right = nullptr;
}node;

node* root;

void add(node* cur, int& num) {
    if (cur->val < num) {
        if (cur->left == nullptr) {
            printf("%d ",cur->val);
            node* n = new node;
            n->val = num;
            cur->left = n;
            return;
        }
        else add(cur->left, num);
    }
    else {
        if (cur->right == nullptr) {
            printf("%d ",cur->val);
            node* n = new node;
            n->val = num;
            cur->right = n;
            return;
        }
        else add(cur->right, num);
    }
}

void deleteTree(node* cur) {
    if (cur->left != nullptr) deleteTree(cur->left);
    if (cur->right!= nullptr) deleteTree(cur->right);
    delete(cur);
}

int main() {
    root = new node;
    int n;
    cin >> n;
    scanf("%d",&root->val);
    for (int i = 1; i < n; ++i) {
        int val;
        scanf("%d",&val);
        add(root,val);
    }
    deleteTree(root);
    return 0;
}