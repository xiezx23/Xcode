#include <bits/stdc++.h>
#define ll long long
#define addfor(i, n) for (int i = 0; i < n; ++i)
#define subfor(i, n) for (int i = n-1; i >= 0; --i)

using namespace std;

int main(){
    int n;
    int m;
    cin >> n;
    for (int ni = 0; ni < n; ++ni) {
        cin >> m;
        int arr[m];
        for (int i = 0; i < m; ++i) {
            scanf("%d",&arr[i]);
        }
        int jumpTime = 0;
        int start = 0, end = 0;
        while(1) {
            int nextend = end;
            for (int i = start; i <= end; ++i) {
                nextend = max(nextend, i+arr[i]);
            }
            if (nextend >= m-1) {
                cout << jumpTime + 1 << endl;
                break;
            }
            else {
                jumpTime += 1;
                start = end;
                end = nextend;
            }
        }
    }
    return 0;
}
