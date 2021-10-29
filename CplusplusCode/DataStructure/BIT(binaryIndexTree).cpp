/*************************************************************************
    > File Name: BIT.cpp
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2021-10-26

    @data_structure: 区间修改加区间查询的树状数组
    @time_complexity: O(m*log n)
    @problem: 洛谷线段树1
*************************************************************************/

// #include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#define ll long long
#define MAXNUM 100010
using namespace std;

ll bit[MAXNUM] = {0}; //单点差分数组
ll ibit[MAXNUM] = {0};//点差分值*修改位置下标
int length;

inline int lowbit(int num) {return num&(-num);}

void add(int posi, int val) {
    for (int i = posi; i <= length; i+=lowbit(i)) {
        bit[i] += val;
        ibit[i] += val*posi;
    }
}

void update(int l, int r, int val) {
    add(l, val);
    add(r+1, -val);
}

ll presum(int posi) {
    ll sum = 0;
    for (int i = posi; i > 0; i-=lowbit(i)) {
        sum += (posi+1)*bit[i] - ibit[i];
    }
    return sum;
}

ll query(int a, int b) {
    return presum(b) - presum(a-1);
}

int main() {
    int m, op, l, r, k;
    cin >> length >> m;
    for (int i = 1; i <= length; ++i) {
        int n;
        scanf("%d",&n);
        update(i, i, n);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            scanf("%d",&k);
            update(l, r, k);
        }
        else {
            printf("%lld\n", query(l, r));
        }
    }
    return 0;
}