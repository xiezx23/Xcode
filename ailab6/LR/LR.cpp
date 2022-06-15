#include <bits/stdc++.h>
#include <pthread.h>
#include "LR.h"
using namespace std;


void LR::readData() {
    // 读入数据集 读入优化版
    freopen("C:/Users/xiezexi/Desktop/Xcode/ailab6/train.csv","r",stdin);
    float num;
    int idx = 1;
    data tmpData; 
    tmpData.vec[0] = 1;
    while(scanf("%f", &num) != EOF) {
        getchar();
        tmpData.vec[idx++] = num;
        if (idx == 41) {
            scanf("%d", &tmpData.label);
            dataSet.push_back(tmpData);
            idx  = 1;
        }
    }
    // cout << dataSet.size() << endl;
}

void LR::divideData() {
    // 划分数据集
    for (int i = 0; i < dataSet.size()*4/5; ++i) {
        idxOfTrain.push_back(i);
    }
    for (int i = dataSet.size()*4/5; i < dataSet.size(); ++i) {
        idxOfValid.push_back(i);
    }
}

inline float LR::lrFunct(float vec[N]) {
    // 计算预测标签
    float ans = 0;
    for (int i = 0; i < N; ++i) {
        ans += (vec[i] * w[i]);
    }
    ans = 1.0/(1.0+exp(-ans));
    return ans;
}


float LR::test() {
    int cnt = 0;
    for (auto idx: idxOfValid) {
        data& tmpData = dataSet[idx];
        float ans = lrFunct(tmpData.vec);
        int curLabel = 0;
        if (ans >= 0.5) curLabel = 1;
        if (curLabel == tmpData.label) {
            cnt ++;
        }
    }
    return ((float)cnt) / idxOfValid.size();
}

void LR::caculateLoss() {
    // float sum = 0;
    memset(delta_w, 0, sizeof(delta_w));
    for (auto idx: idxOfTrain) {
        data& tmpData = dataSet[idx];
        float ans = lrFunct(tmpData.vec);
        ans = tmpData.label - ans;
        for (int i = 0; i < N; ++i) {
            delta_w[i] += tmpData.vec[i]*ans;
        }
        // sum += abs(ans);
    }
    // cout << sum << endl;
}

void LR::updateW() {
    // 批量梯度下降更新
    for (int i = 0; i < N; ++i) {
        w[i] += eta * delta_w[i];
    }
}

int main() {
    clock_t start = clock();
    LR test;
    printf("start reading data\n");
    test.readData();
    test.divideData();
    printf("finish reading data, use time: %d ms\n", clock()-start);
    printf("start training data\n");
    start = clock();
    float bestRate = 0, curRate;
    int itTime = 10000;
    for (int i = 0; i < itTime; ++i) {
        test.caculateLoss();
        test.updateW();
        curRate = test.test();
        bestRate = max(bestRate, curRate);
        // printf("cur: %.5f   best: %.5f\n",curRate,bestRate);
        if (i % 2000 == 0) {
            test.eta = test.eta * 0.99;
        }
    }
    printf("number of iterations: %d \n", itTime);
    printf("finish training, best rate: %.5f  use time: %d ms\n",bestRate, clock() - start);
    return 0;
}