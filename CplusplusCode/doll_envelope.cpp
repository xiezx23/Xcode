/*************************************************************************
    > File Name: doll_envelope.cpp
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2021-09-29
    @method:
    1、先按长宽又小到大排序 O(N*logN)
    2、动态规划由小到大枚举右边界 O(N*N)
    
    @from:matrix 5-4 套娃信封
************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct node{
    int a;
    int b;
}node;

int cmp (const void* a, const void* b) {
    node* a1 = (node*)a;
    node* b1 = (node*)b;
    if (a1->a == b1->a){
        return a1->b - b1->b;
    }
    return a1->a - b1->a;
}
int main(){
    int n;
    cin >> n;
    node l[n];
    for (int i = 0; i < n; ++i) cin >> l[i].a >> l[i].b;
    qsort(l, n, sizeof(node), cmp);
    vector<int> ans(n, 1);
    for (int i = 1; i < n; ++i)
    for (int j = 0; j < i; ++j) {
        if (l[i].b > l[j].b && l[i].a > l[j].a) {
            ans[i] = max(ans[i],ans[j] + 1);
        }
    }
    cout << *max_element(ans.begin(),ans.end());
    return 0;
}
