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
        obj.head = obj.tail = new NODE;
        obj.head->data = value;
        obj.head->next = obj.tail;
    } else {
        obj.tail->next = new NODE;
        obj.tail = obj.tail->next;
        obj.tail->data = value;
        obj.tail->next = obj.head;
    }
}

List Sorted;
NODE *mergeList(NODE *A, NODE *B, List &ListA, List &ListB){
    if(A == 0) return B;
    if(B == 0) return A;
    if(A->data <= B->data){
        if(A->next == ListA.head){
            A->next = 0;
            Sorted.tail = B;
        }
        A->next = mergeList(A->next, B,ListA, ListB);
        Sorted.head = A;
    } else {
        if(B->next == ListB.head){ 
            B->next = 0;
            Sorted.tail = A;
        }
        B->next = mergeList(A, B->next,ListA, ListB);
        Sorted.head = B;
    }
    return Sorted.tail->next = Sorted.head;
}

int print(List list){
    NODE *ref = list.head;
    if(ref == 0){
        cout << "[EMPTY LIST]" << endl;
        return false;
    } else {
        do {
            cout << ref->data;
            ref = ref->next;
            if(ref != list.head ) cout << " => ";
        } while(ref != list.head);
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
    print(A);

    cout << "[B] ";
    print(B);

    mergeList(A.head, B.head, A, B);
    cout << "[S] ";
    print(Sorted);
}