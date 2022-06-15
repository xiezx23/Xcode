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

typedef struct{
	int x;
	int y;
	int d;
}node;

int n, m;
int ufset[1001];

void init() {
	for (int i = 0; i < n; ++i) {
		ufset[i] = i;
	}
}

bool cmp(node a, node b) {
	return a.d > b.d;
}

int find(int i) {
	if (ufset[i] != i) {
		ufset[i] = find(ufset[i]);
	}
	return ufset[i];
}

int main(){
	int t;
	cin >> t;
	while(t--) {
		int ans = 0;
		int x, y, d;
		vector<node> arr;
		cin >> n >> m;
		init();
		for (int i = 0; i < m; ++i) {
			cin >> x >> y >> d;
			node tmp = {x,y,d};
			arr.push_back(tmp);
		}
		sort(arr.begin(), arr.end(), cmp);
		for (auto i : arr) {
			if (find(i.x) != find(i.y)) {
				ans += i.d;
				ufset[find(i.x)] = find(i.y);
			}
		}
		cout << ans << endl;
	}
	return 0;
}
