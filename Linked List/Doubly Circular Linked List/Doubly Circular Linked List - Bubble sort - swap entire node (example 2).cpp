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
        head = tail = new NODE;
        head->txt = txt;
        head->data = value;
        head->prev = head->next = tail;
    } else {
        prevnode = tail;
        tail->next = head->prev = new NODE;
        tail = tail->next;
        tail->prev = prevnode;
        tail->txt = txt;
        tail->data = value;
        tail->next = head;
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

void bubbleSort_ASC(){
    if(head == NULL){
        cout << "Sorting not possible!" << endl;
    } else {
        NODE *prevX, *prevY = NULL;
        for(NODE *x = head; x->next != head; x = x->next){
            prevX = x->prev;
            int i = 1;
            for(NODE *y = head; y->next != head; y = y->next){
                prevY = y->prev; temp = y->next;
                string updateX;
                if(y->data > temp->data){
                    updateX = (prevX && prevX->next == y) ? "prev" : (x->next == y) ? updateX = "x" : "";

                    NODE *swap = temp->next;
                    temp->next = y;
                    y->next = swap;
                    y->prev = temp;
                    temp->prev = prevY;
                    prevY->next = temp;
                    if(swap) swap->prev = y;
                    if(prevY == tail){
                        head = x = temp;
                        tail->next = head;
                        head->prev = tail;
                    }
                    if(swap == head){
                        tail = y;
                        tail->next = head;
                        head->prev = tail;
                    }
                    
                    if(updateX == "prev") {
                        prevX->next = temp;
                    } else if(updateX == "x"){
                        x->next = temp;
                    }
                    y = temp;
                }
                i++;
            }
        }
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