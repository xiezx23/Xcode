#include <bits/stdc++.h>

using namespace std;

int n, m;
int arr[500000];
set<int> doubleSolution;

int& getIdx(int x, int y) {
    return arr[x*(m+2) + y];
}

int main() {
    int num;
    cin >> n >> m;
    int badIdx, preNum = 0;
    int globalBadIdx = -1;
    for (int i = 0; i < n; ++i) {
        getIdx(i, 0) = 0;
        getIdx(i, m+1) = 1e9 + 7;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &num);
            getIdx(i, j) = num;

        }
    }
    for (int i = 0; i < n; ++i) {
        badIdx = -1;
        preNum = getIdx(i, 1);
        for (int j = 2; j <= m; ++j) {
            num = getIdx(i, j);
            if (num < preNum) {
                if (badIdx == -1)
                    badIdx = j;
                else {
                    cout << "0 0";
                    return 0;
                }
            }
            preNum = num;
        }
        if(badIdx != -1) {
            if (getIdx(i, badIdx-1) > getIdx(i, badIdx+1)) {
                badIdx -= 1;
                doubleSolution.clear();
            }
            // else if (getIdx(i, badIdx-1) == getIdx(i, badIdx+1)) {
            //     // 双解
            //     if (i == 0 || globalBadIdx == -1) {
            //         doubleSolution.insert(badIdx);
            //         doubleSolution.insert(badIdx-1);
            //         globalBadIdx = badIdx;
            //     }
            //     else {
            //         if (doubleSolution.count(badIdx) && doubleSolution.count(badIdx-1)) {
            //             // ok
            //             globalBadIdx = badIdx;
            //         }
            //         else {
            //             doubleSolution.clear();
            //             if (badIdx == globalBadIdx || badIdx-1 == globalBadIdx) {
            //                 badIdx = globalBadIdx;
            //             }
            //             else {
            //                 cout << "0 0";
            //                 return 0;
            //             }
            //         }
            //     }
            // }
            else {
                doubleSolution.clear();
            }
            if (doubleSolution.size() != 2) {
                if (globalBadIdx == -1) globalBadIdx = badIdx;
                else {
                    if (badIdx == -1) continue;
                    else {
                        if (badIdx != globalBadIdx) {
                            cout << "0 0";
                            return 0;
                        }
                    }
                }
            }
        }
    }
    if (globalBadIdx == -1) {
        cout << "1 1";
        return 0;
    }
    else {
        if (doubleSolution.size() == 2) {
            for (auto g: doubleSolution) {
                globalBadIdx = g;
                int globalL = -1, globalR = m+1;
                bool flag = true;
                for (int i = 0; i < n; ++i) {
                    int base = getIdx(i, globalBadIdx);
                    getIdx(i, globalBadIdx) = getIdx(i, globalBadIdx-1);
                    // 确定右边界
                    int* ridx = upper_bound(&getIdx(i, 0), &getIdx(i, m+1), base);
                    int r = ridx- &getIdx(i, 0);
                    if (r > globalBadIdx) {
                        r -= 1;
                    }
                    // 确定左边界
                    int l;
                    for (int idx = r; idx >= 0;--idx) {
                        if (getIdx(i, idx) < base) {
                            l = idx;
                            break;
                        }
                    }
                    if (l < globalBadIdx) {
                        l += 1;
                    }
                    globalL = max(globalL, l);
                    globalR = min(globalR, r);
                    if (globalR < globalL) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    cout << globalBadIdx << " " << globalL ;
                    return 0;
                }
            }
            cout << "0 0";
            return 0;
        }
        else {
            int globalL = -1, globalR = m+1;
            for (int i = 0; i < n; ++i) {
                int base = getIdx(i, globalBadIdx);
                getIdx(i, globalBadIdx) = getIdx(i, globalBadIdx-1);
                // 确定右边界
                int* ridx = upper_bound(&getIdx(i, 0), &getIdx(i, m+1), base);
                int r = ridx- &getIdx(i, 0);
                if (r > globalBadIdx) {
                    r -= 1;
                }
                // 确定左边界
                int l;
                for (int idx = r; ;--idx) {
                    if (getIdx(i, idx) < base) {
                        l = idx;
                        break;
                    }
                }
                if (l < globalBadIdx) {
                    l += 1;
                }
                globalL = max(globalL, l);
                globalR = min(globalR, r);
                if (globalR < globalL) {
                    cout << "0 0";
                    return 0;
                }
            }
            cout << globalBadIdx << " " << globalL ;
            return 0;
        }
    }
    return 0;
}