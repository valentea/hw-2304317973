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
    for(auto user : userList_){
        if(user->getName() == userName){
            vector<Product *> hitS;
            hitS.push_back(hit);
            cart_.insert(make_pair(user, hitS));
        }
    }
}

vector<Product *> MyDataStore::viewCart(std::string userName) {
    for(auto user : userList_){
        if(user->getName() == userName){
            return cart_.find(user)->second;
        }
    }
}