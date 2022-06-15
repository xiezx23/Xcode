#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#define ll long long
#define MAXNUM 100010
using namespace std;

class Solution {
public:
    inline bool matchChar(char a, char b) {
        if (a == '.') return true;
        return (a==b);
    }
    string initPattern(string str) {
        char preChar = '0';
        int flag = 0, skip = 0;
        for (int i = 0; i < str.size(); ++i) {
            str[i-skip] = str[i];
            if (str[i] == preChar && flag) {
                skip++;
            }
            else {
                if (str[i] == '*') {
                    flag = 1;
                }
                else {
                    preChar = str[i];
                    flag = 0;
                }
            }
        }
        return str.substr(0, str.size()-skip);
    }
    bool isMatch(string s, string p) {
        s = s+"1";
        p = p+"1";
        p = initPattern(p);
        int sidx = 0, pidx = 0;
        char preChar = '%';
        for ( ; pidx < p.size() && sidx < s.size();) {
            if (p[pidx] == '*') {
                if (matchChar(preChar, s[sidx])) {
                    ++sidx;
                }
                else {
                    preChar = p[pidx];
                    ++pidx;
                }
            }
            else {
                if (!matchChar(p[pidx], s[sidx])) {
                    if (pidx+1 < p.size() && p[pidx+1] == '*') {
                        // 零次匹配
                        pidx ++;
                        return isMatch(s, p.substr(0, pidx-1)+p.substr(pidx+1, p.size()));
                    }
                    else {
                        return false;
                    }
                }
                else {
                    sidx++;
                }
                preChar = p[pidx];
                pidx ++;
            }
        }
        if (sidx < s.size()) return false;
        else if (pidx == p.size()) return true;
        else {
            string subP = p.substr(pidx, p.size());
            if (subP == "*1") return true;
            else return isMatch("01", subP);
        }
    }
};

int main() {
    Solution slt;
    string a, b;
    for (;;) {
        cin >> a >> b;
        cout << slt.isMatch(a, b) << endl;
    }
}