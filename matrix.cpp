#include <bits/stdc++.h>

using namespace std;

typedef struct{
    int a,b;
}node;

node arr[100000];
int mark[1000001] = {0};
int n;
int maxl = 0;

bool cmp(node a, node b) {
    return a.a < b.a;
}


int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        scanf("%d %d",&arr[i].a,&arr[i].b);
        maxl =  max(maxl, arr[i].a);
    }
    sort(arr, arr+n, cmp);
    int head = 0;
    for (int i = 0; i < n; ++i) {
        int end = arr[i].a;
        for (; head < end; ++head) {

        }
    }
    int mm = INT_MAX;
    for (int i = 0; i < n; ++i) {
        mark[i] += (n-i-1);
        mm = min(mm, mark[i]);
    }
    cout << mm+1;
    return 0;
}