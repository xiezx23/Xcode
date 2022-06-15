#include <bits/stdc++.h>
#include <pthread.h>
#include <time.h>
#include "BPNN.h"
using namespace std;


// void BPNN::readData() {
//     // 读入数据集
//     std::ios::sync_with_stdio(0);
//     // freopen("C:/Users/xiezexi/Desktop/Xcode/ailab6/train.csv","r",stdin);
//     ifstream inFile("C:/Users/xiezexi/Desktop/Xcode/ailab6/train.csv", ios::in);
//     float num;
//     int idx = 0;
//     data tmpData;
//     string getLine;
//     char c;
//     while(getline(inFile, getLine)) {
//         stringstream sstream(getLine);
//         while(sstream >> num >> c) {
//                 tmpData.vec[idx++] = num;
//                 if (idx == 40) {
//                     sstream >> tmpData.label;
//                     dataSet.push_back(tmpData);
//                     idx  = 0;
//                 }
//         }
//     }
//     cout << dataSet.size() << endl;
// }


void BPNN::readData() {
    // 读入数据集 读入优化版
    freopen("C:/Users/xiezexi/Desktop/Xcode/ailab6/train.csv","r",stdin);
    float num;
    int idx = 0;
    data tmpData;
    while(scanf("%f", &num) != EOF) {
        getchar();
        tmpData.vec[idx++] = num;
        if (idx == 40) {
            scanf("%d", &tmpData.label);
            dataSet.push_back(tmpData);
            idx  = 0;
        }
    }
    // cout << dataSet.size() << endl;
}

void BPNN::divideData() {
    // 划分数据集
    for (int i = 0; i < dataSet.size()*4/5; ++i) {
        idxOfTrain.push_back(i);
    }
    for (int i = dataSet.size()*4/5; i < dataSet.size(); ++i) {
        idxOfValid.push_back(i);
    }
}

void BPNN::clearInRecord() {
    // 清除隐藏层数据
    for (int i = 0; i < hiddenLayer_size; ++i) {
        hiddenLayer[i].in = hiddenLayer[i].bias;
    }
    // 清除输出层数据
    outputLayer.in = outputLayer.bias;
}

void BPNN::clearDeltaRecord() {
    // 清除隐藏层数据
    for (int i = 0; i < hiddenLayer_size; ++i) {
        hiddenLayer[i].clearDelta();
    }
    // 清除输出层数据
    outputLayer.clearDelta();
}

inline float f(float in) {
    // sigmiod 激活
    return 1/(1 + exp(-in));
}

void BPNN::forwardCalc(data& cur_data) {
    // 正向计算
    clearInRecord();
    // 输入层到隐藏层
    for (int i = 0; i < N; ++i) {
        node& curInputNote = inputLayer[i];
        curInputNote.out = cur_data.vec[i]; // 输入层不需激活
        for (int j = 0; j < hiddenLayer_size; ++j) {
            hiddenLayer[j].in += curInputNote.out * curInputNote.w[j];
        }
    }
    // 隐藏层激活后传递到输出层
    for (int i = 0; i < hiddenLayer_size; ++i) {
        node& curHiddenNode = hiddenLayer[i];
        curHiddenNode.out = f(curHiddenNode.in); // 激活
        outputLayer.in += curHiddenNode.out * curHiddenNode.w[0];
    }
    // 输出层激活
    outputLayer.out = f(outputLayer.in);
    // 记录均方误差
    float e = cur_data.label - outputLayer.out;
    // 输出层Err
    outputLayer.Err = e * outputLayer.out * (1-outputLayer.out);
}

void BPNN::backProp() {
    // 反向传播
    outputLayer.delta_bias += outputLayer.Err;
    // 输出层到隐藏层
    for (int i = 0; i < hiddenLayer_size; ++i) {
        node& curHiddenNode = hiddenLayer[i];
        curHiddenNode.Err = curHiddenNode.out * (1-curHiddenNode.out) * outputLayer.Err * curHiddenNode.w[0];
        curHiddenNode.delta_bias += curHiddenNode.Err;
        curHiddenNode.delta_w[0] += outputLayer.Err * curHiddenNode.out;
    }
    // 隐藏层到输入层
    for (int i = 0; i < N; ++i) {
        node& curInputNode = inputLayer[i];
        for (int j = 0; j < hiddenLayer_size; ++j) {
            curInputNode.delta_w[j] += curInputNode.out * hiddenLayer[j].Err;
        }
    }
}

float BPNN::training(int maxTime) {
    float bestRate = 0;
    while(maxTime--) {
        clearDeltaRecord();
        for (auto idx: idxOfTrain) {
            forwardCalc(dataSet[idx]);
            backProp();
        }
        float curRate = test();
        bestRate = max(bestRate, curRate);
        // printf("cur: %.5f  best: %.5f\n", curRate,bestRate);
        /* 记录最优参数 */
        update();
        // learningRate *= 0.9999; // 动态学习率
    }
    return bestRate;
}

void BPNN::update() {
    float trainDataSize = idxOfTrain.size();
    // 更新输入到隐藏层
    for (int i = 0; i < N; ++i) {
        node& tmp = inputLayer[i];
        for (int j = 0; j < hiddenLayer_size; ++j) {
            tmp.w[j] += tmp.delta_w[j] * learningRate / trainDataSize;
        }
    }
    // 更新隐藏层到输出层
    for (int i = 0; i < hiddenLayer_size; ++i) {
        node& tmp = hiddenLayer[i];
        tmp.w[0] += tmp.delta_w[0] * learningRate / trainDataSize;
        tmp.bias += tmp.delta_bias * learningRate / trainDataSize;
    }
    // 更新输出层偏置
    outputLayer.bias += outputLayer.delta_bias * learningRate / trainDataSize;
}

float BPNN::test() {
    // 计算验证集正确率
    float E = 0;
    for (auto idx: idxOfValid) {
        data& cur_data = dataSet[idx];
        clearInRecord();
        // 输入层到隐藏层
        for (int i = 0; i < N; ++i) {
            node& curInputNote = inputLayer[i];
            curInputNote.out = cur_data.vec[i]; // 输入层不需激活
            for (int j = 0; j < hiddenLayer_size; ++j) {
                hiddenLayer[j].in += curInputNote.out * curInputNote.w[j];
            }
        }
        // 隐藏层激活后传递到输出层
        for (int i = 0; i < hiddenLayer_size; ++i) {
            node& curHiddenNode = hiddenLayer[i];
            curHiddenNode.out = f(curHiddenNode.in); // 激活
            outputLayer.in += curHiddenNode.out * curHiddenNode.w[0];
        }
        // 输出层激活
        outputLayer.out = f(outputLayer.in);
        int predict = 0;
        if (outputLayer.out >= 0.5) predict = 1;
        if (predict == cur_data.label) {
            E ++;
        }
    }
    return E / idxOfValid.size();
}


inline void printLine() {
    printf("*********************\n");
}

int main() {
    clock_t start = clock();
    int hl_size = 3; // 隐藏层节点数为3
    BPNN test(1, hl_size);
    printf("start reading data\n");
    test.readData();
    test.divideData();
    printf("finish reading data, use time: %d ms\n", clock()-start);printLine();
    printf("start training data\n");
    int itTime = 5000;
    float bestRate = test.training(itTime);
    printf("number of iterations: %d \n", itTime);
    printf("finish training, best rate: %.5f  use time: %d ms\n",bestRate, clock() - start);
    return 0;
}