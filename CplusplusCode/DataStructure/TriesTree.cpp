/*************************************************************************
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2022-5-2

    @data_structure: 字典树裸板
    @problem: 洛谷P8306 【模板】字典树
*************************************************************************/
#include <bits/stdc++.h>
#define ll long long
#define addfor(idx, n) for (int idx = 0; idx < n; ++idx)
#define subfor(idx, n) for (int idx = n-1; idx >= 0; --idx)


using namespace std;

typedef struct triesTreeNode {
    int count = 0; // 记录分支数
    unordered_map<char, triesTreeNode*> subNode;
}triesTreeNode;

void addStr(triesTreeNode* root, string& str) {
    triesTreeNode* curNode = root; 
    curNode->count += 1;
    for (int i = 0; i < str.size(); ++i) {
        if (curNode->subNode.count(str[i]-'0') == 0) {
            curNode->subNode[str[i]-'0'] = new(triesTreeNode);
        }
        curNode = curNode->subNode[str[i]-'0'];
        curNode->count += 1;
    }
}

int searchStr(triesTreeNode* root, string& str) {
    triesTreeNode* curNode = root; 
    for (int i = 0; i < str.size(); ++i) {
        if (curNode->subNode.count(str[i]-'0') == 0) {
            return 0;
        }
        curNode = curNode->subNode[str[i]-'0'];
    }
    return curNode->count;
}

void clean(triesTreeNode* curNode) {
    for (auto i: curNode->subNode) {
        clean(i.second);
    }
    delete(curNode);
}

int main(){
    int T, n, q;
    string str;
    std::ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> T;
    while(T--) {
        cin >> n >> q;
        triesTreeNode* root = new(triesTreeNode);
        addfor(idx, n) {
            cin >> str;
            addStr(root, str);
        }
        addfor(idx, q) {
            cin >> str;
            cout << searchStr(root, str) << endl;
        }
    }
    return 0;
}