/************************************************
    @method: 递归
    @level: 普及-

    @time: 2021-11-01
*************************************************/
// #include <bits/stdc++.h>
#include <iostream>
#define ll long long
#define addfor(i, n) for (int i = 0; i < n; ++i)
#define subfor(i, n) for (int i = n-1; i >= 0; --i)

using namespace std;

string solution(int num) {
    int hm[20] = {0};
    int mark = 0;
    while(num) {
        if (num&1) {
            hm[mark] = 1;
            num -= 1;
        }
        num = num/2;
        mark += 1;
    }
    string ans = "";
    for (int i = 19; i >= 0; --i) {
        if (hm[i]) {
            if (ans == "")  {
                if (i == 0) ans += "2(0)";
                else if (i == 1) ans += "2";
                else if (i == 2) ans += "2(2)";
                else ans += "2("+solution(i)+")";
            }
            else {
                if (i == 0) ans += "+2(0)";
                else if (i == 1) ans += "+2";
                else if (i == 2) ans += "+2(2)";
                else ans += "+2("+solution(i)+")";
            }
        }
    }
    return ans;
}

int main(){
    int n;
    cin >> n;
    cout << solution(n);
    return 0;
}