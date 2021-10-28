/*************************************************************************
    > File Name: put_eggs.cpp
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2021-10-25
    

    @from:matrix 8-3 放鸡蛋
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

void show(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d",*arr);
        arr += 1;
    }
    printf("\n");
}

int main() {
    int t;
    scanf("%d",&t);
    while(t--) {
        int n, m;
        scanf("%d%d",&n,&m);//n eggs and m baskets
        int ans[m+1] = {0};
        ans[0] = n;
        show(ans,m);
        while (1) {
            int skip = 0;
            int lowIndex = -1;
            for (int j = m-1; j > 0; --j) {
                skip += ans[j-1] - ans[j];
                if (skip != 0 && lowIndex == -1) lowIndex = j;
                if (skip >= 2) {
                    ans[j-1] -= 1;
                    ans[lowIndex] += 1;
                }
            }
            if (skip < 2) break;
            else show(ans,m);
        }
    }
    return 0;
}