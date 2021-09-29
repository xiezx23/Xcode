/*************************************************************************
    > File Name: the_kth_arrange.cpp
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2021-09-29
    @method: 通过列表可发现规律：
    1、在差值(k-1)是A(n,n)的k倍时，倒数第n+1位就向上进k位
    2、由高到低不断对A(n,n)取余，逐位确定该位排列
    
    @from:matrix 5-5 第k个排列
************************************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    int n, k;
    cin >> n >> k;
    int hash[n+1] = {0};
    int num = 1;
    k -= 1;
    for (int i = 2; i < n; ++i) num *= i;
    for (int i = n - 1; i; --i) {
        if (k >= num) {
            int t = k/num;
            k = k%num;
            int count = 0;
            for (int j = 1; j <= n; ++j) {
                if (hash[j] == 0){
                    count += 1;
                }
                if (count == t + 1) {
                    hash[j] = 1;
                    cout << j;
                    break;
                }
            }
        }
        else {
            for (int j = 1; j <= n; ++j) {
                if (hash[j] == 0) {
                    hash[j] = 1;
                    cout << j;
                    break;
                }
            }
        }
        num /= i;
    }
    for (int j = 1; j <= n; ++j) {
        if (hash[j] == 0) {
            hash[j] = 1;
            cout << j;
            break;
        }
    }
    return 0;
}
