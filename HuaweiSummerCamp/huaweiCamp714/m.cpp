#include <bits/stdc++.h>

using namespace std;

int matrix[10][10] = {
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,0,0,1,1,1,1,
    1,1,1,0,0,0,0,1,1,1,
    1,1,1,0,0,0,0,1,1,1,
    1,1,1,1,0,0,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1
};

int oriMap[1005][1005];
int preSum[1005][1005];
int n, m;

int count(int start_x, int start_y) {
    int up, lf, ul;
    bool flag = false;
    if (start_x == 0) {
        flag = true;
        up = 0;
    }
    else up = preSum[start_x - 1][start_y + 9];
    if (start_y == 0) {
        flag = true;
        lf = 0;
    }
    else lf = preSum[start_x + 9][start_y-1];
    if (flag) ul = 0;
    else {
        ul = preSum[start_x - 1][start_y - 1];
    }
    return preSum[start_x + 9][start_y + 9] + ul - up -lf;
}

int main () {
    cin >> n >> m;
    string s;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        for (int j = 0; j < m; ++j) {
            if (s[j] == '#') oriMap[i][j] = 1;
            else oriMap[i][j] = 0;
        }
    }
    int preRecord = 0;
    for (int j = 0; j < m; ++j) {
        preRecord += oriMap[0][j];
        preSum[0][j] = preRecord;
    }
    preRecord = oriMap[0][0];
    for (int i = 1; i < n; ++i) {
        preRecord += oriMap[i][0];
        preSum[i][0] = preRecord;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            preSum[i][j] = oriMap[i][j] + preSum[i-1][j] + preSum[i][j-1] - preSum[i-1][j-1];
        }
    }
    // 比对中间块
    set<pair<int,int>> recordPosi;
    for (int i = 0; i <= n - 10; ++i) {
        for (int j = 0; j <= m - 10; ++j) {
            // cout << count(i,j) << endl;
            if (count(i, j) == 88) {
                // check
                bool checkGood = true;
                for (int x = i; x < i + 10; ++x) {
                    for (int y = j; y < j + 10; ++y) {
                        if (oriMap[x][y] != matrix[x-i][y-j]) {
                            checkGood = false;
                            break;
                        }
                    }
                }
                if (checkGood) {
                    recordPosi.insert(make_pair(i+5, j+5));
                }
            }
        }
    }
    int typeCcnt = 0, typeScnt = 0;
    for (auto p: recordPosi) {
        // cout << p.first << ' ' << p.second << endl;
        int x = p.first, y = p.second;
        if (recordPosi.count(make_pair(x + 7, y))) {
            typeCcnt ++;
            recordPosi.erase(make_pair(x + 7, y));
            p.first = -1000;
            continue;
        }
        else if (recordPosi.count(make_pair(x - 7, y))) {
            typeCcnt ++;
            recordPosi.erase(make_pair(x - 7, y));
            p.first = -1000;
            continue;
        }
        else if (recordPosi.count(make_pair(x, y + 7))) {
            typeCcnt ++;
            recordPosi.erase(make_pair(x, y + 7));
            p.first = -1000;
            continue;
        }
        else if (recordPosi.count(make_pair(x, y - 7))) {
            typeCcnt ++;
            recordPosi.erase(make_pair(x, y - 7));
            p.first = -1000;
            continue;
        }
        else {
            typeScnt ++;
        }
    }
    cout << typeCcnt << " " << typeScnt;
    return 0;
}