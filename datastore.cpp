#include <bits/stdc++.h>
using namespace std;
//小数据库，可以实现data.txt里的数据的读取跟追加

typedef struct node{
    string name;
    string year;
}node;

vector<node> arr;

void init() {
    freopen("C:\\Users\\xiezexi\\Desktop\\Xcode\\data.txt","r",stdin);
    string name, year;
    while(cin >> name >> year) {
        node tmp = {name,year};
        arr.push_back(tmp);
    }
    freopen("CON","r",stdin); //把输入切换回控制台
    cin.clear();  //清除输入流缓存
}

void close() {
    freopen("C:\\Users\\xiezexi\\Desktop\\Xcode\\data.txt","w",stdout);
    for (auto i: arr) {
        cout << i.name << " " << i.year << endl;
    }
    fclose(stdout);
}

void add() {
    string n, y;
    cin >> n >> y;
    node tmp = {n, y};
    arr.push_back(tmp);
}

int main() {
    init();
    while(1) {
        printf("操作:\n0:退出\n1:添加\n2:显示人数\n\n");
        int opra = 1;
        fflush(stdin);
        cin >> opra;
        if (opra == 0) break;
        else if (opra == 1) {
            add();
        }
        else if (opra == 2) {
            cout << "人数: " << arr.size() << endl << endl;
        }
        else {
            cout << "输入格式错误\n\n";
        }
    }
    close();
    return 0;
}