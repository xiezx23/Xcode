#include <bits/stdc++.h>
#include "../include/NaiveBayes.h"
using namespace std;

void NaiveBayes::test_Bernoulli() {
    ansSet.clear();
    int idxOfStrarr = 0, ans = 0;
    double N = train_set.size();
    for (auto text: valid_set) {
        double bestP = 0;
        string bestLabel;
        // 分标签计算概率
        for (auto i: train_indexMap) {
            string label = i.first;
            double nei = 0, Nei = i.second.size();
            double p = Nei / N;
            for (auto word: text) {
                nei = 0;
                for (auto idx: i.second) {
                    if (train_set[idx].count(word.first)) {
                        nei ++;
                    }
                }
                p *= (nei+1) / (Nei+4000);
                // p *= (nei+0.001) / (Nei+1000);
            }
            // cout << label << "的概率: " << p << endl;
            if (p > bestP) {
                bestP = p;
                bestLabel = label;
            }
        }
        // cout << "likely: " << bestLabel << " ans: ";
        // cout << valid_labelArr[idxOfStrarr] << endl;
        if (bestLabel == valid_labelArr[idxOfStrarr++]) {
            ans ++;
        }
        ansSet.push_back(bestLabel);
    }
    cout << "Accuracy: " << (double)ans / valid_set.size() << endl;
}


void NaiveBayes::test_Multinomial() {
    ansSet.clear();
    int idxOfStrarr = 0, ans = 0;
    double N = train_set.size();
    for (auto text: valid_set) {
        double bestP = 0;
        string bestLabel;
        // 分标签计算概率
        for (auto i: train_indexMap) {
            string label = i.first;
            double nWk = 0, nW = 0;
            for (auto idx: i.second) {
                for (auto j: train_set[idx]) {
                    nW += j.second;
                }
            }
            double p = nW / N;
            for (auto word: text) {
                nWk = 0;
                for (auto idx: i.second) {
                    if (train_set[idx].count(word.first)) {
                        nWk += train_set[idx][word.first];
                    }
                }
                p *= (nWk+0.001) / (nW+100000);
            }
            // cout << label << "的概率: " << p << endl;
            if (p > bestP) {
                bestP = p;
                bestLabel = label;
            }
        }
        // cout << "最可能的标签：" << bestLabel << endl;
        // cout << valid_labelArr[idxOfStrarr++] << endl;
        if (bestLabel == valid_labelArr[idxOfStrarr++]) {
            ans ++;
        }
        ansSet.push_back(bestLabel);
    }
    cout << "ac: " << (double)ans / valid_set.size() << endl;
}


void NaiveBayes::read() {
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


void NaiveBayes::readSet(const string& path, dataSet& dtSet, indxMap& indexMap, vector<string>& strArr) {
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


void NaiveBayes::write() {
    string path = "../output.csv";
    ofstream outFile(path, ios::out);
    for (auto i: ansSet) {
        outFile << i << endl;
    }
}

int main() {
    NaiveBayes bern_Test;
    bern_Test.read();
    bern_Test.test_Bernoulli();
    bern_Test.write();
    return 0;
}