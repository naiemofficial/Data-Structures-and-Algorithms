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

List merged;
void mergeList(List &A, List &B){
    NODE *sort = merged.head = A.head;
    if(A.head != 0 && B.head != 0){
        while(sort->next != 0){
            sort = sort->next;
        }
        sort->next = B.head;
        merged.tail = B.tail;
    } else {
        cout << "Merge not possible" << endl;
    }
}

int print(List list){
    NODE *ref = list.head;
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
    add(A, 15);
    add(A, 22);
    add(A, 28);
    add(A, 20);
    add(A, 48);

    add(B, 18);
    add(B, 100);
    add(B, 85);
    add(B, 42);
    add(B, 25);

    cout << "[A] ";
    print(A);

    cout << "[B] ";
    print(B);

    mergeList(A, B);
    cout << "[S] ";
    print(merged); // List "merged" intialized before the mergeList function
}