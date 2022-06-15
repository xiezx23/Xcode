/*************************************************************************
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2022 
************************************************************************/
#include <bits/stdc++.h>
#define ll long long
#define addfor(i, n) for (int i = 0; i < n; ++i)
#define subfor(i, n) for (int i = n-1; i >= 0; --i)

using namespace std;

int main(){
    int t, n, num;
    cin >> t;
    while (t--) {
        cin >> n;
        int mark = 1;
        vector<int> arr;
        for (int i = 0; i < n; ++i) {
            cin >> num;
            arr.push_back(num);
        }
        int topend = -1, nextend = 0, topstart, nextstart;
        if (n % 2 == 0) {
            mark = 0;
        }
        else while(1) {
            topstart = topend + 1;
            nextstart = nextend + 1;
            topend = nextend;
            for (int i = topend+1; ; ++i) {
                if (i + 2 == arr.size()) {
                    nextend = arr.size() -1;
                    break;
                }
                else {
                    if (arr[i] > arr[i+1]) {
                        nextend = i;
                        break;
                    }
                }
            }
            if ((nextend-nextstart+1)%2 == 1) {
                mark = 0;
                break;
            }
            for (int i = nextstart; i <= nextend;) {
                int pre = arr[i];
                while(arr[topstart] < pre) topstart += 1;
                if (topstart > topend) {
                    mark = 0;
                    break;
                }
                if (arr[i + 1] > arr[topstart]) {
                    if (topstart != topend) {
                        if (arr[i+1] < arr[topstart+1]) i += 2;
                        else {
                            mark = 0;
                            break;
                        }
                    }
                    else i += 2;
                }
                else {
                    mark = 0;
                    break;
                }
            }
            if (nextend == arr.size() -1 || mark == 0) break;
        }
        if (mark) cout << "YES\n";
        else cout << "NO\n";
    }
    
    return 0;
}

/*
5
2
10 5
3
1 4 7
3
5 3 2
3
10 4 23
5
10 6 20 5 8
*/