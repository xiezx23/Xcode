/*************************************************************************
    > File Name: add_operator.cpp
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2021-10-12
    
    @method: 枚举运算符和数字链接，并在搜索时实时计算答案

    @from:matrix 6-1 添加运算符
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

vector<string> ansStr;
int length;
int target;
string originNum;

bool if_test(int posi, int res, string ans, int preMark, int preNum) {
    if (posi == length) {
        if (preMark == 0) res += preNum;
        else if (preMark == 1) res -= preNum;
        else res *= preNum; // preMark == 2
        if (res == target && ans != originNum) {
            ansStr.push_back(ans);
        }
        return true;
    }
    return false;
}

void dfs(int posi, int res, string ans, int preMark, int preNum, int preMUL) {
    if (if_test(posi, res, ans, preMark, preNum)){
        return;
    }
    //  * 号
    dfs(posi+1, res, ans + "*" + originNum[posi], preMark, preNum*(originNum[posi]-'0'), (originNum[posi]-'0')); 
    //  + 号
    if (preMark == 2) dfs(posi+1, res*preNum, ans + "+" + originNum[posi], 0, originNum[posi]-'0', INT_MIN);
    else if (preMark == 1) dfs(posi+1, res-preNum, ans + "+" + originNum[posi], 0, originNum[posi]-'0', INT_MIN);
    else dfs(posi+1, res+preNum, ans + "+" + originNum[posi], 0, originNum[posi]-'0', INT_MIN);
    //  - 号
    if (preMark == 2) dfs(posi+1, res*preNum, ans + "-" + originNum[posi], 1, originNum[posi]-'0', INT_MIN);
    else if (preMark == 1) dfs(posi+1, res-preNum, ans + "-" + originNum[posi], 1, originNum[posi]-'0', INT_MIN);
    else dfs(posi+1, res+preNum, ans + "-" + originNum[posi], 1, originNum[posi]-'0', INT_MIN);
    // 连续数
    if (preMUL != INT_MIN && preMUL != 0) {
        dfs(posi+1, res, ans + originNum[posi], preMark, preNum/preMUL*(preMUL*10+originNum[posi]-'0'), preMUL*10+originNum[posi]-'0');
    }
    else if (preNum != 0) dfs(posi+1, res, ans + originNum[posi], preMark, preNum*10+originNum[posi]-'0',INT_MIN);
    return;
}

int main(){
    cin >> originNum;
    cin >> target;
    length = originNum.size();
    dfs(1, 0, originNum.substr(0,1), 0, originNum[0]-'0', 0);
    for (auto v:ansStr) {
        cout << v << endl;
    }
    return 0;
}
