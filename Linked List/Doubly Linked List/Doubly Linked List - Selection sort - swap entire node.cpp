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
        NODE *prevX = 0;
        for(NODE *x = head; x->next != 0; x = x->next){
            prevX = x->prev; temp = x;
            NODE *prevY = 0;
            for(NODE *y = x->next; y != 0; y = y->next){
                if(y->data < temp->data){
                    temp = y;
                    prevY = y->prev;
                }
            }
            
            if(temp != x){
                if(prevX != 0){
                    prevX->next = temp;
                    temp->prev = prevX;
                }
                if(prevY != 0){
                    prevY->next = x;
                    x->prev = prevY;
                }
                if(prevX == 0){
                    head = temp;
                    head->prev = 0;
                }

                NODE *swap = temp->next;
                temp->next = (x->next == temp) ? x : x->next;
                if(temp->next) temp->next->prev = temp;
                x->next = swap;

                if(swap == 0){
                    tail = x;
                } else {
                    swap->prev = x;
                }
                x = temp;
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
    add('C', 50);
    add('B', 10);
    add('D', 15);
    add('E', 30);
    add('F', 70);
    add('G', 20);
    add('H', 40);
    
    selectionSort_ASC();
    print(head);
}