#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while(t--) {
        int a, b;
        cin >> a >> b;
        int x = b - a;
        if (x == 0) {
            cout << 0 << endl;
        }
        else if (x > 0) {
            if (x & 1 == 1) {
                cout << 1 << endl;
            }
            else {
                x >>= 1;
                if (x & 1 == 1) 
                    cout << 2 << endl;
                else cout << 3 << endl;
            }
        }
        else {
            x = -x;
            if (x & 1 == 1) {
                cout << 2 <<endl;
            }
            else cout << 1<< endl;
        }
    }
    return 0;
}