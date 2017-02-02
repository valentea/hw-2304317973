#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

struct Item{
    Item(int v, Item* n) { val = v; next = n; }
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
        return runningTotal + head->val + findAverage(head->next);
    }
}




void removeEvens(Item* &head) {
    if (head == NULL) {
        return;
    }
    else{
        if ((head->val % 2) == 0) {
            Item* deleteNode = new Item(NULL, NULL);
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

Item* concatenate(Item* head1, Item* head2) {

    if (head1 == NULL) return head2;
    else if (head2 == NULL) return head1;

    else if (head1->val != NULL && head2->val != NULL) {
        head1->next = concatenate(head1->next, head2);
        return head1;
    } else {
        head2->next = concatenate(head2->next, head1);
        return head2;
    }
}

void constructList(Item* &head, int val){
    Item* newHead = new Item(NULL, NULL);
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

    if(0 == listLength(headListOne) || 0 == listLength(headListTwo)){
        printList(outFile, bigList);
        outFile << fixed << setprecision(2) << 0;
        cout << "average: " << fixed << setprecision(2) << 0;
        return 1;
    }


    //FIND AVERAGE
    double average  = findAverage(bigList) / listLength(bigList);
    cout << "average: " << fixed << setprecision(1) <<  average << endl;
    printList(outFile, bigList);
    outFile << fixed << setprecision(1) << average;
    outFile.close();

    while(NULL != headListOne){
        Item* temp  = headListOne;
        headListOne = headListOne->next;
        delete temp;
    }
    while(NULL != headListTwo){
        delete[] headListTwo;
        headListTwo = headListTwo->next;
    }


    return 99;


}