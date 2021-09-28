/*************************************************************************
    > File Name: the_nearest_sum.cpp
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2021-09-27
************************************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    int size ,target;
    cin >> size;
    int arr[size+1];
    for (int i = 0; i < size; ++i) cin >> arr[i];
    cin >> target;
    sort(arr, &arr[size-1]);
    int sum;
    int nearest_ans = arr[0] + arr[1] + arr[2];
    int left_posi = 0, right_posi = size -1;
    for (int mid = 1; mid < size - 1; ++mid) {
        for (;left_posi < mid && right_posi > mid;) {
            sum = arr[left_posi] + arr[mid] + arr[right_posi];
            nearest_ans = abs(target - sum) > abs(target - nearest_ans)?nearest_ans:sum;
            if (sum == target) {
                cout << target;
                return 0;
            }
            else if (sum > target) {
                right_posi -= 1;
            }
            else {
                left_posi += 1;
            }
        }
        left_posi = 0;
        right_posi = size-1;
    }
    cout << nearest_ans;
    return 0;
}
