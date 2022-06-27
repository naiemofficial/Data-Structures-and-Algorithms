#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *next;
};

class List {
    public:
        NODE *head = NULL;
        NODE *tail = NULL;
};

void add(List &obj, int value){
    if(obj.head == NULL){
        obj.head = new NODE;
        obj.head->data = value;
        obj.head->next = 0;
        obj.tail = obj.head;
    } else {
        obj.tail->next = new NODE;
        obj.tail = obj.tail->next;
        obj.tail->data = value;
        obj.tail->next = 0;
    }
}

NODE *mergeList(NODE *A, NODE *B){
    if(A == 0) return B;
    if(B == 0) return A;
    if(A->data <= B->data){
        A->next = mergeList(A->next, B);
        return A;
    } else {
        B->next = mergeList(A, B->next);
        return B; 
    }
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
    List A, B;
    add(A, 10);
    add(A, 30);
    add(A, 50);
    add(A, 70);
    add(A, 90);

    add(B, 20);
    add(B, 40);
    add(B, 60);
    add(B, 80);
    add(B, 100);

    cout << "[A] ";
    print(A.head);

    cout << "[B] ";
    print(B.head);

    NODE *Sorted = mergeList(A.head, B.head);
    cout << "[S] ";
    print(Sorted);
}