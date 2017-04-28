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

    QApplication app(argc, argv);
    QWidget *window = new QWidget;

    QPushButton *logIn = new QPushButton("Log In");
    QPushButton *newUser = new QPushButton("Make New User");
    QPushButton *quit = new QPushButton("Quit");
    QLineEdit *userName = new QLineEdit("User Name");
    QLineEdit *password = new QLineEdit("Password");

    QGridLayout *grid = new QGridLayout;
    QHBoxLayout *topLine = new QHBoxLayout;
    QHBoxLayout *bottomLine = new QHBoxLayout;

    topLine->addWidget(userName);
    topLine->addWidget(password);

    bottomLine->addWidget(logIn);
    bottomLine->addWidget(newUser);
    bottomLine->addWidget(quit);

    grid->addLayout(topLine, 0, 0);
    grid->addLayout(bottomLine, 1, 0);

    window->setLayout(grid);
    window->show();

    string usernameRaw = (newUser->text()).toStdString();
    string passwordRaw = (password->text()).toStdString();


    QObject::connect(quit, SIGNAL(clicked()), &app, SLOT(quit()));
    QObject::connect(logIn, SIGNAL(clicked()), userName, SLOT());

    return app.exec();


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
