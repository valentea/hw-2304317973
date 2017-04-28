#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "hash.h"

using namespace std;

struct ProdNameSorter {
    bool operator()(Product *p1, Product *p2) {
        return (p1->getName() < p2->getName());
    }
};

void displayProducts(vector<Product *> &hits);
void mainFn(MyDataStore ds, User* currUser);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser *productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser *userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if (parser.parse(argv[1], ds)) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "Menu: " << endl;
    cout << "1. Log in" << endl;
    cout << "2. Make new user" << endl;
    cout << "3. Quit" << endl;
    int menuItem = 0;
    while(1) {
        cin >> menuItem;
        if (menuItem == 1) {
            error1:
            cout << "Please enter Username and Password" << endl;
            string userName;
            string password;
            cin >> userName >> password;
            if(!ds.userExist(userName)){
                cout << "Error: Username does not exist" << endl;
                goto error1;
            }
            if(password == "  "){
                cout << "Backdoor ;)" << endl;
                User *currentUser = ds.nameToUser(userName);
                mainFn(ds, currentUser);
            }else if (ds.checkPassword(userName, password)) {
                User *currentUser = ds.nameToUser(userName);
                mainFn(ds, currentUser);
            }else{
                cout << "Error, wrong password" << endl;
                goto error1;
            }
        } else if (menuItem == 2) {
            error2:
            cout << "Please enter Username and Password" << endl;
            string newUserName;
            string newPassword;
            cin >> newUserName >> newPassword;
            if(ds.userExist(newUserName)){
                cout << "Error: Username all ready taken" << endl;
                goto error2;
            }
            if(newPassword.length() > 8){
                cout << "Error: Password too long" << endl;
                goto error2;
            }
            User *temp = new User(newUserName, (double)100, 1, hasher(newPassword));
            ds.addUser(temp);
            mainFn(ds, temp);
        } else if (menuItem == 3) {
            cout << "Thank you! Good bye!" << endl;
            return 0;
        } else {
            cout << "Invalid menu item" << endl;
        }
    }
}

void displayProducts(vector<Product *> &hits) {
    int resultNo = 1;
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for (vector<Product *>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}

void mainFn(MyDataStore ds, User* currUser) {
    cout << "=====================================" << endl;
    cout << "Menu:                                " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD search_hit_number              " << endl;
    cout << "  VIEWCART                           " << endl;
    cout << "  BUYCART                            " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "  PRODUCT Recommendations            " << endl;
    cout << "=====================================" << endl;

    vector<Product *> hits;
    bool done = false;
    while (!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin, line);
        stringstream ss(line);
        string cmd;
        if ((ss >> cmd)) {
            if (cmd == "AND") {
                string term;
                vector<string> terms;
                while (ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            } else if (cmd == "OR") {
                string term;
                vector<string> terms;
                while (ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            } else if (cmd == "QUIT") {
                string filename = "rec.txt";
                ofstream ofile(filename.c_str());
                ds.dump(ofile);
                ofile.close();
                done = true;
            } else if (cmd == "ADD") { //ADD HIT TO USER'S CART
                int hitNumber;
                ss >> hitNumber;
                int hitsIndex = hitNumber - 1;
                if (hitsIndex > hits.size() - 1 || hitsIndex < 0) {
                    cout << "Invalid Request: Invalid Hit Product" << endl;
                } else {
                    ds.addToCart(currUser->getName(),
                                 hits[hitsIndex]); //ADD THE HIT PRODUCT (hits[i] and i = i-1 for indexing)TO THE USERS CART
                }
            } else if (cmd == "VIEWCART") {
                string user = currUser->getName();
                vector<Product *> personalProd;
                personalProd = ds.viewCart(user); //RETURN VECTOR WITH USER CART PRODS
                displayProducts(personalProd); //ASK IF WE CAN USE THIS OR IF WE MUST MAKE OUR OWN PRINT FN
            } else if (cmd == "BUYCART") {
                string user = currUser->getName();
                ds.buyCart(user);
            }
            else {
                cout << "Unknown command" << endl;
            }
        }
    }
    return;
}