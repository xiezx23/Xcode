#include <bits/stdc++.h>
using namespace std;

typedef struct staff{
    int id, age, wages;
    char name[20];
    staff* next;
}staff;


void registerStaff(int n, staff* head) {
    staff* cur = head;
    staff* tmp;
    while(n--) {
        tmp = (staff*)malloc(sizeof(staff));
        scanf("%d%d%d",&tmp->id,&tmp->age,&tmp->wages);
        scanf("%s",tmp->name);
        cur->next = tmp;
        cur = tmp;
    }
}

int main() {
    staff head;
    int n; 
    cin >> n;
    registerStaff(n, &head);
    staff* cur = head.next;
    for (int i = 0; i < n; ++i) {
        cout << cur->age << cur->id << cur->name << endl;
        cur = cur->next;
    }
}