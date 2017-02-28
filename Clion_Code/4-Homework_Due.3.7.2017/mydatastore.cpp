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
    productList_.insert(p);
}

void MyDataStore::addUser(User *u) {
    userList_.insert(u);
    vector<Product *> emptyCart;
    pair<User *, vector<Product *>> personalCart;
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
    for(auto test : terms){ //CHANGE THE VECTOR OF SEARCHED TERMS INTO A SET FOR THE SEARCH FNs
        termsSet.insert(test);
    }

    if(type == 0) { //"AND" SEARCH
        for (auto singleProd : productList_) { //CYCLE THROUGH EACH PRODUCT IN THE DATABASE
            set<string> singleProdKeyWords = singleProd->keywords(); //GET KEYWORDS FOR SINGLE PROD
            set<string> outPut;
            outPut = setIntersection(singleProdKeyWords, termsSet); //SEE IF SEARCH TERMS BOTH SHOW UP IN PROD
            if (outPut.size() != 0) { //IF THERE IS ANYTHING IN THE OUTPUT THEN WE FOUND A MATCH
                hits.push_back(singleProd);
            }
        }
        return hits;
    }

    if(type == 1){ //"OR" SEARCH
        for (auto singleProd : productList_) { //CYCLE THROUGH EACH PRODUCT IN THE DATABASE
            set<string> singleProdKeyWords = singleProd->keywords(); //GET KEYWORDS FOR SINGLE PROD
            set<string> outPut;
            outPut = setUnion(singleProdKeyWords, termsSet); //SEE IF ONE OF THE SEARCH TERMS SHOW UP IN PROD
            if (outPut.size() != 0) { //IF THERE IS ANYTHING IN THE OUTPUT THEN WE FOUND A MATCH
                hits.push_back(singleProd);
            }
        }
        return hits;
    }
    return hits;

}

void MyDataStore::addToCart(string userName, Product* hit) {
    bool userFound = false;
    for(auto user : userList_){
        if(user->getName() == userName){
            userFound = true;
            map<User *, vector<Product *>>::iterator it;
            it = cart_.find(user);
            it->second.push_back(hit);
        }
    }
    if(!userFound){
        cout << "Invalid Request: Invalid Username" << endl;
    }
}

vector<Product *> MyDataStore::viewCart(std::string userName) {
    bool userFound = false;
    for(auto user : userList_){
        if(user->getName() == userName){
            userFound = true;
            return cart_.find(user)->second;
        }
    }
    if(!userFound){
        cout << "Invalid Username" << endl;
    }
}

void MyDataStore::buyCart(string userName) {

    for(auto user : userList_){
        if(user->getName() == userName){
            double originalPrice = user->getBalance();
            map<User *, vector<Product *>>::iterator it;
            it = cart_.find(user);
            for(auto test : it->second){
                if(user->getBalance() > test->getPrice() || test->getQty() >= 0 ) {
                    user->deductAmount(test->getPrice());
                    test->subtractQty(1);
                }
            }
        }
    }
}