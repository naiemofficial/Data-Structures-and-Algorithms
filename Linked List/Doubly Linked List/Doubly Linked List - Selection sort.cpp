#include <iostream>
using namespace std;

struct NODE {
    int data;
    char txt;
    NODE *prev;
    NODE *next;
};

NODE *head, *tail, *prevnode, *temp;
void add(char txt, int value){
    if(head == NULL){
        head = new NODE;
        head->txt = txt;
        head->data = value;
        head->next = 0;
        tail = head;
    } else {
        prevnode = tail;
        tail->next = new NODE;
        tail = tail->next;
        tail->prev = prevnode;
        tail->txt = txt;
        tail->data = value;
        tail->next = 0;
    }
}

void selectionSort_ASC(){
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

int print(NODE *ref){
    if(ref == 0){
        cout << "[EMPTY LIST]" << endl;
        return false;
    } else {
        while(ref != 0){
            cout << "[" << ref->txt << "-" << ref->data << "]";
            ref = ref->next;
            if(ref != 0 ) cout << " => ";
        }
        cout << endl;
        return true;
    }
}

int main(){
    add('A', 100);
    add('B', 10);
    add('C', 50);
    add('D', 15);
    add('E', 30);
    add('F', 70);
    add('G', 20);
    add('H', 40);
    
    selectionSort_ASC();
    print(head);
}