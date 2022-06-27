#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *prev;
    NODE *next;
};

NODE *head, *tail, *prevnode, *temp;
void add(int value){
    if(head == NULL){
        head = new NODE;
        head->data = value;
        head->next = 0;
        tail = head;
    } else {
        prevnode = tail;
        tail->next = new NODE;
        tail = tail->next;
        tail->prev = prevnode;
        tail->data = value;
        tail->next = 0;
    }
}

void linearSearch(int search){
    if(head == 0){
        cout << "A search couldn't be completed in an empty list.";
    } else {
        temp = head;
        int result = 0;
        for(int i = 1; temp != 0; i++){
            if(temp->data == search){
                result = i;
                break;
            }
            temp = temp->next;
        }

        if(result > 0){
            cout << "The value [" << search << "] is matched with the [NODE-" << result << "]";
        } else {
            cout << "The value [" << search << "] didn't match with any node in the list.";
        }

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
    cout << endl << "List: ";
    if(print(head)){
        cout << endl << endl;

        cout << "-----------------------------------------" << endl;
        cout << "Note! Enter zero (0) to end the program. " << endl;
        input = 1;
        while(true){
            cout << "Enter a value to be searched: ";
            cin >> input;
            if(input != 0){
                linearSearch(input);
                cout << endl << endl;
            } else {
                cout << "Program exited!";
                break;
            }
        }
    }
}