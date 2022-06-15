#ifndef PLA_H
#define PLA_H

# include <bits/stdc++.h>
#define N 40
using namespace std;

typedef struct data {
    float vec[N];
    int label;
}data;

float w[N] = {0}; // 权重向量
float b = 1;      // 偏置
vector<data> dataSet;
vector<int> idxOfTrain, idxOfValid;

vector<pair<int,int>> errorPoint;
vector<pair<int,int>> errorPoint2;


float plaFunct(float vec[N]);

class PLA {
private:
    int step = 1;     // 学习率

public:
    void readData();
    void divideData();
    void updateW();
    float caculateLoss();
    float test();
    float caculateLoss_PARALLEL();
};

#endif