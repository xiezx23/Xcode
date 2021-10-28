#include <bits/stdc++.h>
using namespace std;

int n[15]; //放置输入数
int f[15][2][10]; //计算每posi,limit,highNum下的答案
int g[15][2][10][10]; //记录每posi,limit,highNum下当该位置数为i时的答案
int vis[15][2][10]; //记录搜索

void dp(int posi, int limit, int highNum){
    if (vis[posi][limit][highNum]==0) vis[posi][limit][highNum] = 1;
    else return;
    //初始化
    for (int i = 0; i < 10; ++i){
        g[posi][limit][highNum][i] = 0;
    }
    f[posi][limit][highNum] = 0;
    //处理尾数
    if (posi == 0) {
        if (highNum != 0){
            int l = 9;
            if (limit == 1){
                l = n[posi];
            }
            for (int i = 0;i<=l; ++i) {
                if (abs(i-highNum)>2) {
                    g[0][limit][highNum][i] = 1;
                }
            }
        }
        return;
    }
    //正常处理
    int lim = limit? n[posi]: 9, h = highNum, l;
    for (int i = 0; i <= lim; ++i) {
        if (highNum == 0){
            h = i;
        }
        l = limit&&(i==n[posi])? 1: 0;
        int lim2 = l? n[posi-1]: 9;
        dp(posi-1, l, h);
        for (int j = 0; j <= lim2; ++j) {
            if (abs(i-j)<=7 || (i==0&&highNum==0))
                g[posi][limit][highNum][i] += g[posi-1][l][h][j];
        }
        f[posi][limit][highNum] += g[posi][limit][highNum][i];
    }
    return;
}

int solution(int num){
    int size = 0;
    while(num){
        n[size++] = num%10;
        num /= 10;
    }
    for(int i = 0; i < size; ++i)
    for(int j = 0; j < 2; ++j)
    for(int h = 0; h < 10; ++h){
        vis[i][j][h] = 0;
    }
    dp(size-1, 1, 0);
    //cout << f[size-1][1][0] << endl;
    return f[size-1][1][0];
}

int main() {
    int x, y;
    cin >> x >> y;
    cout << solution(y)-solution(x-1) << endl;
    return 0;
}