#ifndef LR_H
#define LR_H

# include <bits/stdc++.h>
#define N 41
using namespace std;

typedef struct data {
    float vec[N];
    int label;
}data;

float w[N] = {0}; // 权重向量
float delta_w[N] = {0};

class LR {
private:
    vector<data> dataSet;
    vector<int> idxOfTrain, idxOfValid;

public:
    float eta = 3;     // 学习率
    LR() {
        for (int i = 0; i < N; ++i) {
            w[i] = ((float)(rand()%200 - 100))/100;
        }
    }
    void readData();
    void divideData();
    void updateW();
    void caculateLoss();
    float lrFunct(float vec[N]);
    float test();
};

#endif