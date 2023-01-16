#include <iostream>

using namespace std;

int solution(int coins[10], int size) {
    // coins是一个数组，存放每堆硬币数量
    // size代表堆数
    // 答案return给调用者
    int ans = 0;
    for (int i = 0; i < size; ++i) {
        if (coins[i] % 2 == 0) {
            // 该堆上的硬币数可以被2整除
            ans += coins[i] / 2;
            // ans = ans + coins[i]/2;
        }
        else {
            ans += coins[i] / 2 + 1;
        }
    }
    return ans;
}

int main() {
    int coins[10] = {2,3,10};
    int size = 3;
    cout << solution(coins, size);
    return 0;
}