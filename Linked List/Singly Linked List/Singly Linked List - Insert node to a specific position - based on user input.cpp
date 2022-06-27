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

int addTo(int position, int value){
    temp = head;
    if(position >= 1){    
        for(int i = 1; i < position-1; i++){
            temp = temp->next; // point to position immediate previous node
            if(temp == 0){
                break; 
            }
        }
        if(temp || position == 1){
            NODE *newnode = new NODE;
            newnode->data = value;
            if(position == 1){
                newnode->next = head;
                head = temp = newnode;
                if(head->next == 0) tail = head;
            } else {
                newnode->next = temp->next;
                temp->next = newnode;
                if(newnode->next == 0) tail = newnode;
            }
        }
    }
    if(position < 1 || temp == 0){
        cout << "Data not inserted. Invalid position [" << position <<"]." << endl;
        return false;
    }
    return true;
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
    int input = 1, position = 0;
    while(true){
        if(head == 0){
            cout << "Enter a value for the first/initial NODE: ";
            cin >> input;
        } else {
            cout << "Enter a position to add a new NODE: ";
            cin >> position;
            cout << "Enter a value for the position [" << position << "]: ";
            cin >> input;
        }

        if(input == 0){
            cout << "Program exited!" << endl;
            break;
        } else {
            bool added = true;
            if(head == 0){
                add(input);
            } else {
                added = addTo(position, input);
            }

            if(added){
                position = (position) ? position : ++position;
                cout << "Value [" << input << "] added at the position " << position << ". ";
                cout << "Updated list: \t" << endl << "↳ ";
                if(!print(head)) break;
            }
            cout << endl << endl;
        }
    }
}