#include <bits/stdc++.h>
using namespace std;
#define pr pair<double, double>

double getDataFromIdx(string& line, int index) {
    int size = line.size() - 1, start = 0, cnt = 0;
    for (int idx = 0; idx < size; ++idx) {
        if (line[idx] == ',') {
            cnt ++;
            if (cnt == index) {
                start = idx + 1;
                break;
            }
        }
    }
    string rate;
    for (start; line[start] != ','; ++start) rate += line[start];
    stringstream str1(rate);
    double ans;
    str1 >> ans;
    return ans;
}

pr getData(string& line) {
    double ans1 = getDataFromIdx(line, 5);
    double ans2 = getDataFromIdx(line, 8);
    return make_pair(ans1, ans2);
}

void divide(double& us, double& ds, int& uc, int& dc, pr& data) {
    if (data.first > 0) {
        us += data.second;
        uc ++;
    }
    else {
        ds += data.second;
        dc ++; 
    }
}

int main() {
    auto r_ptr = freopen("X:\\data.csv","r",stdin);
    auto w_ptr = freopen("X:\\dataOut.csv","w",stdout);
    string year1;
    string year2, year3, year4;
    getline(cin, year1); cout << year1 << endl;
    getline(cin, year1);
    year1 += ",业绩上升敏感值均值,业绩下降敏感值均值,薪酬粘性";
    cout << year1 << endl;
    while(getline(cin, year1)) {
        getline(cin, year2);
        getline(cin, year3);
        getline(cin, year4);
        pr rate1 = getData(year2), rate2 = getData(year3), rate3 = getData(year4);
        double upSum = 0, downSum = 0;
        int upCnt = 0, downCnt = 0;
        divide(upSum, downSum, upCnt, downCnt, rate1);
        divide(upSum, downSum, upCnt, downCnt, rate2);
        divide(upSum, downSum, upCnt, downCnt, rate3);
        double upAvr = upSum / upCnt;
        double downAvr = downSum / downCnt;
        string backStr = "," + to_string(upAvr) + "," + to_string(downAvr) + "," + to_string(upAvr - downAvr);
        cout << year1+backStr << endl << year2+backStr << endl << year3+backStr << endl << year4+backStr << endl;
    }
    fclose(r_ptr);
    fclose(w_ptr);
    freopen("CON", "w", stdout);
    cout << "finish" << endl;
    return 0;
}
