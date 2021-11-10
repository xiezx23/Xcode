// #include <bits/stdc++.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef struct node{
    int val;
    node* left = nullptr;
    node* right = nullptr;
}node;

vector<string> ans;
node* root;
int n, m;

void add(node* cur, int& num) {
    if (cur->val > num) {
        if (cur->left == nullptr) {
            node* n = new node;
            n->val = num;
            cur->left = n;
            return;
        }
        else add(cur->left, num);
    }
    else {
        if (cur->right == nullptr) {
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

void buildTree() {
    root = new node;
    scanf("%d",&root->val);
    for (int i = 1; i < n; ++i) {
        int val;
        scanf("%d",&val);
        add(root,val);
    }
}


string tran(int num) {
    string sign = "";
    if (num < 0) {
        sign = "-";
        num = -num;
    }
    string str = "";
    while(num) {
        str = (char)(num%10+'0')+str;
        num /= 10;
    }
    return sign+str;
}

void dfs(node* cur, int num, string str) {
    int mark = 1;
    num += cur->val;
    string tmp0 = "";
    if (str != "") tmp0 = "->";
    str += tmp0+ tran(cur->val);
    if (cur->left != nullptr) {
        mark = 0;
        dfs(cur->left, num, str);
    }
    if (cur->right != nullptr) {
        mark = 0;
        dfs(cur->right, num, str);
    }
    if (mark && num == m) {
        ans.push_back(str);
        return;
    }
}

void solution() {
    ans.clear();
    dfs(root, 0, "");
    for(auto i: ans) {
        cout << i << endl;
    }
    if (ans.size() == 0) cout << "NULL\n";
}

int main() {
    while (scanf("%d%d",&n,&m) != EOF) {
        buildTree();
        solution();
        deleteTree(root);
    }
    return 0;
}