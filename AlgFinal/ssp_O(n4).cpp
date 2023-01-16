// #include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define pr pair<int,int>
#define ll long long
using namespace std;

const int M = 100;
const int N = 100;
const int SIZE = 100;
const int INF = 2147483647;
const char* file_in = "C:/Users/xiezexi/Desktop/Xcode/AlgFinal/data.in";


typedef struct node {
	// 流量
	int f[2*SIZE + 10];
	// 单位费用
	int w[2*SIZE + 10];
	// 增广路中的前继节点
	int pre;
	// 增加一条连向to的边
	void addEdge(int to) {
		f[to] = 1;
	}
	// 删边
	void deleteEdge(int to) {
		f[to] = 0;
	}
    // 刷新
    void init(int num) {
        memset(f, 0, sizeof(int)*num);
        memset(w, 0, sizeof(int)*num);
    }
}node;

// 目标位置信息
typedef struct point {
    int x, y;
    point(int xx, int yy) {
        x = xx;
        y = yy;
    }
}point;

// 计算曼哈顿距离
int getL1distance(point& a, point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

class solution {
private:
    int m, n, size; // 地图长、宽、仓库数
    char grid[M][N];
    vector <point> gPos; // 记录货物位置
    vector <point> wPos; // 记录仓库位置
	node nd[2*SIZE + 10]; // 费用流节点
	int sIdx; // 源的下标
	int tIdx;	  // 汇的下标
	int nodeNum;  // 节点数
	int dis[2*SIZE + 10]; // 距离数组


public:
    // 读取输入数据
    void readGrid() {
        scanf("%d %d", &m, &n);
        if (m == 0) exit(0);
        getchar();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = getchar();
            }
            getchar();
        }
    }

    // 获取货物和仓库位置
    void getPosition() {
        gPos.clear();
        wPos.clear();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'W') {
                    wPos.push_back(point(i, j));
                }
                else if (grid[i][j] == 'G') {
                    gPos.push_back(point(i, j));
                }
            }
        }
        size = wPos.size();
    }

	// 建立带权边
	void buildEdge(int f, int t, int w) {
		nd[f].addEdge(t);
		nd[f].w[t] = w;
		nd[t].w[f] = -w; // 反边单位费用
	}

	// 建图，初始化边权
	void initFlow() {
		// 0号点为源点，2n + 1号点为汇点 (n为仓库数)
		sIdx = 0;
		tIdx = 2*size + 1;
		nodeNum = tIdx + 1;
		// 左节点为1~n，右节点为n+1~2n
        for (int idx = 0; idx < nodeNum; ++idx) nd[idx].init(nodeNum);

		for (int i = 1; i <= size; ++i) nd[sIdx].addEdge(i);
		for (int j = size+1; j <= 2*size; ++j) nd[j].addEdge(tIdx);
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				int w = getL1distance(gPos[i], wPos[j]);
				buildEdge(i+1, j+size+1, w);
			}
		}
	}

	// 初始化距离数组
	void initDistance() {
		dis[sIdx] = 0;
		for (int i = 1; i < nodeNum; ++i) dis[i] = INF;
	}

	// SPFA算法求最小费用增广路
	int SPFA() {
		// 队列优化的Bellman-Ford算法
        bool vis[2*SIZE + 2] = {0};
		queue<int> q;
		q.push(sIdx); vis[sIdx] = 1;
		initDistance();
		while(q.size()) {
			int curNode = q.front();
            vis[curNode] = 0;
			q.pop();
			for (int to = 0; to < nodeNum; ++to) {
				// curNode和to之间有边 且 可以减少到to的dis
				if (nd[curNode].f[to] && dis[curNode] + nd[curNode].w[to] < dis[to]) {
					dis[to] = dis[curNode] + nd[curNode].w[to];
					nd[to].pre = curNode; // 记录前继点
					if (!vis[to]) {
                        q.push(to); // 更新点入队
                        vis[to] = 1;
                    }
				}
			}
		}
		return dis[tIdx];
	}

	// 更新费用流
	void updateFlow() {
		// 利用前继点从汇点回溯得到增广路，并更新边流量
		int curNode = tIdx;
		while(curNode != sIdx) {
			int preNode = nd[curNode].pre;
			// 建反边
			nd[curNode].addEdge(preNode);
			// 删原边
			nd[preNode].deleteEdge(curNode);
			curNode = preNode;
		}
	}

	int MCMF() {
		int ret = 0;
		for (int i = 0; i < size; ++i) {
			ret += SPFA();
			updateFlow();
		}
		return ret;
	}


    int solve() {
        // 读图
        readGrid();
        // 提取GW位置
        getPosition();
        // 初始化费用流
		initFlow();

        return MCMF();
    }
};

int main() {
    auto r_ptr = freopen(file_in, "r", stdin);
    /*****************************************/
	while(1) {
		solution sl;
		cout << sl.solve() << endl;
	}
    /*****************************************/
    // fclose(r_ptr);
    return 0;
}