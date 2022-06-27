#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *prev;
    NODE *next;
};

class List {
    public:
        NODE *prevnode = NULL;
        NODE *head = NULL;
        NODE *tail = NULL;
};

void add(List &obj, int value){
    if(obj.head == NULL){
        obj.head = obj.tail = new NODE;
        obj.head->data = value;
        obj.head->prev = obj.head->next = obj.tail;
    } else {
        obj.prevnode = obj.tail;
        obj.tail->next = obj.head->prev = new NODE;
        obj.tail = obj.tail->next;
        obj.tail->prev = obj.prevnode;
        obj.tail->data = value;
        obj.tail->next = obj.head;
    }
}

List Sorted;
void mergeList(List &listA, List &listB){
    NODE *A = listA.head, *B = listB.head;
    if(A || B){
        NODE *root = new NODE;
        NODE *sort = root;
        while(!(A == 0 && B == 0)){
            if((A && B && A->data <= B->data) || (A && !B)){
                sort->next = A;
                A = A->next;
                if(A == listA.head) A = 0;
            } else {
                sort->next = B;
                B = B->next;
                if(B == listB.head) B = 0;
            }
            Sorted.prevnode = sort;
            sort = sort->next;
            sort->prev = Sorted.prevnode;
        }
        Sorted.head = root->next;
        Sorted.tail = sort;
        Sorted.tail->next = Sorted.head;
        Sorted.head->prev = Sorted.tail;
    } else {
        cout << "Merge sort not possible" << endl;
    }
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
            if(ref != list.head) cout << " => ";
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

    mergeList(A, B);
    cout << "[S] ";
    print(Sorted);
}