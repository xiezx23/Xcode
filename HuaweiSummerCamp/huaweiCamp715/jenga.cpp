// https://codeforces.com/group/wmhDiB5PTN/contest/389412/problem/J
// 矩阵快速幂推演

#include <bits/stdc++.h>
using namespace std;

#define ll long long
typedef pair<int,int> pr;

const ll MOD = 1e9 + 7;

typedef struct mat{
    ll arr[8][8] {
        1,1,1,0,0,0,0,0,
        1,0,0,0,0,0,0,0,
        0,1,0,0,0,0,0,0,
        0,0,1,0,0,0,0,0,
        0,1,0,0,1,3,1,0,
        0,0,0,0,1,0,0,0,
        0,0,0,0,0,1,0,0,
        0,0,0,0,0,0,1,0
    };
    void init() {
        for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            this->arr[i][j] = i == j? 1: 0;
        }
    }
    void operator*= (const mat& another) {
        ll tmp[8][8];
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                ll num = 0;
                for (int idx = 0; idx < 8; ++idx) {
                    num += this->arr[i][idx] * another.arr[idx][j];
                    num %= MOD;
                }
                tmp[i][j] = num;
            }
        }
        for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            this->arr[i][j] = tmp[i][j];
        }
    }
}mat;

mat ansMat;

void ksm(ll cnt) {
    mat r;
    while(cnt) {
        if (cnt & 1) {
            ansMat *= r;
        }
        r *= r;
        cnt >>= 1;
    }
}


int main() {
    ll n;
    cin >> n;
    if (n == 1) {
        cout << 1;
        return 0;
    }
    else if (n == 2) {
        cout << 4;
        return 0;
    }
    ansMat.init();
    ksm(n-3);
    ll f[8] = {4,2,1,1,2,1,0,0};
    ll h[8] = {0};
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            h[i] += ansMat.arr[i][j] * f[j];
            h[i] %= MOD;
        }
    }
    ll ans = 2*h[1]%MOD + 2*h[2]%MOD + h[3] + 3*h[5]%MOD + 3*h[6]%MOD + h[7];
    ans %= MOD;
    cout << ans;
    return 0;
} 