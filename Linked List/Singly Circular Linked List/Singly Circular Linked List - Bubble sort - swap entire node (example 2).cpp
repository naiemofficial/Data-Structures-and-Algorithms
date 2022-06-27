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

void bubbleSort_ASC(){
    if(head == NULL){
        cout << "Sorting not possible!" << endl;
    } else {
        NODE *prevX = 0;
        for(NODE *x = head; x->next != head; x = x->next){
            NODE *prevY = 0;
            for(NODE *y = head; y->next != head; y = y->next){
                temp = y->next;
                string updateX;
                if(y->data > temp->data){
                    updateX = (prevX && prevX->next == y) ? "prev" : (x->next == y) ? updateX = "x" : "";

                    NODE *swap = temp->next;
                    temp->next = y;
                    y->next = swap;
                    if(prevY) prevY->next = temp;
                    if(!prevY) head = x = temp; tail->next = head;
                    if(swap == head) tail = y; tail->next = head;
                    
                    if(updateX == "prev") {
                        prevX->next = temp;
                    } else if(updateX == "x"){
                        x->next = temp;
                    }
                    y = temp;
                }
                prevY = y;
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
    
    bubbleSort_ASC();
    print(head);
}