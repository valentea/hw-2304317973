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

Item* concatenate(Item* head1, Item* head2) {
    if (head1 != NULL){
        return concatenate(head1->next, head2);
    }
    else{
        head1 = head2;
        return head1;
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
    cout << "list One" << endl;
    while (numberListOne >> addNumber){
        constructList(headListOne, addNumber);
        cout << headListOne->val << endl;
        headListOne = headListOne->next;
    }
    getline(ifile, temp);
    cout << "list Two" << endl;
    stringstream numberListTwo(temp);
    while (numberListTwo >> addNumber){
        constructList(headListTwo, addNumber);
        cout << headListTwo->val << endl;
        headListTwo = headListTwo->next;
    }

    //MAKE ONE BIG LIST
    Item* bigList = concatenate(headListOne, headListTwo);
    cout << "BigList" << endl;
    while(bigList != NULL){
        cout << bigList->val << endl;
        bigList = bigList->next;
    }
    cout << "end of BigList" << endl;

    return 7;


}