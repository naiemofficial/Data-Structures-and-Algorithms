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
        head = new NODE;
        head->txt = txt;
        head->data = value;
        head->next = 0;
        tail = head;
    } else {
        tail->next = new NODE;
        tail = tail->next;
        tail->txt = txt;
        tail->data = value;
        tail->next = 0;
    }
}

void bubbleSort_ASC(){
    if(head == NULL){
        cout << "Sorting not possible!" << endl;
    } else {
        NODE *prevX = 0;
        for(NODE *x = head; x->next != 0; x = x->next){
            NODE *prevY = 0;
            for(NODE *y = head; y->next != 0; y = y->next){
                temp = y->next;
                if(y->data > temp->data){
                    string updateX = (prevX && prevX->next == y) ? "prev" : (x->next == y) ? updateX = "x" : "";

                    NODE *swap = temp->next;
                    temp->next = y;
                    y->next = swap;
                    if(prevY) prevY->next = temp;
                    if(!prevY) head = x = temp;
                    if(!swap) tail = y;
                    
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
    
    bubbleSort_ASC();
    print(head);
}