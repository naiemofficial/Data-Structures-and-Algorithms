#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *next;
};

NODE *head, *tail, *temp;
void add(int value){
    if(head == NULL){
        head = tail = new NODE;
        head->data = value;
        head->next = tail;
    } else {
        tail->next = new NODE;
        tail = tail->next;
        tail->data = value;
        tail->next = head;
    }
}

int deleteBegin(){
    temp = head;
    if(temp == 0){
        cout << "Action not complete" << endl;
        return false;
    } else {
        if(temp->next == head){
            head = tail = 0;
        } else {
            head = temp->next;
            tail->next = head;
        }
        delete temp;
        return true;
    }
}

int print(NODE *ref){
    if(ref == 0){
        cout << "[EMPTY LIST]" << endl;
        return false;
    } else {
        do {
            cout << ref->data;
            ref = ref->next;
            if(ref != head) cout << " => ";
        } while(ref != head);
        cout << endl;
        return true;
    }
}

int main(){
    cout << "Note! Enter zero (0) to exit from entering input. " << endl;
    int input = 1, i = 0;
    while(input != 0){
        cout << "Enter a value for the NODE-" << ++i << ": ";
        cin >> input;
        if(input != 0) add(input);
    }
    cout << endl << "Linked list ";
    if(print(head)){
        cout << endl << endl;

        cout << "-----------------------------------------" << endl;
        cout << "Note! Enter zero (0) to end the program. " << endl;
        cin.ignore();
        
        string input;
        while(true){
            cout << "Press enter to continue deleting node(s) at the beginning ↩ ";
            getline(cin, input);
            if(input == ""){
                bool update = deleteBegin();
                if(update){
                    cout << "1 node has been deleted from the beginning. ";
                    cout << "Updated list: " << endl << "↳ ";
                    if(!print(head)){
                        break;
                    }
                }
                cout << endl << endl;
            } else {
                cout << "Program exited!";
                break;
            }
        }
    }
}