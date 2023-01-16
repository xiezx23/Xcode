#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    int l,r;
    while(q--) {
        scanf("%d%d", &l,&r);
        l -= 1; r -= 1;
        bool checkGood = true;
        for (; l < r;) {
            if (s[l] != s[r]) {
                checkGood = false;
                break;
            }
            l ++;
            r --;
        }
        if (checkGood) {
            cout << "Budada\n";
        }
        else {
            int cnt = r - l + 1;
            if (cnt & 1 == 1) {
                cout << "Putata\n";
            }
            else {
                cout << "Budada\n";
            }
        }
    }
    return 0;
}