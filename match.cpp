#include <bits/stdc++.h>
using namespace std;

const int teamSize = 8; // 球队数

vector<string> teamName = {"生科","地院","药院","政务","电信","传设心理联","信管","中东联"};
// vector<string> teamName = {"计院","法院","管院","电信","系统","环院","化院","传设"};
int vsTable[teamSize-1][teamSize];
int arr[8] = {0,7,6,5,4,3,2,1};

void turnToNext() {
    // 0号位置不动
    int tail = arr[7];
    for (int i = 6; i > 0; --i) arr[i + 1] = arr[i];
    arr[1] = tail;
}

void calculate_schedule() {
    for (int round = 0; round < teamSize - 1; ++round) {
        // printf("第%d轮: \n", round + 1);
        int head = 0, tail = 7;
        while(head < tail) {
            // cout << teamName[arr[head]] << "vs" << teamName[arr[tail]] << endl;
            vsTable[round][arr[head]] = arr[tail];
            vsTable[round][arr[tail]] = arr[head];
            ++head;
            --tail;
        }
        turnToNext();
    }
}

void print_schedule() {
    for (int round = 0; round < teamSize - 1; ++round) {
        printf("第%d轮: \n", round + 1);
        int visited[teamSize] = {0};
        for (int i = 0; i < teamSize; ++i) {
            if (!visited[i]) {
                int army = vsTable[round][i];
                cout << teamName[i] << "vs" << teamName[army] << endl;
                visited[i] = visited[army] = 1;
            }
        }
    }
}

// bool change_schedule(int round, int a, int b) {
//     // 想让a和b在第round轮对战
//     int oriRound;
//     for (int r = 0; r < teamSize - 1; ++r) {
//         if (vsTable[r][a] == b) {
//             oriRound - r;
//             break;
//         }
//     }
//     if (oriRound == round) return true;
//     int c = vsTable[round][a], d = vsTable[round][b];
    
// }

int main() {
    calculate_schedule();
    print_schedule();
    return 0;
}