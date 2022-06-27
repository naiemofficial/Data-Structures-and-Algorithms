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

void selectionSort_ASC(NODE* head){
    NODE *temp;
    if(head == NULL){
        cout << "Sorting not possible!" << endl;
    } else {
        for(NODE *x = head; x->next != head; x = x->next){
            temp = x;
            for(NODE *y = x->next; y != head; y = y->next){
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
                if(A == listA.head) A = 0;
            } else if ((A && B && A->data > B->data) || (!A && B)) {
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