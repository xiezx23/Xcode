/*************************************************************************
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2022-5-2

    @data_structure: 线性筛模板
    @problem: 洛谷P3383 【模板】线性筛
*************************************************************************/
#include <bits/stdc++.h>
#define ll long long
#define addfor(i, n) for (int i = 0; i < n; ++i)
#define subfor(i, n) for (int i = n-1; i >= 0; --i)

using namespace std;

const int maxN = 100000010;
bitset <maxN> mark;
int primeSize = 0;
int prime[3000010];

void init() {
    for (int i = 0; i < maxN; ++i) {
        mark[i] = 0;
    }
}

int main(){
    init();
    ios::sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    for (int i = 2; i < n; ++i) {
        if (!mark[i]) {
            prime[primeSize++] = i;
        }
        for (int j = 0; j < primeSize && i*prime[j] < n; ++j) {
            mark[i*prime[j]] = 1;
            if (i%prime[j] == 0) break;
        }
    }
    while (q--) {
        int num;
        cin >> num;
        cout << prime[num-1] <<endl;
    }
    return 0;
}