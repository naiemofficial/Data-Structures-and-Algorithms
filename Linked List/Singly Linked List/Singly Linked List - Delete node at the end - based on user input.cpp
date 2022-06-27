#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *next;
};

NODE *head, *tail, *temp;
void add(int value){
    if(head == NULL){
        head = new NODE;
        head->data = value;
        head->next = 0;
        tail = head;
    } else {
        tail->next = new NODE;
        tail = tail->next;
        tail->data = value;
        tail->next = 0;
    }
}

int deleteEnd(){
    NODE *prev;
    temp = head;

    if(temp == 0){
        cout << "Action not complete" << endl;
        return false;
    } else {
        while(temp->next != 0){
            prev = temp;
            temp = temp->next;
        }

        if(prev->next == 0){
            head = 0;
        } else {
            prev->next = 0;
        }
        if(temp->next == 0) tail = prev;
        delete temp;
        return true;
    }
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
        cout << "Enter a value for the NODE-" << ++i << ": ";
        cin >> input;
        if(input != 0) add(input);
    }
    cout << endl << "Linked list:\t";
    if(print(head)){
        cout << endl << endl;

        cout << "-----------------------------------------" << endl;
        cout << "Note! Enter zero (0) to end the program. " << endl;
        cin.ignore();
        
        string input;
        while(true){
            cout << "Press enter to continue deleting node(s) at the end ↩ ";
            getline(cin, input);
            if(input == ""){
                bool update = deleteEnd();
                if(update){
                    cout << "1 node has been deleted from the end. ";
                    cout << "Updated list is: \t" << endl << "↳ ";
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