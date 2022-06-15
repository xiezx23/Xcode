#include <bits/stdc++.h>
#define ll long long
#define addfor(i, n) for (int i = 0; i < n; ++i)
#define subfor(i, n) for (int i = n-1; i >= 0; --i)

using namespace std;


int main() {
    int t, n, num;
    std::ios::sync_with_stdio(false);
    cin >> t;
    while(t--) {
        cin >> n;
        int sum = 0;
        while(n--) {
            cin >> num;
            sum = sum^num;
        }
        if (sum == 0) {
            cout << "No\n";
        }
        else {
            cout << "Yes\n";
        }
    }
}