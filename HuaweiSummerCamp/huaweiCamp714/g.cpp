#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n;
int v1, v2;
int sx, sy, tx, ty;

typedef struct point {
    double x, y;
    void init(int xx, int yy) {
        x = xx;
        y = yy;
    }
}point;

double loadTime[1005][1005];
double directToEnd;
point pt[1005];
int ptSize = 2;
// 0号点是start, 1号点是end

void cntTime (int a, int b) {
    double t;
    if (a == 0) {
        double aa = (pt[a].x - pt[b].x);
        double bb = (pt[a].y - pt[b].y);
        t = (sqrt(aa*aa + bb*bb)) / v1;
        loadTime[a][b] = t;
        loadTime[b][a] = t;
        if (b == 1) {
            directToEnd = t;
        }
    }
    else {
        double aa = (pt[a].x - pt[b].x);
        double bb = (pt[a].y - pt[b].y);
        double load = (sqrt(aa*aa + bb*bb));
        double v2Load = 3 * v2;
        if (load >= v2Load) {
            t = 3 + (load - v2Load) / v1;
        }
        else {
            t = load / v2;
        }
        loadTime[a][b] = t;
        loadTime[b][a] = t;
        // if (b == 1) {
        //     if (t >= directToEnd) {
        //         visited[a] = 1;
        //     }
        // }
    }
    return;
}

int main() {
    cin >> n;
    int inX, inY;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &inX, &inY);
        pt[ptSize].init(inX, inY);
        ptSize ++;
    }
    scanf("%d%d%d%d", &sx, &sy, &tx, &ty);
    scanf("%d%d", &v1, &v2);
    pt[0].init(sx, sy);
    pt[1].init(tx, ty);
    // 转换时间
    for (int i = 0; i < n + 2; ++i) {
        for (int j = i+1; j < n + 2; ++j) {
            cntTime(i, j);
        }
    }
    // // dijstra
    // priority_queue<pair<double, int>, vector<pair<double,int>>, greater<pair<double,int>>> pq;
    // pq.push(make_pair(0.0, 0));
    // vector<bool> visited(1005,false);
    // while(1) {
    //     pair<double, int> pr = pq.top();
    //     pq.pop();
    //     if (pr.second == 1) {
    //         printf("%.12lf",pr.first);
    //         break;
    //     }
    //     if (!visited[pr.second]) {
    //         visited[pr.second] = true;
    //         for (int i = 1; i < n + 2; ++i) {
    //             double newTime = pr.first + loadTime[pr.second][i];
    //             pq.push(make_pair(newTime, i));
    //         }
    //     }
    // }
    // dijstra
    priority_queue<pair<double, int>, vector<pair<double,int>>, greater<pair<double,int>>> pq;
    pq.push(make_pair(0.0, 0));
    vector<bool> visited(1005,false);
    while(1) {
        pair<double, int> pr = pq.top();
        pq.pop();
        if (pr.second == 1) {
            printf("%.12lf",pr.first);
            break;
        }
        if (visited[pr.second]) continue;
        visited[pr.second] = true;
        for (int i = 1; i < n + 2; ++i) {
            if (visited[i]) continue;
            double newTime = pr.first + loadTime[pr.second][i];
            pq.push(make_pair(newTime, i));
        }
    }
    return 0;
}