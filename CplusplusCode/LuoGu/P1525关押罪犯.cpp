/************************************************
    @method: 并查集
    @level: 普及+/提高

    @time: 2021-11-08
*************************************************/
#include <bits/stdc++.h>
#define ll long long
#define addfor(i, n) for (int i = 0; i < n; ++i)
#define subfor(i, n) for (int i = n-1; i >= 0; --i)

using namespace std;

int uset[20010]; //普通并查集
int f[20010] = {0}; //f[i]表示不跟i同个牢房的集合的某个元素

typedef struct node{
    int a,b;
    int val;
}node;
node arr[100010];

int cmp(const void* a, const void* b) {
    node* aa = (node*)a;
    node* bb = (node*)b;
    return bb->val - aa->val;
}

int find(int p) {
    if (uset[p] == p) return p;
    else {
        uset[p] = find(uset[p]);
        return uset[p];
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    addfor(i, m) {
        scanf("%d%d%d",&arr[i].a,&arr[i].b,&arr[i].val);
    }
    qsort(arr, m, sizeof(node), cmp);
    addfor(i, n) {
        uset[i+1] = i+1;
    }
    addfor(i, m) {
        if (find(arr[i].a) == find(arr[i].b)) {
            cout << arr[i].val;
            return 0;
        }
        else {
            if (f[arr[i].a] == 0){
                f[arr[i].a] = arr[i].b;
            }
            else {
                uset[find(arr[i].b)] = find(f[arr[i].a]);
            }
            if (f[arr[i].b] == 0){
                f[arr[i].b] = arr[i].a;
            }
            else {
                uset[find(arr[i].a)] = find(f[arr[i].b]);
            }
        }
    }
    cout << 0;
    return 0;
}