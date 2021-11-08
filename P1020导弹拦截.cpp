/************************************************
    @method: 贪心 剪枝
    @level: 普及/提高-

    @difficult: 要求时间复杂度O(n logn), 只想出了O(n)的解法拿到100分,
    后来多搞了一个剪枝冲到150分, 看来还是不行。
    @time: 2021-11-01
*************************************************/
#include <bits/stdc++.h>
#define ll long long
#define addfor(i, n) for (int i = 0; i < n; ++i)
#define subfor(i, n) for (int i = n-1; i >= 0; --i)

using namespace std;

int num;
int arr[100010] = {0};
int size = 0;

int main(){
    while(scanf("%d",&num) != EOF) {
        arr[size++] = num;
    }
    int ans[size] = {0};
    int store[size] = {0}; //剪枝数组
    int maxans = 0;
    subfor(i, size) {
        int count = 1;
        int dp = 0;
        for (int j = i+1; j < size; ++j) {
            if (arr[i] >= arr[j]) {
                dp = max(dp, ans[j]);
                if (dp == store[j]) break; //剪枝
            }
        }
        ans[i] = count+dp;
        maxans = max(ans[i], maxans);
        store[i] = maxans; //剪枝预备
    }
    cout << maxans << endl;
    //处理多少套系统可以拦截全部导弹-贪心
    int setnum = 0;
    int missile = size;
    int startpoint = 0;
    while(missile) {
        int base = -1;
        for (int i = startpoint; i < size; ++i) {
            if (arr[i] == -1) continue;
            if (base == -1 || base >= arr[i]) {
                if (base == -1) startpoint = i+1;
                base = arr[i];
                missile -= 1;
                arr[i] = -1;
            }
        }
        setnum += 1;
    }
    cout << setnum;
    return 0;
}