#include <bits/stdc++.h>
#include "../include/knnClassifier.h"
using namespace std;


int main() {
    knnClassifier knn_test;
    knn_test.read();
    // for (int i = 1; i < 200; ++i) {
    //     cout << "k = " << i << ", Accuracy:" << knn_test.test(i) << endl;
    // }
    knn_test.test(11);
    knn_test.write();
    return 0;
}