#ifndef BPNN_H
#define BPNN_H

# include <bits/stdc++.h>
#define N 40
using namespace std;

typedef struct data {
    float vec[N];
    int label;
}data;  // 数据集的数据单位

vector<data> dataSet;               //存放数据集
vector<int> idxOfTrain, idxOfValid; //记录训练集和验证集的数据集内下标

typedef struct node {
    int nextLayer_size; // 下层节点个数
    float* w;           // 链接下层节点边权
    float* delta_w;     // 更新梯度
    float bias;         // 神经元激活偏置
    float delta_bias;	// 更新偏置梯度
    float in;           // 神经元输入值
    float out;          // 神经元输出
    float Err;          // 误差部分偏导
    void init(int nl_size){
        nextLayer_size = nl_size;
        w = (float*)malloc(sizeof(float)*nl_size);
        delta_w = (float*)malloc(sizeof(float)*nl_size);
        for (int i = 0;i < nl_size; ++i) {
            w[i] = ((float)(rand()%200 - 100))/100;
        }
        bias = ((float)(rand()%200 - 100))/100;
    }
    void clearDelta() {
        memset(delta_w, 0, sizeof(float)*nextLayer_size);
        delta_bias = 0;
    }
    ~node() {
        free(w);
        free(delta_w);
    }
}node;  // 神经节点

class BPNN {
private:
    float learningRate;
    node* inputLayer;
    int hiddenLayer_size;
    node* hiddenLayer;
    node outputLayer;
    vector<data> errorPoint;

public:
    BPNN(float lr = 1, int hl_size = 3) {
        learningRate = lr;
        hiddenLayer_size = hl_size;
        // 构建输入层
        inputLayer = new node[N];
        for (int i = 0; i < N; ++i) {
            inputLayer[i].init(hl_size);
        }
        // 构建隐藏层
        hiddenLayer = new node[hl_size];
        for (int i = 0; i < hl_size; ++i) {
            hiddenLayer[i].init(1);
        }
        // 构建输出层
        outputLayer.init(0);
    }
    ~BPNN() {
        delete(inputLayer);
        delete(hiddenLayer);
    }
    void readData();            // 数据集读入
    void divideData();          // 数据集划分
    void forwardCalc(data&);    // 正向计算
    void backProp();            // 反向传播
    void clearInRecord();       // 清除节点正向数据
    void clearDeltaRecord();    // 清除节点梯度记录
    void update();              // 梯度更新
    float training(int);        // 训练
    float test();               // 测试当前验证集总误差
};

#endif