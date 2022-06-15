#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
int n,m,dis;

inline bool test(vector<int>& gua, int mid) {
    bool flag = 0; int count = 1;
    int last = gua[1];
    for(int i = 2; i <= n; i++)
    {
        if(gua[i]-last >= mid){
            count++; last = gua[i];
            if(count == m){flag = 1; break;}
        }
    }
    return flag;
}


int main()
{
    scanf("%d%d%d",&n,&m,&dis);
    vector<int>gua(n+1);
    for(int i = 1; i<=n; i++)
    {
        scanf("%d",&gua[i]);
    }
    sort(gua.begin(),gua.end());
    if(m == 2){
        printf("DELHI BBQ\n");
        printf("%d",gua[n]-gua[1]);
    }
    else {
        int left = 1, right = gua[n]-gua[1], mydis, mid;
        while(left<right-1)
        {
            mid = right - (right-left)/2; // 防溢出
            if(test(gua, mid)){
                left = mid;
            }
            else{
                right = mid;
            }
        }
        mydis = left;
        if(mydis > dis)
        {
            printf("DELHI BBQ\n");
            printf("%d",mydis);
        }
        else
        {
            printf("XHM BBQ\n");
            printf("%d",mydis);
        }
    }
    return 0;
}
