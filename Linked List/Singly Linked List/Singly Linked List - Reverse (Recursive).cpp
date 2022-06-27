#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *next;
};

NODE *head, *tail;
void add(int value){
    if(head == NULL){
        head = new NODE;
        head->data = value;
        head->next = 0;
        tail = head;
    } else {
        tail->next = new NODE;
        tail = tail->next;
        tail->data = value;
        tail->next = 0;
    }
}

NODE *reverseRecursive(NODE *node){
    if(node == 0) return 0;
    if(node->next == 0){
        tail = head;
        head = node;
        return node;
    }
    NODE *reverse = reverseRecursive(node->next);
    reverse->next = node;
    node->next = 0;
    return node;
}

int print(NODE *ref){
    if(ref == 0){
        cout << "[EMPTY LIST]" << endl;
        return false;
    } else {
        while(ref != 0){
            cout << ref->data;
            ref = ref->next;
            if(ref != 0 ) cout << " => ";
        }
        cout << endl;
        return true;
    }
}

int main(){
    add(10);
    add(20);
    add(30);
    add(40);
    add(50);

    reverseRecursive(head);
    print(head);
}