#include "mydatastore.h"
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"

using namespace std;

MyDataStore::MyDataStore(){
    productList_;
    userList_;
}

void MyDataStore::addProduct(Product *p) {
    productList_.insert(p);
}

void MyDataStore::addUser(User *u) {
    userList_.insert(u);
}

//virtual std::vector<Product*> search(std::vector<std::string>& terms, int type) = 0;

//virtual void dump(std::ostream& ofile) = 0;

std::vector<Product *> search(std::vector<std::string>& terms, int type){

}

