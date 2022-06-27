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

int deleteVal(int value){
    NODE *prev;
    temp = head;
    for(int i = 1; temp->data != value; i++){
        prev = temp;
        temp = temp->next;
        if(temp == 0) break;
    }

    if(temp == 0){
        cout << "The value [" << value << "] doesn\'t exist in the list!" << endl;
        return false;
    } else {
        if(head->data == value){
            head = temp->next;
        } else {
            prev->next = temp->next;
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
        input = 1;
        while(input != 0){
            cout << "Enter an available value to be deleted: ";
            cin >> input;
            if(input != 0){
                bool update = deleteVal(input);
                if(update){
                    cout << "Item [" << input << "] is deleted. ";
                    cout << "Updated list: \t" << endl << "↳ ";
                    if(!print(head)) break;
                }
                cout << endl << endl;
            } else {
                cout << "Program exited!";
            }
        }
    }
}