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
        head = tail = new NODE;
        head->data = value;
        head->prev = head->next = tail;
    } else {
        prevnode = tail;
        tail->next = head->prev = new NODE;
        tail = tail->next;
        tail->prev = prevnode;
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
    add(10);
    add(20);
    add(30);
    add(40);
    add(50);
    print(head);
    linearSearch(50);
}