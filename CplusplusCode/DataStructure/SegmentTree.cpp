/*************************************************************************
    > File Name: BIT.cpp
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2021-10-26

    @data_structure: 区间修改加区间查询的线段树
    @time_complexity: O(log n)的修改和查询
    @problem: 洛谷 [模板]线段树1
*************************************************************************/

#include <bits/stdc++.h>
#define ll long long
#define maxnum 100010
using namespace std;

ll tree[maxnum<<2];
ll mark[maxnum<<3] = {0};
ll num[maxnum];

void build(int l, int r, int p) {
    if (l == r){
        tree[p] = num[l];
    }
    else {
        build(l, (l+r)/2, 2*p);
        build((l+r)/2+1, r, 2*p+1);
        tree[p] = tree[2*p] + tree[2*p+1];
    }
}

void update(int p, int l, int r, int al, int ar, ll val) {
    if (r < al || l > ar) return;
    else if(l >= al && r <= ar) {
        tree[p] += (r-l+1)*val;
        mark[2*p] += val;
        mark[2*p+1] += val;
    }
    else {
        tree[p] += (min(ar,r)-max(al,l)+1)*val;
        int mid = l + ((r-l)>>1);
        update(2*p, l, mid, al, ar, val);
        update(2*p+1, mid+1, r, al, ar, val);
    }
}

ll query(int p, int l, int r, int al, int ar) {
    if (r < al || l > ar) return 0;
    else if (l >= al && r <= ar)  {
        tree[p] += mark[p]*(r-l+1);
        mark[2*p] += mark[p];
        mark[2*p+1] += mark[p];
        mark[p] = 0;
        return tree[p];
    }
    else {
        tree[p] += mark[p]*(r-l+1);
        mark[2*p] += mark[p];
        mark[2*p+1] += mark[p];
        mark[p] = 0;
        int mid = l + ((r-l)>>1);
        return query(2*p, l, mid, al, ar)+query(2*p+1, mid+1, r,al, ar);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        scanf("%lld",&num[i]);
    }
    build(1,n,1);
    for(int i = 0; i < m; ++i) {
        int op, x, y;
        ll k;
        scanf("%d%d%d",&op,&x,&y);
        if(op == 2) cout << query(1,1,n,x,y) << endl;
        else {
            scanf("%lld",&k);
            update(1,1,n,x,y,k);
        }
    }
    return 0;
}