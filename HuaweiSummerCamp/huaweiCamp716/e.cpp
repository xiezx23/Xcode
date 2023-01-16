#include <bits/stdc++.h>
#define ll long long
#define addfor(i, n) for (int i = 0; i < n; ++i)
#define subfor(i, n) for (int i = n-1; i >= 0; --i)
#define readInt(i) scanf("%d",&i)
#define readLL(i) scanf("%lld",&i)
using namespace std;

int t;
ll k, l, r;
bool preRecord = true;

ll dp[130][2];
ll maxNum[130][2];
ll minNum[130][2];
bool vi[130][2];
int length = 0;
ll botton[130] = {0};
ll up[130] = {0};

void digitDp(int curIdx, int isLimit) {
    if (curIdx == length) return;
    if (vi[curIdx][isLimit]) return;
    vi[curIdx][isLimit] = true;
    ll beginNum = botton[curIdx], endNum = up[curIdx];
    digitDp(curIdx + 1, 1);
    digitDp(curIdx + 1, 0);
    if (isLimit) {
        dp[curIdx][1] = dp[curIdx+1][1] + endNum + 1;
        maxNum[curIdx][1] = maxNum[curIdx+1][1] * k + endNum;
        minNum[curIdx][1] = minNum[curIdx+1][1] * k + endNum;
        if (beginNum < endNum || preRecord) {
            preRecord = true;
            ll tmp = dp[curIdx + 1][1] + endNum;
            if (curIdx == length-1) {
                if (endNum - 1 == 0) {
                    tmp -= 1;
                }
            }
            dp[curIdx][0] = tmp;
            maxNum[curIdx][0] = maxNum[curIdx+1][1] * k + endNum - 1;
            minNum[curIdx][0] = minNum[curIdx+1][1] * k + endNum - 1;
        }
        else {
            dp[curIdx][0] = -1;
        }
    }
    else {
        if (dp[curIdx+1][0] != -1) {
            ll tmp = dp[curIdx+1][0] + k;
            if (dp[curIdx][0] == tmp) {
                maxNum[curIdx][0] = max(maxNum[curIdx][0], maxNum[curIdx+1][0] * k + k - 1);
                minNum[curIdx][0] = min(minNum[curIdx][0], minNum[curIdx+1][0] * k + k - 1);
            }
            else if (dp[curIdx][0] < tmp) {
                dp[curIdx][0] = tmp;
                maxNum[curIdx][0] = maxNum[curIdx+1][0] * k + k - 1;
                minNum[curIdx][0] = minNum[curIdx+1][0] * k + k - 1;
            }
        }
    }
    return ;
}

void solve() {
    preRecord = true;
    ll tmpL = l, tmpR = r;
    int tp = 0;
    for (int i = 0; i < 130; ++i) {
        dp[i][0] = dp[i][1] = 0;
        up[i] = 0;
        botton[i] = 0;
        vi[i][0] = vi[i][1] = false;
        maxNum[i][0] = 0;
        maxNum[i][1] = 0;
        minNum[i][0] = LONG_LONG_MAX;
        minNum[i][1] = LONG_LONG_MAX;
    }
    while(tmpL) {
        botton[tp++] = tmpL % k;
        tmpL /= k;
    }
    tp = 0;
    while(tmpR) {
        up[tp++] = tmpR % k;
        tmpR /= k;
    }
    length = tp;
    dp[length][0] = -1;
    minNum[length][0] = minNum[length][1] = 0;
    digitDp(0, 1);
    digitDp(0, 0);
}

int main () {
    freopen("C:\\Users\\xiezexi\\Desktop\\Xcode\\c.in", "r", stdin);
    readInt(t);
    int cnt = 0;
    while(t--) {
        readLL(k);
        readLL(l);
        readLL(r);
        cnt ++;
        solve();
        ll m, a, b;
        if (dp[0][0] > dp[0][1]) {
            m = dp[0][0] - 2;
            a = maxNum[0][0];
            b = minNum[0][0];
        }
        else  if (dp[0][0] == dp[0][1]) {
            m = dp[0][1] - 2;
            a = max(maxNum[0][0],maxNum[0][1]);
            b = min(minNum[0][0],minNum[0][1]);
        }
        else {
            m = dp[0][1] - 2;
            a = maxNum[0][1];
            b = minNum[0][1];
        }
        printf("Case #%d: ", cnt);
        printf("%lld %lld %lld\n", m, b, a);
    }
    return 0;
}