/*************************************************************************
    > File Name: sortListNode.cpp
    > Author: ZX Xie
    > Mail: 1514806752@qq.com
    > Created Time: 2021-10-25
    

    @from:matrix 8-1 链表排序
************************************************************************/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
struct ListNode {
    T val;
    ListNode* next = nullptr;
    ListNode() : val(0), next(nullptr) {}
};

template<typename T>
bool cmp(ListNode<T>* a, ListNode<T>* b) {
    return a->val < b->val;
}

template<typename T>
ListNode<T>* sortList(ListNode<T>* head) {
    int size = 0;
    ListNode<T>* cur = head->next;
    while (1) {
        if (cur == nullptr) break;
        cur = cur->next;
        size += 1;
    }
    if (size < 2) return head;
    ListNode<T>* arr[size];
    cur = head->next;
    for (int i = 0; i < size; ++i) {
        arr[i] = cur;
        cur = cur->next;
    }
    sort(arr,&arr[size],cmp<T>);
    head->next = arr[0];
    for (int i = 0; i < size-1; ++i) {
        arr[i]->next = arr[i+1];
    }
    arr[size-1]->next = nullptr;
    return head;
}

int main() {
    ListNode<int>* head;
    ListNode<int> arr[5];
    arr[0].val = 3;
    arr[1].val = 5;
    arr[2].val = 2;
    arr[3].val = 9;
    arr[4].val = 1;
    for (int i = 0; i < 4; ++i) {
        arr[i].next = &arr[i+1];
    }
    head->next = &arr[0];
    head = sortList(head);
    for (ListNode<int>* i = head->next; i!=nullptr; i = i->next) {
        cout << i->val <<  "->";
    }
    cout << "nullptr\n";
    return 0;
}