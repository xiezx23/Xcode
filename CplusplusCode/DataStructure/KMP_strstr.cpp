#include<bits/stdc++.h>
#define ll long long

using namespace std;

//在baseStr中查找findStr,若有则返回首字母下标,否则返回-1
int kmp(string baseStr, string findStr) {
    if (findStr.size() == 0) return 0;
    else if (baseStr.size() < findStr.size()) return -1;
    //处理next数组
    int next[findStr.size()];
    memset(next,0,sizeof(int)*findStr.size());
    //i是遍历原字符串的下标,j是对应匹配前缀下标
    for (int i = 1, j = 0; i < findStr.size();) {
        if (findStr[i] == findStr[j]) {
            next[i] = j + 1; //代表i位置的匹配位是j, "+1"是因为在比较中跳转后比对的是j的下一位
            i += 1, j += 1; //匹配成功双下标下行
        }
        else if (j == 0) i += 1; //i连首字母都匹配不上,考虑i的下一位
        else j = next[j-1]; //当之前匹配上的位置有对应前缀时跳转过去
    }
    //开始匹配
    int posiIndex = 0;
    for (int i = 0; i < baseStr.size(); ) {
        if (baseStr[i] == findStr[posiIndex]) {
            posiIndex += 1;
            if (posiIndex == findStr.size()) {
                return i - posiIndex + 1;
            }
            i += 1;
        }
        else if (posiIndex == 0) i += 1;
        else posiIndex = next[posiIndex - 1];
    }
    return -1;
}

int main() {
    string a, b;
    cin >> a >> b;
    cout << kmp(a,b);
    return 0;
}