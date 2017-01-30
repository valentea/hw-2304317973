#include <iostream>
#include <fstream>

using namespace std;

struct Item{
    int val;
    Item* next;
};

Item* concatenate(Item* head1, Item* head2);
void removeEvens(Item*& head);
double findAverage(Item* head);
void constructList(Item* head, int val);

//Item *concatenate(Item* head1, Item* head2){
//    Item* temp;
//    if(head1 != NULL){
//        concatenate(head1->next, head2);
//    } else{
//        head2 = head1;
//        return head2;
//    }
//}

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
    if(argc > 2){
        cerr << "Only need input.in" << endl;
        return 1;
    }

    ifstream ifile(argv[1]);
    if(ifile.fail()){
        cerr << "Error" << endl;
        return 1;
    }

    Item* headListOne = NULL;
    Item* headListTwo = NULL;
    constructList(headListOne, 10);

    return 7;



}