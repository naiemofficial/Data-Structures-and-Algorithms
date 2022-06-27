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
        obj.head = new NODE;
        obj.head->data = value;
        obj.head->next = 0;
        obj.tail = obj.head;
    } else {
        obj.prevnode = obj.tail;
        obj.tail->next = new NODE;
        obj.tail = obj.tail->next;
        obj.tail->prev = obj.prevnode;
        obj.tail->data = value;
        obj.tail->next = 0;
    }
}

void selectionSort_ASC(NODE *head){
    NODE *temp;
    if(head == NULL){
        cout << "Sorting not possible!" << endl;
    } else {
        for(NODE *x = head; x->next != 0; x = x->next){
            temp = x;
            for(NODE *y = x->next; y != 0; y = y->next){
                if(y->data < temp->data) temp = y;
            }
            if(temp != x){
                int swap = x->data;
                x->data = temp->data;
                temp->data = swap;
            }
        }
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
            } else if ((A && B && A->data > B->data) || (!A && B)) {
                sort->next = B;
                B = B->next;
            }
            Sorted.prevnode = sort;
            sort = sort->next;
            sort->prev = Sorted.prevnode;
        }
        Sorted.head = root->next;
        Sorted.tail = sort;
        Sorted.head->prev = 0;
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

    selectionSort_ASC(A.head);
    selectionSort_ASC(B.head);

    mergeList(A, B);
    cout << "[S] ";
    print(Sorted);
}