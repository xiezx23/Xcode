#include <bits/stdc++.h>
#include <pthread.h>
#include <time.h>
#include "PLA.h"
using namespace std;


void PLA::readData() {
    /// 读入数据集 读入优化版
    freopen("C:/Users/xiezexi/Desktop/Xcode/ailab6/train.csv","r",stdin);
    float num;
    int idx = 0;
    data tmpData;
    while(scanf("%f", &num) != EOF) {
        getchar();
        tmpData.vec[idx++] = num;
        if (idx == 40) {
            scanf("%d", &tmpData.label);
            if (tmpData.label == 0) tmpData.label = -1;
            dataSet.push_back(tmpData);
            idx  = 0;
        }
    }
    // cout << dataSet.size() << endl;
}

void PLA::divideData() {
    // 划分数据集
    for (int i = 0; i < dataSet.size()*4/5; ++i) {
        idxOfTrain.push_back(i);
    }
    for (int i = dataSet.size()*4/5; i < dataSet.size(); ++i) {
        idxOfValid.push_back(i);
    }
}


float plaFunct(float vec[N]) {
    // 计算预测标签
    float ans = b;
    for (int i = 0; i < 40; ++i) {
        float tmp = (vec[i] * w[i]);
        ans += tmp;
    }
    return ans;
}

// void* para_fct1(void* arg) {
//     int curLabel = 0;
//     float* sumLoss = new float;
//     for (int i = 0; i < idxOfTrain.size() / 2; ++i) {
//         int idx = idxOfTrain[i];
//         data& tmpData = dataSet[idx];
//         float ans = plaFunct(tmpData.vec);
//         curLabel = ans > 0 ? 1: -1;
//         if (curLabel != tmpData.label) {
//             // 误差点写入点集
//             errorPoint.push_back(make_pair(idx, tmpData.label));
//             sumLoss[0] -=  tmpData.label * ans;
//         }
//     }
//     return sumLoss;
// }

// void* para_fct2(void* arg) {
//     int curLabel = 0;
//     float* sumLoss = new float;
//     for (int i = idxOfTrain.size() / 2; i < idxOfTrain.size(); ++i) {
//         int idx = idxOfTrain[i];
//         data& tmpData = dataSet[idx];
//         float ans = plaFunct(tmpData.vec);
//         curLabel = ans > 0 ? 1: -1;
//         if (curLabel != tmpData.label) {
//             // 误差点写入点集
//             errorPoint2.push_back(make_pair(idx, tmpData.label));
//             sumLoss[0] -=  tmpData.label * ans;
//         }
//     }
//     return sumLoss;
// }

// float PLA::caculateLoss_PARALLEL() {
//     // 并行处理误差点的计算
//     errorPoint.clear();
//     errorPoint2.clear();
//     float sumLoss = 0;
//     pthread_t tid1 = 1, tid2 = 2;
//     pthread_create(&tid1, NULL, para_fct1, NULL);
//     pthread_create(&tid2, NULL, para_fct2, NULL);
//     void* getRet;
//     pthread_join(tid1, &getRet);
//     sumLoss += ((float*)getRet)[0];
//     delete((float*)getRet);
//     pthread_join(tid2, &getRet);
//     sumLoss += ((float*)getRet)[0];
//     delete((float*)getRet);
//     return sumLoss;
// }

float PLA::caculateLoss() {
    errorPoint.clear();
    int curLabel = 0;
    float sumLoss = 0;
    for (auto idx: idxOfTrain) {
        data& tmpData = dataSet[idx];
        float ans = plaFunct(tmpData.vec);
        curLabel = ans > 0 ? 1: -1;
        if (curLabel != tmpData.label) {
            // 误差点写入点集
            errorPoint.push_back(make_pair(idx, tmpData.label));
            sumLoss -=  tmpData.label * ans;
        }
    }
    // cout << (double)errorPoint.size() / idxOfTrain.size() << endl;
    return sumLoss;
}

float PLA::test() {
    // 计算在验证集的正确率
    int curLabel = 0, correctNum = 0;
    for (auto idx: idxOfValid) {
        data& tmpData = dataSet[idx];
        float ans = plaFunct(tmpData.vec);
        curLabel = ans > 0 ? 1: -1;
        if (curLabel == tmpData.label) {
            correctNum ++;
        }
    }
    return (float)correctNum / idxOfValid.size();
}


void PLA::updateW() {
    // 从误差点集中随机选点修正w和b
    // for (auto i: errorPoint2) errorPoint.push_back(i);
    int errorSize = errorPoint.size();
    pair<int,int> pr = errorPoint[rand() % errorSize];
    int idx = pr.first, label = pr.second;
    for (int i = 0; i < N; ++i) {
        // w[i] += step * dataSet[idx].vec[i];
        w[i] += label * dataSet[idx].vec[i];
    }
    b += label;
}

inline void printLine() {
    printf("*********************\n");
}

int main() {
    clock_t start = clock();
    PLA test;
    printf("start reading data\n");
    test.readData();
    test.divideData();
    printf("finish reading data, use time: %d ms\n", clock()-start);printLine();
    printf("start training data\n");
    start = clock();
    float bestRate = 0, curRate;
    int itTime = 60000;
    for (int i = 0; i < itTime; ++i) {
        test.caculateLoss();
        curRate = test.test();
        bestRate = max(bestRate, curRate);
        // printf("cur: %.5f   best: %.5f\n",curRate,bestRate);
        // test.caculateLoss_PARALLEL();
        test.updateW();
    }
    printf("number of iterations: %d \n", itTime);
    printf("finish training, best rate: %.5f  use time: %d ms\n",bestRate, clock() - start);
    return 0;
}





// void* para_fct1(void* arg) {
//     float* arr = (float*)arg;
//     int left = 0, right = 20;
//     float* ans = new float(0);
//     for (int i = 0; i < 20; ++i) {
//         ans[0] += (arr[i] * w[i]);
//     }
//     return ans;
// }

// void* para_fct2(void* arg) {
//     float* arr = (float*)arg;
//     float* ans = new float(0);
//     for (int i = 20; i < N; ++i) {
//         ans[0] += (arr[i] * w[i]);
//     }
//     return ans;
// }

// float PLA::plaFunct(float vec[N]) {
//     // 并行计算预测标签
//     float ans = b;
//     pthread_t tid1 = 1, tid2 = 2;
//     pthread_create(&tid1, NULL, para_fct1, vec);
//     pthread_create(&tid2, NULL, para_fct2, vec);
//     void* getRet;
//     pthread_join(tid1, &getRet);
//     ans += ((float*)getRet)[0];
//     free((float*)getRet);
//     pthread_join(tid2, &getRet);
//     ans += ((float*)getRet)[0];
//     free((float*)getRet);
//     return ans;
// }