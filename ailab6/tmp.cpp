#include <bits/stdc++.h>
using namespace std;

int main() {
    float cnt = 10000000;
    float round = 0;
    float randH, randW;
    srand(time(0));
    while(cnt--) {
        randH = (rand() % 200 - 100) / 100.0;
        randW = (rand() % 200 - 100) / 100.0;
        if (randH*randH + randW*randW < 1) round ++;
    }
    cout << 4.0*round/10000000 << endl;
}