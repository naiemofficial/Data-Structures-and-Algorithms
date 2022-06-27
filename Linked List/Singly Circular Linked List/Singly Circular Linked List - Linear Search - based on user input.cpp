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

void linearSearch(int search){
    if(head == 0){
        cout << "A search couldn't be completed in an empty list.";
    } else {
        temp = head;
        int result = 0, i = 1;
        do {
            if(temp->data == search){
                result = i;
                break;
            }
            temp = temp->next;
            i++;
        } while(temp != head);

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