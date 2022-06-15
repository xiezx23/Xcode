// 链式前向星模板
#include <bits/stdc++.h>

#define maxNum 10000

using namespace std;

typedef struct node {
    int to;
    int next = -1;
    int val;
}node;

int head[maxNum];
node narr[maxNum];
int cnt = 0;

void init() {
    memset(head, -1, sizeof(head));
}

void add(int u, int v, int w) {
    // 建双边
    narr[cnt].to = v;
    narr[cnt].val = w;
    narr[cnt].next = head[u];
    head[u] = cnt++;
    narr[cnt].to = u;
    narr[cnt].val = w;
    narr[cnt].next = head[v];
    head[v] = cnt++;
}

int findEdge(int u, int v) {
    int curTo = head[u];
    while(curTo != -1) {
        if (narr[curTo].to == v) {
            cout << "反边：" << narr[curTo^1].val << " 正边";
            return narr[curTo].val;
        }
        else {
            curTo = narr[curTo].next;
        }
    }
    return -1;
}

int main () {
    init();
    int n, u, v, w;
    cout << "输入边数：";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> u >> v >> w;
        add(u,v,w);
    }
    while(1) {
        cin >> u >> v;
        cout << findEdge(u,v) << endl;
    }
    return 0;
}