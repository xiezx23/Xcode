/*************************************************************************
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2022-5-24

    @data_structure: 网络流模板
    @problem: 洛谷P3376 【模板】网络流
*************************************************************************/

#include <bits/stdc++.h>
#define INFTY INT_MAX
using namespace std;
typedef long long ll;
typedef struct {
    ll val;
    int to;
    int next;
    void setPara(int v, ll w, int nx) {
        to = v;
        val = w;
        next = nx;
    }
}node;

int cnt = 0;
int head[520010];
node edge[520010];
int global_s, global_t; // 源和汇

void init() {
    memset(head, -1, sizeof(head));
}

void add(int u, int v, ll w) {
    edge[cnt].setPara(v, w, head[u]);
    head[u] = cnt++;
    // 建反向边
    edge[cnt].setPara(u, 0, head[v]);
    head[v] = cnt++;
}

void read() {
    int flag[2510][2510];
    for (int i = 0; i < 2510; ++i) {
        memset(flag[i], 0, sizeof(int)*2510);
    }
    int n,m,u,v;
    ll w;
    scanf("%d %d %d %d", &n, &m, &global_s, &global_t);
    while(m--) {
        scanf("%d%d%lld", &u, &v, &w);
        if (flag[u][v] == 0) {
            flag[u][v] = cnt;
            flag[v][u] = cnt+1;
            add(u,v,w);
        } else {
            edge[flag[u][v]].val += w;
        }
    }
}

void changeCapacity(int u, int v, ll num) {
// 正向边权减少num， 反向增加num
    int curTo = head[u];
    while(curTo != -1) {
        node tmp = edge[curTo];
        if (tmp.to == v) {
            edge[curTo].val -= num;
            edge[curTo^1].val += num; // 反边
            return;
        }
        else {
            curTo = tmp.next;
        }
    }
}

ll findAugment() {
    bitset<520010> visit;
    int preNode[520010] = {0}; 
    ll maxCurFlow = 0;
    int tailNode = 0;
    queue<pair<int,ll>> q; q.push(make_pair(global_s, INFTY));
    pair<int,ll> tmp;
    visit[global_s] = 1;
    bool flag = true;
    while(flag) {
        int qSize = q.size();
        if (qSize == 0) break;
        while(qSize--) {
            tmp = q.front(); q.pop();
            if (tmp.first == global_t) {
                // maxCurFlow = max(tmp.second, maxCurFlow);
                if (tmp.second > maxCurFlow) {
                    tailNode = tmp.first;
                    maxCurFlow = tmp.second;
                }
                flag = false;
            }
            else {
                int curTo = head[tmp.first];
                while(curTo != -1) {
                    node tmpNode = edge[curTo];
                    if (!visit[tmpNode.to]) {
                        if (tmpNode.val > 0) {
                            visit[tmpNode.to] = 1;
                            q.push(make_pair(tmpNode.to, min(tmp.second, tmpNode.val)));
                            preNode[tmpNode.to] = tmp.first; // 记录路径前点
                        }
                    }
                    curTo = tmpNode.next;
                }
            }
        }
    }
    if (maxCurFlow == 0) {
        return 0;
    }
    // 根据路径修改边权
    int pre = preNode[global_t], nex = global_t;
    while(pre != global_s) {
        changeCapacity(pre, nex, maxCurFlow);
        nex = pre;
        pre = preNode[pre];
    }
    changeCapacity(pre, nex, maxCurFlow);
    return maxCurFlow;
}

void solve() {
    ll maxFlow = 0;
    ll ret = 1;
    while(ret) {
        ret = findAugment();
        maxFlow += ret;
    }
    printf("%lld\n", maxFlow);
}

int main() {
    init();
    read();
    solve();
}