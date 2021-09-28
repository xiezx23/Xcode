/*************************************************************************
    > File Name: legal_ip_address.cpp
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2021-9-27
************************************************************************/
#include <iostream>

using namespace std;

int read (string);

int main(){
    int num;
    string str;
    cin >> str;
    int length = str.length();
    for (int i = 1; i<=3; ++i) {
        num = read(str.substr(0,i));
        if (num > 255) continue;
        for (int j = 1; j<=3; ++j) { 
            num = read(str.substr(i,j));
            if (num > 255) continue;
            for (int k = 1; k<=3; ++k) { 
                num = read(str.substr(i+j,k));
                if (length-i-j-k <= 0 || num > 255 ) continue;
                num = read(str.substr(i+j+k, length-i-j-k));
                if (num <= 255) {
                    //legal_ip
                    cout << str.substr(0,i)+"."+str.substr(i,j)+"."+str.substr(i+j,k)+"."+str.substr(i+j+k, length-i-j-k) << endl;
                }
            }
        }
    }
    return 0;
}

int read(string str) {
    if (str[0] == '0' && str.length() != 1) return 256;
    int num = 0;
    for (int i = 0; i < str.length(); ++i) {
        num *= 10;
        num += str[i] - '0';
    }
    return num;
}