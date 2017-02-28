#include "mydatastore.h"
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore(){

}

MyDataStore::~MyDataStore() {

}

void MyDataStore::addProduct(Product *p) {
    productList_.insert(p); //ADD PROD TO productList_ (MyDataStore DATA MEMBER)
}

void MyDataStore::addUser(User *u) {
    userList_.insert(u); //ADD USER TO userList_ (MyDataStore DATA MEMBER)
    vector<Product *> emptyCart;
    pair<User *, vector<Product *>> personalCart; //FOR EVERY USER IN DataStore, MAKE A CART PAIR AND INSERT TO cart_
    personalCart.first = u;
    personalCart.second = emptyCart;
    cart_.insert(personalCart);

}

void MyDataStore::dump(std::ostream& ofile){

}

std::vector<Product*> MyDataStore::search(std::vector<std::string> &terms, int type) {
    std::set<std::set<std::string>> anything;
    vector<Product *> hits;

    set<string> termsSet;
    for(vector<string>::iterator test = terms.begin(); test != terms.end(); test++){ //CHANGE THE VECTOR OF SEARCHED TERMS INTO A SET FOR THE SEARCH FNs
        termsSet.insert(*test);
    }

    if(type == 0) { //"AND" SEARCH
        for (set<Product *>::iterator singleProd = productList_.begin(); singleProd != productList_.end(); singleProd++) { //CYCLE THROUGH EACH PRODUCT IN THE DATABASE
            set<string> singleProdKeyWords = (*singleProd)->keywords(); //GET KEYWORDS FOR SINGLE PROD
            set<string> outPut;
            outPut = setIntersection(singleProdKeyWords, termsSet); //SEE IF SEARCH TERMS BOTH SHOW UP IN PROD
            if (outPut.size() != 0) { //IF THERE IS ANYTHING IN THE OUTPUT THEN WE FOUND A MATCH
                hits.push_back(*singleProd);
            }
        }
        return hits;
    }

    if(type == 1){ //"OR" SEARCH
        for (set<Product *>::iterator singleProd = productList_.begin(); singleProd != productList_.end(); singleProd++) { //CYCLE THROUGH EACH PRODUCT IN THE DATABASE
            set<string> singleProdKeyWords = (*singleProd)->keywords(); //GET KEYWORDS FOR SINGLE PROD
            set<string> outPut;
            outPut = setUnion(singleProdKeyWords, termsSet); //SEE IF ONE OF THE SEARCH TERMS SHOW UP IN PROD
            if (outPut.size() != 0) { //IF THERE IS ANYTHING IN THE OUTPUT THEN WE FOUND A MATCH
                hits.push_back(*singleProd);
            }
        }
        return hits;
    }
    return hits;

}

void MyDataStore::addToCart(string userName, Product* hit) {
    bool userFound = false;
    for(set<User *>::iterator user = userList_.begin(); user != userList_.end(); user++){ //LOOP THROUGH ALL USERS IN DATA FILE
        if((*user)->getName() == userName){ //AND FIND ONE THAT MATCHES SAME USERNAME
            userFound = true;
            map<User *, vector<Product *>>::iterator it;
            it = cart_.find(*user); //FIND THE SPECIFIC CART FOR GIVEN USER
            it->second.push_back(hit); //ADD hit PROD TO CART FOR GIVEN USER
        }
    }
    if(!userFound){
        cout << "Invalid Request: Invalid Username" << endl;
    }
}

vector<Product *> MyDataStore::viewCart(std::string userName) {
    bool userFound = false;
    for(set<User *>::iterator user = userList_.begin(); user != userList_.end(); user++){ //LOOP THROUGH ALL USERS IN DATA FILE
        if((*user)->getName() == userName){ //AND FIND ONE THAT MATCHES SAME USERNAME
            userFound = true;
            return cart_.find(*user)->second; //RETURN THIS USERS CART TO BE PRINTED IN main()
        }
    }
    if(!userFound){
        cout << "Invalid Username" << endl;
        vector<Product *> emptyVecForUsernameFail; //RETURNS EMPTY VECTOR SO THERE IS NO SEGFAULT WHEN ATTEMPING TO PRINT
        return emptyVecForUsernameFail;
    }
}

void MyDataStore::buyCart(string userName) {
    bool userFound = false;
    for (set<User *>::iterator user = userList_.begin(); user != userList_.end(); user++) { //LOOP THROUGH ALL USERS IN DATA FILE
        if ((*user)->getName() == userName) { //AND FIND ONE THAT MATCHES SAME USERNAME
            userFound = true;
            map<User *, vector<Product *>>::iterator it;
            it = cart_.find(*user); //LOOK AT SPESIFIC USER CART
            for (vector<Product *>::iterator singleProdFromCart = it->second.begin(); singleProdFromCart != it->second.end();) { //LOOP THROUGH ALL PRODUCTS IN CART
                if ((*user)->getBalance() >= (*singleProdFromCart)->getPrice() && (*singleProdFromCart)->getQty() >= 0) { //CHECK TO SEE IF USER HAS ENOUGH MONEY, AND PRODUCT IS IN STOCK
                    (*user)->deductAmount((*singleProdFromCart)->getPrice()); //TAKE MONEY AWAY FROM USER'S CREDIT
                    cout << (*user)->getName() << " credit is: " << (*user)->getBalance() << endl;
/*LOOK AT THIS*/    (productList_.find(*singleProdFromCart)).operator*()->subtractQty(1); //NOT WORKING: DOES NOT TAKE FROM productList_->qty_ ONLY TAKES FROM STACK BUT RESETS WHEN BACK IN MAIN
                    cout << (productList_.find(*singleProdFromCart)).operator*()->getQty() << endl;
                    it->second.erase(singleProdFromCart);
                }
            }
        }
    }
    if(!userFound){
        cout << "Invalid Username" << endl;
    }
}

