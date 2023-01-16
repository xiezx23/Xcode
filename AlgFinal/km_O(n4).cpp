// #include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
// #define sfor(i, start, n) for (int i = start; i < n; ++i)
// #define rfor(i, n, end) for (int i = n-1; i >= end; --i)
#define pr pair<int,int>
#define ll long long
using namespace std;

const int M = 100;
const int N = 100;
const int SIZE = 100;
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

// 相等子图Equality Graph
typedef struct EG {
private:
    // 货物(仓库)数量
    int size;
    // 右节点对应预分配的左节点，-1代表未分配
    int match[SIZE];
    // 每次寻找增广路径标记已访问右节点，每轮刷新
    int visited[SIZE];
    // edge[i][j] 1和0代表货物i和仓库j是否有边
    int edge[SIZE][SIZE];
    // 交错树左节点
    set<int> S;
    // 交错树右节点
    set<int> T;

public:
    // 根据规模构造子图
    void init(int s) {
        size = s;
    }

    // 断开全部边并清空配对
    void refresh() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                edge[i][j] = 0;
            }
        }
        memset(match, -1, sizeof(int)*size);
    }

    // 在货物i和仓库j建边
    void addEdge(int i, int j) {
        edge[i][j] = 1;
    }

    // 为货物i寻找增广路径并配对仓库
    bool findAndMatch(int i) {
        // 交错树新增左节点
        S.insert(i);
        for (int j = 0; j < size; ++j) {
            if (edge[i][j] && !visited[j]) {
                visited[j] = 1;
                // 交错树新增右节点
                T.insert(j);
                // 当仓库空闲或者仓库原配有额外空闲仓库时成功配对
                if (match[j] == -1 || findAndMatch(match[j])) {
                    match[j] = i;
                    return true;
                }
            }
        }
        return false;
    }

    // 匈牙利算法验证完美匹配
    bool Hungarian(set<int>& inS, set<int>& inT) {
        // 遍历左节点寻找增广路更新匹配
        for (int i = 0; i < size; ++i) {
            // 刷新访问标记和交错树
            memset(visited, 0, sizeof(int)*size);
            S.clear();
            T.clear();
            if (!findAndMatch(i)) {
                // 返回交错树
                inS = S;
                inT = T;
                return false;
            }
        }
        return true;
    }
}EG;

class solution {
private:
    int m, n, size; // 地图长、宽、仓库数
    char grid[M][N];
    vector <point> gPos; // 记录货物位置
    vector <point> wPos; // 记录仓库位置
    int w[SIZE][SIZE]; // 边权w[i][j]，代表货物i到仓库j的L1距离
    int gl[SIZE]; // 货物的可行顶标
    int wl[SIZE]; // 仓库的可行顶标
    EG eGraph; // 生成子图
public:
    // 读取输入数据
    void readGrid() {
        scanf("%d %d", &m, &n);
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
            int minY = INT32_MAX;
            for (int x = 0; x < size; ++x) {
                minY = min(minY, w[x][y]);
            }
            wl[y] = minY;
        }
    }

    // 根据当前可行顶标生成相等子图
    void createEqualityGraph() {
        eGraph.refresh();
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (gl[i] + wl[j] == w[i][j]) {
                    // 满足顶标条件，可建边
                    eGraph.addEdge(i, j);
                }
            }
        }
    }

    // 更新可行顶标
    void updateFeasibleLabel(set<int>& S, set<int>& T) {
        // 计算alpha
        int alpha = INT32_MAX;
        // for (auto x: S) {
        //     for (int y = 0; y < size; ++y) {
        //         if (T.count(y) == 0) {
        //             alpha = min(alpha, w[x][y] - gl[x] - wl[y]);
        //         }
        //     }
        // }
        for (set<int>::iterator x = S.begin(); x != S.end(); ++x) {
            for (int y = 0; y < size; ++y) {
                if (T.count(y) == 0) {
                    alpha = min(alpha, w[*x][y] - gl[*x] - wl[y]);
                }
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

    // KM算法求二分图最小完美匹配的总权重
    int Kuhn_Munkres() {
        // 交错树左节点
        set<int> S;
        // 交错树右节点
        set<int> T;
        // 初始化顶标
        initFeasibleLabel();
        for (;;) {
            // 根据顶标生成相等子图
            createEqualityGraph();
            // 在相等子图E上用匈牙利算法验证完美匹配
            if (eGraph.Hungarian(S, T)) {
                break;
            }
            // 更新可行顶标
            updateFeasibleLabel(S, T);
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
        eGraph.init(size);
        return Kuhn_Munkres();
    }
};

int main() {
    auto r_ptr = freopen(file_in, "r", stdin);
    /*****************************************/
    solution sl;
    cout << sl.solve();
    /*****************************************/
    fclose(r_ptr);
    return 0;
}