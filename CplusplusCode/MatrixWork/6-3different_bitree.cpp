/*************************************************************************
    > File Name: diff_bitree.cpp
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2021-10-13
    
    @method: 观察规律发现当节点可以左右摇摆时产生多义，故只需找出摇摆节点数。
    摇摆节点的特点是前序遍历和后序遍历的逆这两个字符串的公共二位字串
    例如:  前序：A-B-C-D  后序：C-B-D-A
    故前序ABCD和后序逆ADBC的公共部分为BC，代表有一个摇摆节点

    @from:matrix 6-3 不同形态二叉树
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int ans = 1;
    string pre, aft;
    cin >> pre >> aft;
    char has[30] = {0};
    for (int i = 0; i < pre.length()-1; ++i) {
        has[pre[i]-'A'] = pre[i+1];
    }
    for (int i = aft.length()-1; i; --i) {
        if (aft[i-1] == has[aft[i]-'A']) ans*=2;
    }
    cout << ans;
    return 0;
}