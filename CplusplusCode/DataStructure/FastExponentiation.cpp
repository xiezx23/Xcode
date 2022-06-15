/*************************************************************************
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2022-5-2

    @data_structure: 快速幂模板
    @problem: 洛谷P1226 【模板】快速幂
*************************************************************************/
#include <bits/stdc++.h>
#define ll long long
#define addfor(i, n) for (int i = 0; i < n; ++i)
#define subfor(i, n) for (int i = n-1; i >= 0; --i)

using namespace std;

ll pow(int a, int b, int p) {
    if (b == 1) {
        return a;
    }
    ll tmp = pow(a, b>>1, p);
    tmp = tmp*tmp % p;
    if (b&1 == 1) {
        return a*tmp%p;
    }
    return tmp;
}

int main(){
    int a, b, p;
    cin >> a >> b >> p;
    cout << a << '^' << b << " mod " << p << "=";
    if (b == 0) {
        cout << a%p;
    }
    else cout << pow(a,b,p);
    return 0;
}