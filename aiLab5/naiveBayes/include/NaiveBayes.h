#include <bits/stdc++.h>
#include "lib.h"
using namespace std;

class NaiveBayes {
private:
    string root = "X:/file/classification_dataset/";
    vector<string> ansSet;

    // train_set[i] 存第i个句子的单词和出现次数
    dataSet train_set;
    // train_indexMap[label] 存标签label对应的句子位置     
    indxMap train_indexMap;
    // train_labelArr[i] 存第i个句子的标签
    vector<string> train_labelArr;

    dataSet valid_set;
    indxMap valid_indexMap;
    vector<string> valid_labelArr;

public:
    void read();
    void readSet(const string&, dataSet&, indxMap&, vector<string>&);
    void write();

    void test_Bernoulli();
    void test_Multinomial();
};