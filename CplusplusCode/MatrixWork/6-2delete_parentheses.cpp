/*************************************************************************
    > File Name: delete_parentheses.cpp
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2021-10-13

    @from:matrix 6-2 删除最少无效括号
************************************************************************/
#include <bits/stdc++.h>
#define ll long long

using namespace std;

set<string> ansStr;
int len = 0;
int num = 0;

void dfs(string origin, string curStr, int posi, int l, int r, int del) {
    if(posi == origin.size()){
        if (l==r) {
            ansStr.insert(curStr);
        }
        return;
    }
    if (origin[posi] == '(') {
        if (l+1 <= num)
            dfs(origin, curStr+origin[posi], posi+1, l+1, r, del);
        if (del+1 <= len)
            dfs(origin, curStr, posi+1, l, r, del+1);
    }
    else if (origin[posi] == ')') {
        if (l >= r+1 && r+1 <= num)
            dfs(origin, curStr+origin[posi], posi+1, l, r+1, del);
        if (del+1 <= len)
            dfs(origin, curStr, posi+1, l, r, del+1);
    }
    else {
        dfs(origin, curStr+origin[posi], posi+1, l, r, del);
    }
}

int main() {
    string str;
    cin >> str;
    int count = 0;
    int left = 0, right = 0;
    stack<char> st;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '(') {
            left += 1;
            st.push('(');
        }
        else if(str[i] == ')') {
            if (st.empty()) count += 1;
            else {
                st.pop();
                right += 1;
            }
        }
    }
    num = min(right, left);
    len = count + st.size();
    dfs(str, "", 0, 0, 0, 0);
    for (auto v: ansStr) cout << v << endl;
    return 0;
}

//leetcode 301

// class Solution {
// public:
//     void dfs(string origin, string curStr, int posi, int l, int r, int del) {
//         if(posi == origin.size()){
//             if (l==r) {
//                 ansStr.insert(curStr);
//             }
//             return;
//         }
//         if (origin[posi] == '(') {
//             if (l+1 <= num)
//                 dfs(origin, curStr+origin[posi], posi+1, l+1, r, del);
//             if (del+1 <= len)
//                 dfs(origin, curStr, posi+1, l, r, del+1);
//         }
//         else if (origin[posi] == ')') {
//             if (l >= r+1 && r+1 <= num)
//                 dfs(origin, curStr+origin[posi], posi+1, l, r+1, del);
//             if (del+1 <= len)
//                 dfs(origin, curStr, posi+1, l, r, del+1);
//         }
//         else {
//             dfs(origin, curStr+origin[posi], posi+1, l, r, del);
//         }
//     }
//     vector<string> removeInvalidParentheses(string s) {
//         string str;
//         cin >> str;
//         int count = 0;
//         int left = 0, right = 0;
//         stack<char> st;
//         for (int i = 0; i < str.size(); ++i) {
//             if (str[i] == '(') {
//                 left += 1;
//                 st.push('(');
//             }
//             else if(str[i] == ')') {
//                 if (st.empty()) count += 1;
//                 else {
//                     st.pop();
//                     right += 1;
//                 }
//             }
//         }
//         num = min(right, left);
//         len = count + st.size();
//         dfs(str, "", 0, 0, 0, 0);
//         vector<string> ans;
//         for (auto v: ansStr) ans.push_back(v);
//         return ans;
//     }
// private:
//     set<string> ansStr;
//     int len = 0;
//     int num = 0;
// };