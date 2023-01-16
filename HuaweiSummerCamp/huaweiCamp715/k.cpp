#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main () {
    int n, m, k, num;
    scanf("%d%d%d", &n, &m, &k);
    // vector<int>  arr;
    int cnt[32] = {0};
    for (int i = 0; i < n; ++i) {
        scanf("%d", &num);
        for (int idx = 0; idx < 32 && num; ++idx) {
            cnt[idx] = num & 1;
            num >>= 1;
        }
    }
    pair<int,int> prArr[n];
    return 0;
}