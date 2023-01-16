// #include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#define pr pair<int,int>
#define ll long long
using namespace std;

const int M = 100;
const int N = 100;
const int SIZE = 100;
const int INF = 2147483647;
const char* file_in = "C:/Users/xiezexi/Desktop/Xcode/AlgFinal/data.in";

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
    int w[SIZE][SIZE]; // 边权w[i][j]，代表货物i到仓库j的L1距离
    int gl[SIZE]; // 货物的可行顶标
    int wl[SIZE]; // 仓库的可行顶标
    
    // 右节点对应预分配的左节点，-1代表未分配
    int match[SIZE];
    // 每次寻找增广路径标记已访问右节点，每轮刷新
    int visited[SIZE];
    // 交错树左节点
    set<int> S;
    // 交错树右节点
    set<int> T;
    // 松弛变量
    int slack[SIZE];

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

    // 计算边权矩阵w[i][j]，代表货物i到仓库j的L1距离
    void cntEdgeWeight() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                w[i][j] = getL1distance(gPos[i], wPos[j]);
            }
        }
    }

    // 初始化可行顶标
    void initFeasibleLabel() {
        memset(gl, 0, sizeof(int)*size);
        for (int y = 0; y < size; ++y) {
            int minY = INF;
            for (int x = 0; x < size; ++x) {
                minY = min(minY, w[x][y]);
            }
            wl[y] = minY;
        }
    }

    // 更新可行顶标 复杂度O(n)
    void updateFeasibleLabel() {
        // 计算alpha
        int alpha = INF;
        for (int y = 0; y < size; ++y) {
            if (T.count(y) == 0) {
                alpha = min(alpha, slack[y]);
            }
        }
        // 计算新一组顶标
        for (int idx = 0; idx < size; ++idx) {
            if (S.count(idx)) {
                gl[idx] += alpha;
            }
            if (T.count(idx)) {
                wl[idx] -= alpha;
            }
            else {
                // 对于T'中的点,slack值会减少alpha (l(x)增大)
                slack[idx] -= alpha;
            }
        }
    }

    // 计算可行顶标和
    int labelSum() {
        int ret = 0;
        for (int idx = 0; idx < size; ++idx) {
            ret += gl[idx] + wl[idx];
        }
        return ret;
    }

    // 为货物i寻找增广路径并配对仓库
    bool findAndMatch(int i) {
        // 交错树新增左节点
        S.insert(i);
        for (int j = 0; j < size; ++j) {
            int gap = w[i][j] - gl[i] - wl[j];
            if (!gap && !visited[j]) {
                // 是可行边且右节点未访问
                visited[j] = 1;
                // 交错树新增右节点
                T.insert(j);
                // 当仓库空闲或者仓库原配有额外空闲仓库时成功配对
                if (match[j] == -1 || findAndMatch(match[j])) {
                    match[j] = i;
                    return true;
                }
            }
            else {
                // 此时该边非可行边，那么j是T'，更新slack
                slack[j] = min(slack[j], gap);
            }
        }
        return false;
    }

    // KM算法求二分图最小完美匹配的总权重
    int Kuhn_Munkres() {
        // 初始化顶标
        initFeasibleLabel();
        // 刷新匹配
        memset(match, -1, sizeof(int)*size);
        // 遍历左节点寻找增广路更新匹配
        for (int i = 0; i < size; ++i) {
            // 刷新slack
            for (int j = 0; j < size; ++j) slack[j] = INF;
            // 最多循环n次
            while(1) {
                 // 刷新访问标记和交错树
                memset(visited, 0, sizeof(int)*size);
                S.clear();
                T.clear();
                if (findAndMatch(i)) {
                    break;
                }
                // 更新可行顶标
                updateFeasibleLabel();
            }
        }
        return labelSum();
    }

    int solve() {
        // 读图
        readGrid();
        // 提取GW位置
        getPosition();
        // 计算边权
        cntEdgeWeight();
        return Kuhn_Munkres();
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