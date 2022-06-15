/************************************************
	@method: 动态规划
	@level: 普及/提高-

	@time: 2022-6-6
*************************************************/
#include <bits/stdc++.h>
#define ll long long
#define addfor(i, n) for (int i = 0; i < n; ++i)
#define subfor(i, n) for (int i = n-1; i >= 0; --i)

using namespace std;

int h[100010];
int hLen = 0;

int main(){
	register int in;
	while(scanf("%d",&in) != EOF) {
		h[hLen++] = in;
	}
	// question 1: 这套系统最多能拦截的导弹数->最长非增子序列
	int dp[hLen+1]; dp[hLen] = 100000;
	for (int i = 0; i < hLen; ++i) dp[i] = 50005;
	for (int i = 0; i < hLen; ++i) {
		*upper_bound(dp, dp+hLen, 50000-h[i]) = 50000-h[i];
	}
	int ans1 = 0;
	while(dp[ans1] < 50005) {
		ans1++;
	}
	printf("%d\n", ans1);
	// question 2: 最少要几套系统能拦截全部导弹->最长单增子列
	for (int i = 0; i < hLen; ++i) dp[i] = 50005;
	for (int i = 0; i < hLen; ++i) {
		*lower_bound(dp, dp+hLen, h[i]) = h[i];
	}
	int ans2 = 0;
	while(dp[ans2] < 50005) {
		ans2++;
	}
	printf("%d", ans2);
	return 0;
}