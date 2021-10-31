/************************************************
    @method: 回溯 深度优先搜索 动态规划
    @level: 普及+/提高
    
    @time: 2021-10-31 中山大学东校园公教楼
*************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define ll long long
#define addfor(i, n) for (int i = 0; i < n; ++i)
#define subfor(i, n) for (int i = n-1; i >= 0; --i)
#define MAXNUM 100
#define mod 80112002
using namespace std;

int maparr[9][9];
int move[2][2] = {1,0,0,1};
int ans = 0;
int size = 0;

int dp(){
    //在回溯中已经确定一条路径，对地图中取一条最大路径值返回
    //使用dp[i][j] += max(dp[i+1][j], dp[i][j+1])
    int d[size][size];
    d[size-1][size-1] = maparr[size-1][size-1];
    for(int i = size-2; i >= 0; --i) d[i][size-1] = d[i+1][size-1]+maparr[i][size-1];
    for(int i = size-2; i >= 0; --i) d[size-1][i] = d[size-1][i+1]+maparr[size-1][i];
    subfor(i, size-1)
    subfor(j, size-1) {
        d[i][j] = maparr[i][j] + max(d[i+1][j],d[i][j+1]);
    }
    return d[0][0];
}

void dfs(int x, int y, int val) {
    //回溯算法+深搜
    int mark = maparr[x][y];
    val += mark;
    maparr[x][y] = 0;
    if (x == size-1 && y == size-1) {
        int ans1 = val + dp();
        ans = max(ans, ans1);
    }
    else {
        if (x+1 < size) dfs(x+1, y, val);
        if (y+1 < size) dfs(x, y+1, val);
    }
    maparr[x][y] = mark;
}

void solution() {
    dfs(0,0,0);
}

int main() {
    cin >> size;
    addfor(i, size) {
        addfor(j, size) {
            maparr[i][j] = 0;
        }
    }
    int x, y, k;
    while(1) {
        scanf("%d%d%d",&x,&y,&k);
        if (x == 0 && y == 0 && k == 0) break;
        maparr[x-1][y-1] = k;
    }
    solution();
    cout << ans;
}