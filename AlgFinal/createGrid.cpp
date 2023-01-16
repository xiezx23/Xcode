#include <bits/stdc++.h>
#define sfor(i, start, n) for (int i = start; i < n; ++i)
#define rfor(i, n, end) for (int i = n-1; i >= end; --i)
#define pr pair<int,int>
#define ll long long

using namespace std;
/* standard input
7 8
...W....
...W....
...W....
GGGWGGGG
...W....
...W....
...W....
*/

void output() {
    int m = rand() % 96 + 5;
    int n = rand() % 96 + 5;
    printf("%d %d\n", m, n);
    char grid[m][n];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = '.';
        }
    }
    int num = min(m*n/3, rand()%100+1);
    for (int i = 0; i < num; ++i) {
        int x = rand() % m;
        int y = rand() % n;
        while (grid[x][y] != '.') {
            x = rand() % m;
            y = rand() % n;
        }
        grid[x][y] = 'W';
    }
    for (int i = 0; i < num; ++i) {
        int x = rand() % m;
        int y = rand() % n;
        while (grid[x][y] != '.') {
            x = rand() % m;
            y = rand() % n;
        }
        grid[x][y] = 'G';
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));
    freopen("C:/Users/xiezexi/Desktop/Xcode/AlgFinal/data.in","w",stdout);
    int n = 20;
    while(n--) {
        output();
    }
    cout << "0 0";
    return 0;
}