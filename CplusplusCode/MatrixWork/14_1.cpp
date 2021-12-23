/*************************************************************************
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2021 
************************************************************************/
#include <bits/stdc++.h>
#define ll long long
#define addfor(i, n) for (int i = 0; i < n; ++i)
#define subfor(i, n) for (int i = n-1; i >= 0; --i)


using namespace std;

typedef struct node{
    int length = -1;
    int food = 0;
    vector<node*> eaten;
}node;

int ans = 0;

void dfs(node* root) {
    if (root->eaten.size() == 0) {
        ans += 1;
    }
    else {
        for (auto i: root->eaten) {
            dfs(i);
        }
    }
}

int main(){
    static int n, m;
    cin >> n >> m;
    node arr[n+1];
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d",&a,&b);
        arr[a].eaten.push_back(&arr[b]);
        arr[b].food = 1;
    }
    //solution
    for (int i = 1; i <= n; ++i) {
        if (arr[i].food == 0) {
            dfs(&arr[i]);
        }
    }
    cout << ans;
    return 0;
}
