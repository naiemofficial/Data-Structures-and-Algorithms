#include <iostream>
using namespace std;

struct NODE {
    int data;
    char txt;
    NODE *next;
};

NODE *head, *tail, *temp;
int n = 0;
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
    n++;
}

void bubbleSort_ASC(){
    if(head == NULL){
        cout << "Sorting not possible!" << endl;
    } else {
        NODE *x = head, *prev;
        for (int i = 0; i < n-1; i++) {
            NODE *y = head;
            for (int j = 0; j < (n-1-i); j++) {
                temp = y->next;
                if(y->data > temp->data){
                    NODE *swap = temp->next;
                    temp->next = y;
                    y->next = swap;
                    if(prev) prev->next = temp;
                    if(!prev) head = x = temp; tail->next = head;
                    if(swap == head) tail = y; tail->next = head;
                    y = temp;
                }
                prev = y; 
                y = y->next;
            }
            x = x->next;
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