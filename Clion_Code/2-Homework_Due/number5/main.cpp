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
void printList(std::ostream& ofile, Item* head);

int listLength(Item* head){
    Item* temp = head;
    int count = 0;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    return count;
}

void printList(std::ostream& ofile, Item* head)
{
    if(head == NULL)
        ofile << std::endl;
    else {
        ofile << head->val << " ";
        printList(ofile, head->next);
    }
}


double findAverage(Item* head){
    double runningTotal = 0;
    if (head == NULL) {
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
    if (argc > 3) {
        cerr << "Only need input.txt and output.txt" << endl;
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
    if(0 == listLength(headListOne)){
        cout << "average: 0.0" << endl;
        return 1;
    }
    getline(ifile, temp);
    stringstream numberListTwo(temp);
    while (numberListTwo >> addNumber){
        constructList(headListTwo, addNumber);
    }

    ofstream outFile;
    outFile.open(argv[2]);

    //MAKE ONE BIG LIST
    Item* bigList = concatenate(headListOne, headListTwo);
    printList(outFile, bigList);


    //REMOVE ALL EVEN NUMBERS
    removeEvens(bigList);
    printList(outFile, bigList);



    //FIND AVERAGE
    double totalSum = findAverage(bigList);
    int length = listLength(bigList);
    double average = totalSum / length;
    cout << "average: " << average << endl;
    printList(outFile, bigList);

    outFile.close();


    return 1;


}