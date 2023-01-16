#include <bits/stdc++.h>
#define ll long long

using namespace std;

string search(string a, string b, string ans, int cntA, int cntB) {
    if (cntA >= 2 || cntB >= 2) return "";
    for (int i = 0; i < a.size() + cntA; ++i) {
        if (a[i] != b[i]) {
            string a1, a2;
            if (i + 1 >= a.size()) a1 = "";
            else a1 = search(a.substr(i + 1, a.size() - i - 1), b.substr(i, b.size() - i), ans + a[i], cntA + 1, cntB);
            if (i + 1 >= b.size()) a2 = "";
            else a2 = search(a.substr(i, a.size() - i), b.substr(i + 1, b.size() -i - 1), ans + b[i], cntA, cntB + 1);
            if (a1.size() == 0 && a2.size() == 0) {
                return "";
            }
            else {
                ans = a1.size() > a2.size() ? a1 : a2;
                return ans;
            }
        }
        ans += a[i];
    }
    return ans;
}

int main () {
    string a, b;
    cin >> a >> b;
    if (a == b) {
        cout << a + 'a';
        return 0;
    }
    a += ' ';
    b += ' ';
    string ans = search(a, b, "", 0, 0);
    if (ans.size() == 0) cout << "IMPOSSIBLE";
    else cout << ans.substr(0, ans.size()-1);
    return 0;
}