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
    add(10);
    add(20);
    add(30);
    add(40);
    add(50);
    print(head);
    linearSearch(30);
}