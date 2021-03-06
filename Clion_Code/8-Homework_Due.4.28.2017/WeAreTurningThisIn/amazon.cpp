#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <QApplication>
#include <QWidget>
#include <QObject>

#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "loginWindow.h"
#include "review.h"

using namespace std;

struct ProdNameSorter {
    bool operator()(Product *p1, Product *p2) {
        return (p1->getName() < p2->getName());
    }
};

void displayProducts(vector<Product *> &hits);
void mainFn(MyDataStore ds);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore* ds = new MyDataStore;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;
    ReviewSectionParser* reviewSectionParser = new ReviewSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);
    parser.addSectionParser("reviews", reviewSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], *ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }
    
        vector<pair<double, string> > test = ds->makeSuggestion("saty");
    for(auto temp : test){
        cout << temp.second << endl;
    }


   QApplication app(argc, argv);
    loginWindow* window = new loginWindow(ds);

    window->show();
    return app.exec();


    return 0;
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

void mainFn(MyDataStore ds) {
    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

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
                string filename;
                if (ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            } else if (cmd == "ADD") { //ADD HIT TO USER'S CART
                string term;
                vector<string> terms;
                while (ss >> term) {
                    terms.push_back(term);
                }
                int hitsIndex = stoi(terms[1]) - 1;
                if (hitsIndex > hits.size() - 1 || hitsIndex < 0) {
                    cout << "Invalid Request: Invalid Hit Product" << endl;
                } else {
                    ds.addToCart(terms[0],
                                 hits[hitsIndex]); //ADD THE HIT PRODUCT (hits[i] and i = i-1 for indexing)TO THE USERS CART
                }
            } else if (cmd == "VIEWCART") {
                string user;
                ss >> user;
                vector<Product *> personalProd;
                personalProd = ds.viewCart(user); //RETURN VECTOR WITH USER CART PRODS
                displayProducts(personalProd); //ASK IF WE CAN USE THIS OR IF WE MUST MAKE OUR OWN PRINT FN
            } else if (cmd == "BUYCART") {
                string user;
                ss >> user;
                ds.buyCart(user);
            }
            else {
                cout << "Unknown command" << endl;
            }
        }

    }
}

