#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#define ll long long
#define MAXNUM 100010
using namespace std;

class Solution {
public:
    inline int test(vector<int>& nums, int n) {
        int ans = 0;
        int headIdx = 0, tailIdx = 0;
        while(headIdx < nums.size()) {
            int base = nums[headIdx];
            while(tailIdx < nums.size() && nums[tailIdx] - base <= n) {
                tailIdx++;
            }
            tailIdx--;
            ans += (tailIdx - headIdx);
            headIdx++;
        }
        return ans;
    } 
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int left = 0, right = nums[nums.size()-1] - nums[0], mid;
        if (test(nums, left) >= k) return left;
        while (right - left > 1) {
            mid = right - (right-left) / 2;
            if (test(nums, mid) >= k) {
                right = mid;
            }
            else left = mid;
        }
        return right;
    }
};

int main() {
    vector<int> arr = {1,6,1};
    int k = 3;
    Solution test;
    cout << test.smallestDistancePair(arr, k);
}