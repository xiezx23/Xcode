#include <bits/stdc++.h>

using namespace std;

int main () {
    int n, m, x;
    cin >> n >> m >> x;
    int ans = 0, num;
    while(n--) {
        scanf("%d", &num);
        if (num >= x) ans ++;
    }
    while(m--) {
        scanf("%d", &num);
        if (num <= x) ans ++;
    }
    cout << ans;
    return 0;
}