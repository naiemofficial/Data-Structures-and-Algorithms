#include <iostream>
using namespace std;

struct NODE {
    int data;
    char txt;
    NODE *next;
};

NODE *head, *tail, *temp;
void add(char txt, int value){
    if(head == NULL){
        head = tail = new NODE;
        head->txt = txt;
        head->data = value;
        head->next = tail;
    } else {
        tail->next = new NODE;
        tail = tail->next;
        tail->txt = txt;
        tail->data = value;
        tail->next = head;
    }
}

void selectionSort_ASC(){
    if(head == NULL){
        cout << "Sorting not possible!" << endl;
    } else {
        NODE *prevX = 0;
        for(NODE *x = head; x->next != head; x = x->next){
            temp = x; 
            NODE *prevY = 0;
            for(NODE *y = x->next; y != head; y = y->next){
                if(y->data < temp->data) temp = y;
                if(y->next != head && y->next->data < temp->data){
                    prevY = y;
                }
            }
            if(temp != x){
                if (prevX != 0) prevX->next = temp;
                if(prevY != 0) prevY->next = x;
                if(prevX == 0) head = temp;

                NODE *swap = temp->next;
                temp->next = (x->next == temp) ? x : x->next;
                x->next = swap;
                
                if(temp == head || swap == head){
                    if(swap == head) tail = x;
                    tail->next = head;
                }
                x = temp;
            }
            prevX = x;
        }
    }
}

int print(NODE *ref){
    if(ref == 0){
        cout << "[EMPTY LIST]" << endl;
        return false;
    } else {
        do {
            cout << "[" << ref->txt << "-" << ref->data << "]";
            ref = ref->next;
            if(ref != head) cout << " => ";
        } while(ref != head);
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