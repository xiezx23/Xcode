/************************************************
    @method: 结构体搜索
    @level: 普及-

    @time: 2021-10-31 中东公教
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

typedef struct node{
    int a, b;
    int g, k;
}node;

int main () {
    int n, a, b, g, k;
    cin >> n;
    node arr[n];
    addfor(i, n) {
        scanf("%d%d%d%d",&a,&b,&g,&k);
        arr[i].a = a;
        arr[i].b = b;
        arr[i].g = g;
        arr[i].k = k;
    }
    int x, y;
    scanf("%d%d",&x,&y);
    subfor(i, n) {
        if (arr[i].a <= x && arr[i].a+arr[i].g >= x) {
            if (arr[i].b <= y && arr[i].b+arr[i].k >= y){
                printf("%d\n",i+1);
                return 0;
            }
        }
    }
    cout << "-1";
    return 0;
}