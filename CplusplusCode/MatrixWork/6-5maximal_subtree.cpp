/*************************************************************************
    > File Name: maximal_subtree.cpp
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2021-10-13

    @from:matrix 6-5 最大对称二叉树
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

typedef struct node{
    string con;
    int weight;
    node* left;
    node* right;
}node;

int mark = 1;

string dfs(node* root) {
    string ans;
    while(root->weight > 0) {
        ans += (char)(root->weight%10 -'0');
        root->weight /= 10;
    }
    if (root->left == nullptr && root->right == nullptr) {
        return ans;
    }
    else if (root->left != nullptr && root->right != nullptr) {
        string l = dfs(root->left);
        string r = dfs(root->right);
        if (l == r){
            int count = 2;
            for (int i = 0; i < l.length(); ++i) {
                if (l[i] == '-') count += 1;
            }
            mark = mark < count? count: mark;
            return ans + "-" + l; // "-"用来分层
        }
        else return "0"; // 代表非对称
    }
    else return "0";
}

int main() {
    int n;
    int l, r;
    cin >> n;
    node nd[n+1];
    for (int i = 1; i <= n; ++i) cin >> nd[i].weight;
    for (int i = 1; i <= n; ++i) {
        cin >> l >> r;
        if (l == -1) nd[i].left = nullptr;
        else nd[i].left = &nd[l];
        if (r == -1) nd[i].right = nullptr;
        else nd[i].right = &nd[r];
    }
    dfs(&nd[1]);
    int bass = 1;
    int ans = 0;
    for (int i = 0; i < mark; ++i) {
        ans += bass;
        bass *= 2;
    }
    cout << ans;
    return 0;
}