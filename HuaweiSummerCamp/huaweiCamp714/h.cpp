#include <bits/stdc++.h>
#include <cmath>
using namespace std;

#define vec pair<double, double>

double multi(vec& a, vec& b) {
    double ans = ( a.first * b.first + a.second * b.second )/ (sqrt(a.first*a.first + a.second * a.second)*sqrt(b.first * b.first + b.second*b.second));
    return ans;
}

int main () {
    int t;
    cin >> t;
    int x1,x2,x3,y1,y2,y3;
    while (t--) {
        scanf("%d%d%d%d%d%d", &x1,&y1,&x2,&y2,&x3,&y3);
        // 1 to 2
        vec base = make_pair(x2-x1, y2-y1);
        double tmpdis12 = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
        double dis12 = sqrt(tmpdis12) / 2;
        double b12 = sqrt(tmpdis12/4 - 1);
        double h12 = dis12 * b12;
        double x,y;
        if (base.second == 0) {
            x = 0, y = 1;
        }
        else {
            x = 1, y = -base.first/base.second;
        }
        double bot = sqrt(x*x + y*y);
        x = x / bot; y = y / bot;
        x *= h12;
        y *= h12;
        vec left_v12 = make_pair(base.first + x, base.second + y);
        vec right_v12 = make_pair(base.first - x, base.second - y);
        // 2 to 3
        vec base23 = make_pair(x3-x2, y3-y2);
        double tmpdis23 = (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2);
        double dis23 = sqrt(tmpdis23) / 2;
        double b23 = sqrt(tmpdis23/4 - 1);
        double h23 = dis23 / b23;
        if (base23.second == 0) {
            x = 0, y = 1;
        }
        else {
            x = 1, y = -base23.first/base23.second;
        }
        bot = sqrt(x*x + y*y);
        x = x / bot; y = y / bot;
        x *= h23;
        y *= h23;
        vec left_v23 = make_pair(base23.first + x, base23.second + y);
        vec right_v23 = make_pair(base23.first - x, base23.second - y);
        // check
        double signl1 = acos(multi(left_v12, left_v23));
        double signr1 = acos(multi(right_v12, left_v23));
        double sum1 = acos(multi(left_v12, right_v12));
        if (abs (sum1 - (signl1 + signr1)) < 1e-8) {
            cout << "yes\n";
            continue;
        }
        // check
        double signl2 = acos(multi(left_v12, right_v23));
        double signr2 = acos(multi(right_v12, right_v23));
        if (abs (sum1 - (signl2 + signr2)) < 1e-8) {
            cout << "yes\n";
            continue;
        }
        cout << "no\n";
    }
    
    return 0;
}