/************************************************
    @method: 记忆化搜索
    @level: 普及/提高-
    
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

typedef struct node
{
    int num;
    vector<node*> in;
    vector<node*> out;
    node() {num = -1;}
}node;

node arr[5001];

ll dfs(node* n){
    ll ans = 0;
    if (n->num != -1) return n->num;
    if (n->out.size() == 0) return 1;
    else {
        for (auto i: n->out) {
            ans += dfs(i);
            ans %= mod;
        }
    }
    n->num = ans;
    return ans;
}

int main() {
    int n, m;
    int x,y;
    scanf("%d%d",&n,&m);
    addfor(i, m){
        scanf("%d%d",&x,&y);
        arr[x].out.push_back(&arr[y]);
        arr[y].in.push_back(&arr[x]);
    }
    ll ans = 0;
    for (auto i: arr) {
        if (i.in.size() == 0 && i.out.size() != 0) {
            ans += dfs(&i);
            ans %= mod;
        }
    }
    cout << ans;
    return 0;
}