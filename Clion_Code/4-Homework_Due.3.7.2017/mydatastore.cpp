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
    for(auto test : terms){
        termsSet.insert(test);
    }


    for(auto test : productList_){
        set<string> prodKeyWord = test->keywords();
        setIntersection(prodKeyWord, termsSet);

    }


}

std::set<Product> keyWordsToProduct(std::set<std::string> keyWords){

}
