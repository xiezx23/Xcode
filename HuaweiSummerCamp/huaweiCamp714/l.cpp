#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, num;
    cin >> n;
    vector <int> arr;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &num);
        arr.push_back(num);
    }
    sort(arr.begin(), arr.end());
    int curAveIdx = 0;
    int maxCnt = 0;
    long long preSum = arr[0];
    for (int i = 1; i < arr.size(); ++i) {
        preSum += arr[i];
        int average = preSum / (i+1);
        while(arr[curAveIdx] <= average) curAveIdx++;
        maxCnt = max(maxCnt, i - curAveIdx + 1);
    }
    cout << maxCnt;
    return 0;
}