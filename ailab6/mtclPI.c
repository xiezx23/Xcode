#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int inRound1 = 0, inRound2 = 0;
int outRound1 = 0, outRound2 = 0;

void* function1(void* arg) {
    int cnt = 10000000;
    float randH, randW;
    srand(time(0));
    while(cnt--) {
        randH = (rand() % 200 - 100) / 100.0;
        randW = (rand() % 200 - 100) / 100.0;
        if (randH*randH + randW*randW > 1) {
            outRound1 ++;
        }
        else inRound1 ++;
    }
    return NULL;
}

void* function2(void* arg) {
    int cnt = 10000000;
    float randH, randW;
    srand(time(0)+1);
    while(cnt--) {
        randH = (rand() % 200 - 100) / 100.0;
        randW = (rand() % 200 - 100) / 100.0;
        if (randH*randH + randW*randW > 1) {
            outRound2 ++;
        }
        else inRound2 ++;
    }
    return NULL;
}

int main() {
    // 用并行计算优化蒙特卡洛计算pi值
    pthread_t p1 = 0, p2 = 1;
    pthread_create(&p1, NULL, function1, NULL);
    pthread_create(&p2, NULL, function2, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    // 估算pi
    float round = inRound1 + inRound2;
    float square = outRound1 + outRound2 + round;
    float pi = 4 * round / square;
    printf("pi : %f\n", pi);
    return 0;
}