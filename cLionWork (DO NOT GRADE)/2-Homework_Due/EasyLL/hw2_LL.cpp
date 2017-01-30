#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Item{
    int val;
    Item* next;
};

Item* concatenate(Item* head1, Item* head2);
void removeEvens(Item*& head);
double findAverage(Item* head);
void constructList(Item* &head, int val);

int count = 0;
void removeEvens(Item* &head) {
    while (head != NULL) {
        cout << "count " << count << endl;
        cout << "Bool Val: " << head.v
             << endl;
        if ((head->val % 2) == 0) {
            removeEvens(head->next->next);
            count++;
        } else {
            removeEvens(head->next);
            count++;
        }
    }
        return;

}

Item* concatenate(Item* head1, Item* head2) {
    Item* bigList = head1;
    if(head1 != NULL){
        head1->next = concatenate(head1->next, head2);
        return head1;
    }
    else if(head1==NULL && head2 != NULL){
        head2->next = concatenate(head1, head2->next);
        return head2;
    }
}

void constructList(Item* &head, int val){
    Item* newHead = new Item;
    newHead->val = val;
    newHead->next = NULL;
    if(head == NULL){
        head = newHead;
    }
    else{
        Item* temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newHead;
    }
    return;
}




int main(int argc, char* argv[]) {
    if (argc > 2) {
        cerr << "Only need input.in" << endl;
        return 1;
    }

    ifstream ifile(argv[1]);
    if (ifile.fail()) {
        cerr << "Error" << endl;
        return 1;
    }

    Item *headListOne = NULL;
    Item *headListTwo = NULL;
    string temp;
    //MAKE ORIGINAL TWO LL
    getline(ifile, temp);
    int addNumber;
    stringstream numberListOne(temp);
    while (numberListOne >> addNumber){
        constructList(headListOne, addNumber);
    }
    getline(ifile, temp);
    stringstream numberListTwo(temp);
    while (numberListTwo >> addNumber){
        constructList(headListTwo, addNumber);
    }

    //MAKE ONE BIG LIST
    Item* bigList = concatenate(headListOne, headListTwo);

    //REMOVE ALL EVEN NUMBERS
    removeEvens(bigList);
    cout << "bigList" << endl;
    while(bigList!=NULL){
        cout << bigList->val << endl;
        bigList = bigList->next;
    }


    return 7;


}