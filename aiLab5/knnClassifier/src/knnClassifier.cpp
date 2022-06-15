#include <bits/stdc++.h>
#include "../include/knnClassifier.h"
using namespace std;

double knnClassifier::test(int k) {
    ansSet.clear();
    int idxOfValid = 0, ans = 0;
    for (auto text: valid_set) { // text是验证集中的句子（urd_set）
        priority_queue<pair<double, string>> pq;
        int idxOfTrain = 0;
        for (auto word: train_set) {
            double d = distance(text, word);
            // 优先队列处理
            if (pq.size() < k) {
                pq.push(make_pair(d, train_labelArr[idxOfTrain]));
            }
            else {
                pair<double,string> tmp = pq.top();
                if (tmp.first > d) {
                    pq.pop();
                    pq.push(make_pair(d, train_labelArr[idxOfTrain]));
                }
            }
            idxOfTrain ++;
        }
        // 根据pq中的众数得出最可能的标签
        string bestLabel, curlabel;
        int bestCount = 0;
        unordered_map<string, int> mp;
        while(pq.size()) {
            curlabel = pq.top().second;
            mp[curlabel] += 1;
            if (mp[curlabel] > bestCount) {
                bestLabel = curlabel;
                bestCount = mp[curlabel];
            }
            pq.pop();
        }
        // cout << "最可能的标签：" << bestLabel << endl;
        // cout << valid_labelArr[idxOfValid++] << endl;
        if (bestLabel == valid_labelArr[idxOfValid++]) {
            ans ++;
        }
        ansSet.push_back(bestLabel);
    }
    double ret = (double)ans / valid_set.size(); // 计算准确率
    cout << ret << endl;
    return ret;
}

int knnClassifier::distance(unordered_map<string,int>& setA, unordered_map<string,int>& setB) {
    // method: 独热码 + 欧几里得距离
    int ans = 0;
    int similarNum = 0;
    for (auto i: setA) {
        if (setB.count(i.first)) {
            similarNum ++;
        }
    }
    // double ans_d = sqrt(setA.size() + setB.size() - similarNum*2);
    ans = setA.size() + setB.size() - (similarNum << 1);
    return ans;
}


void knnClassifier::read() {
    ios::sync_with_stdio(0);
    string trainPath = root + "train_set.csv", 
           validPath = root + "validation_set.csv",
           testPath = root + "test_set.csv",
           examPath  = root + "classification_simple_test.csv";
    readSet(trainPath, train_set, train_indexMap, train_labelArr);
    readSet(validPath, train_set, train_indexMap, train_labelArr);
    // readSet(validPath, valid_set, valid_indexMap, valid_labelArr);
    readSet(examPath, valid_set, valid_indexMap, valid_labelArr);
    // readSet(testPath, valid_set, valid_indexMap, valid_labelArr);
}

void knnClassifier::write() {
    string path = "C:/Users/xiezexi/Desktop/Xcode/aiLab5/knnClassifier/output.csv";
    ofstream outFile(path, ios::out);
    for (auto i: ansSet) {
        outFile << i << endl;
    }
}

void knnClassifier::readSet(const string& path, dataSet& dtSet, indxMap& indexMap, vector<string>& strArr) {
    string lineStr, temp, words, label;
    ifstream inFile(path, ios::in);
    int idxOfWords = dtSet.size(); // 记录文本的次序
    int skipFirstLine = 1;
	while (getline(inFile, lineStr))
	{
        if (skipFirstLine) {
            // 跳过首行
            skipFirstLine = 0;
        }
        else {
            stringstream sstream(lineStr);
            int flag = 1;
            while (getline(sstream, temp, ',')) {
                if (flag) {
                    flag = 0;
                    words = temp;
                }
                else label = temp;
            }
            sstream.clear(); sstream.str(words);
            unordered_map<string, int> tmpMap;
            while (sstream >> temp) {
                tmpMap[temp] ++;
            }
            dtSet.push_back(tmpMap);
            // 根据标签记录对应标签集合的元素下标
            strArr.push_back(label);
            if (indexMap.count(label) == 0) {
                vector<int> tmpVec;
                tmpVec.push_back(idxOfWords);
                indexMap[label] = tmpVec;
            }
            else {
                indexMap[label].push_back(idxOfWords);
            }
            ++ idxOfWords;
        }
	}
    // // 测试读取
    // for (auto i: dtSet) {
    //     for (auto j: i) {
    //         cout << j.first << " ";
    //     }
    //     cout << endl;
    // }
}

int main() {
    knnClassifier knn_test;
    knn_test.read();
    // cout << "k & Accuracy & k & Accuracy & k & Accuracy & k & Accuracy" << endl ;
    // int count = 1;
    // cout << "\\hline" << endl;
    // for (int i = 1; i <= 60; ++i) {
    //     cout << i << "& " << knn_test.test(i);
    //     if (count % 4 != 0) {
    //         cout << " & ";
    //     }
    //     else {
    //         cout << "\\\\" << endl;
    //         cout << "\\hline" << endl;
    //     }
    //     count ++;
    // }
    knn_test.test(11);
    // knn_test.write();
    return 0;
}