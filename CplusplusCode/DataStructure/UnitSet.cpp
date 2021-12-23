/*************************************************************************
    > File Name: UnitSet.cpp
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2021-11-8

    @data_structure: 并查集(带合并路径不带秩的一般并查集)
*************************************************************************/

#include <bits/stdc++.h>

using  namespace std;

int uset[10010];

inline void init() {
    for(int i = 0; i < 10010; ++i) {
        uset[i] = i;
    }
}

int find(int index) {
    if (uset[index] == index) return index;
    else {
        uset[index] = find(uset[index]); // 合并路径
        return uset[index];
    }
}

void merge(int x, int y) {
    uset[find(x)] = find(y);
}

string query(int x, int y) {
    if (find(x) == find(y)){
        return "Y";
    }
    else return "N";
}

int main() {
    int n, m, z, x, y;
    cin >> n >> m;
    init();
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &z,&x,&y);
        if (z == 1) {
            merge(x, y);
        }
        else cout << query(x, y) << endl;
    }
    return 0;
}