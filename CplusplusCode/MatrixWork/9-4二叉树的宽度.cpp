#include <bits/stdc++.h>

using namespace std;

typedef struct node{
    int val;
    node* left = nullptr;
    node* right = nullptr;
}node;

node* root;
int level[1000] = {0};

void add(node* cur, int& num, int lev) {
    if (cur->val < num) {
        if (cur->left == nullptr) {
            node* n = new node;
            n->val = num;
            cur->left = n;
            level[lev] += 1;
            return;
        }
        else add(cur->left, num, lev+1);
    }
    else {
        if (cur->right == nullptr) {
            node* n = new node;
            n->val = num;
            cur->right = n;
            level[lev] += 1;
            return;
        }
        else add(cur->right, num, lev+1);
    }
}

void deleteTree(node* cur) {
    if (cur->left != nullptr) deleteTree(cur->left);
    if (cur->right!= nullptr) deleteTree(cur->right);
    delete(cur);
}

void buildTree() {
    root = new node;
    level[0] = 1;
    int n;
    cin >> n;
    scanf("%d",&root->val);
    for (int i = 1; i < n; ++i) {
        int val;
        scanf("%d",&val);
        add(root,val,1);
    }
}

void solution() {
    int maxnum = level[0];
    for (int i = 0; i < 1000; ++i) {
        if (level[i] == 0) break;
        maxnum = max(maxnum, level[i]);
        level[i] = 0;
    }
    cout << maxnum << endl;
}

int main() {
    int t;
    cin >> t;
    for (int ii = 0; ii < t; ++ii) {
        buildTree();
        solution();
        deleteTree(root);
    }
    return 0;
}