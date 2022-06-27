#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *next;
};

NODE *head, *tail, *temp;
void addBegin(int value){
    temp = new NODE;
    temp->data = value;
    temp->next = head;
    head = temp;
    if(head->next == 0) tail = head;
}

int print(NODE *ref){
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
    cout << "Note! Enter zero (0) to exit from entering input. " << endl;
    int input = 1, i = 0;
    while(input != 0){
        cout << "Enter a value for the beginning NODE: ";
        cin >> input;
        if(input != 0) addBegin(input);
    }
    cout << endl << "Linked List: ";
    print(head);
}