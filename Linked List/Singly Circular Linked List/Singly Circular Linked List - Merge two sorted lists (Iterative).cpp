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
List mergeList(List &ListA, List &ListB){
    NODE *A = ListA.head, *B = ListB.head;
    if(A || B){
        NODE *root = new NODE;
        NODE *sort = root;
        do {
            if((A && B && A->data <= B->data) || (A && !B)){
                sort->next = A;
                A = (A->next == ListA.head) ? 0 : A->next;
            } else {
                sort->next = B;
                B = (B->next == ListB.head) ? 0 : B->next;
            }
            sort = sort->next;
        } while(!(A == 0 && B == 0));
        Sorted.head = root->next;
        Sorted.tail = sort;
        Sorted.tail->next = Sorted.head;
    }  else {
        cout << "Merge sort not possible" << endl;
        Sorted.head = 0;
    }
    return Sorted;
}

int print(List &list){
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

    mergeList(A, B);
    cout << "[S] ";
    print(Sorted);
}