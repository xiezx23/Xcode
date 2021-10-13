/*************************************************************************
    > File Name: Breath_tarv_bitree.cpp
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2021-10-13
    
    @method: 递归分左右子树处理即可
    这里用了vector数组里分层实现广度优先遍历

    @from:matrix 6-4 二叉树广度优先遍历
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

vector<char> ans[30];

void dfs(string pre, string mid, int level) {
    if (pre.length() == 0) return;
    ans[level].push_back(pre[0]);
    int mark = 0;
    for (int i = 0; i < mid.length(); ++i) {
        if (mid[i] == pre[0]) {
            mark = i;
            break;
        }
    }
    //left tree
    dfs(pre.substr(1,mark),mid.substr(0,mark), level+1);
    //right tree
    dfs(pre.substr(1+mark,pre.length()-1-mark),mid.substr(1+mark,pre.length()-1-mark), level+1);
    return;
}

int main() {
    string pre, mid;
    cin >> pre >> mid;
    dfs(pre, mid, 0);
    for (auto v:ans)
    for (auto vv:v) cout << vv;
    return 0;
}