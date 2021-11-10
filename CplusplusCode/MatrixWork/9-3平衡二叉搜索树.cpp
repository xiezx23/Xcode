#include <bits/stdc++.h>
#define ll long long
using namespace std;

int mark = 1;

int high(int* arr, int left, int right) {
    int base = arr[left];
    int mid = right+1;
    if (left == right) return 1;
    else if (left > right) return 0;
    for (int i = left+1; i <= right; ++i) {
        if (arr[i] > base) {
            mid = i;
            break;
        }
    }
    int lh = high(arr, left+1, mid-1);
    int rh = high(arr, mid, right);
    if (abs(lh - rh) > 1) mark = 0;
    return max(lh, rh)+1;
}

void solution(int* arr, int& size) {
    high(arr, 0, size-1);
}

int main() {
    int t, n;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        cin >> n;
        int* arr = new int[n];
        for(int j = 0; j < n; ++j) {
            scanf("%d",&arr[j]);
        }
        mark = 1;
        solution(arr, n);
        if (mark) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}