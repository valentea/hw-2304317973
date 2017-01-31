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
int listLength(Item* head);

int listLength(Item* head){
    Item* temp = head;
    int count = 0;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    return count;
}


double findAverage(Item* head){
    double runningTotal = 0;
    if (head == NULL) {
        cout << "exit here" << endl;
        return runningTotal;
    }
    else {
        runningTotal = head->val + findAverage(head->next);
        return runningTotal;
    }
}

void removeEvens(Item* &head) {
    if (head == NULL) {
        return;
    }
    else{
        if ((head->val % 2) == 0) {
            Item* deleteNode = new Item;
            deleteNode = head->next;
            head = deleteNode;
            removeEvens(head);
        } else{
            removeEvens(head->next);
            return;

        }
    }
    return;
}

//Item* concatenate(Item* head1, Item* head2) {
//
//    if (head1 == NULL) return head2;
//    else if (head2 == NULL) return head1;
//
//    else if (head1 != NULL && head2->val != NULL) {
//        head1->next = concatenate(head1->next, head2);
//        return head1;
//    } else {
//        head2->next = concatenate(head2->next, head1);
//        return head2;
//    }
//}

Item* concatenate(Item* list1, Item* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    if (list1->val < list2->val) {
        list1->next = concatenate(list1->next, list2);
        return list1;
    } else {
        list2->next = concatenate(list2->next, list1);
        return list2;
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
    cout << "makes it this far" << endl;
    while (numberListOne >> addNumber){
        cout << "makes it this far 1" << endl;
        cout << "addNumber: " << addNumber << endl;
        constructList(headListOne, addNumber);
    }
    cout << "makes it this far 2" << endl;
    getline(ifile, temp);
    cout << "makes it this far 3" << endl;
    stringstream numberListTwo(temp);
    while (numberListTwo >> addNumber){
        cout << "makes it this far 4" << endl;
        constructList(headListTwo, addNumber);
    }

    //MAKE ONE BIG LIST
    cout << "makes it this far 5" << endl;
    Item* bigList = concatenate(headListOne, headListTwo);
    cout << "makes it this far 6" << endl;



    //REMOVE ALL EVEN NUMBERS
    removeEvens(bigList);
    cout << "makes it this far 7" << endl;



    //FIND AVERAGE
    double totalSum = findAverage(bigList);
    int length = listLength(bigList);
    double average = totalSum / length;
    cout << "average: " << average << endl;

    return 4;


}