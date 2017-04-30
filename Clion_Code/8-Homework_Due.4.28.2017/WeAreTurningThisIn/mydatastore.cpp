#include "mydatastore.h"
#include <string>
#include <set>
#include <vector>
#include <climits>
#include <list>
#include <numeric>
#include "product.h"
#include "user.h"
#include "util.h"
#include "hash.h"

using namespace std;

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {

}

void MyDataStore::addProduct(Product *p) {
    productList_.insert(p); //ADD PROD TO productList_ (MyDataStore DATA MEMBER)
}

void MyDataStore::addUser(User *u) {
    userList_.insert(u); //ADD USER TO userList_ (MyDataStore DATA MEMBER)
    vector<Product *> emptyCart;
    pair<User *, vector<Product *> > personalCart; //FOR EVERY USER IN DataStore, MAKE A CART PAIR AND INSERT TO cart_
    personalCart.first = u;
    personalCart.second = emptyCart;
    cart_.insert(personalCart);

}

void MyDataStore::dump(std::ostream &ofile) {
    for(set<Product *>::iterator prodSingle = productList_.begin(); prodSingle != productList_.end(); prodSingle++){
        (*prodSingle)->dump(ofile); //LOOP THROUGH ALL AVALABLE PRODUCTS AND INSERT DATA TO ofile
    }

}

std::vector<Product *> MyDataStore::search(std::vector<std::string> &terms, int type) {
    std::set<std::set<std::string> > anything;
    vector<Product *> hits;

    set<string> termsSet;
    for (vector<string>::iterator test = terms.begin();
         test != terms.end(); test++) { //CHANGE THE VECTOR OF SEARCHED TERMS INTO A SET FOR THE SEARCH FNs
        termsSet.insert(*test);
    }

    if (type == 0) { //"AND" SEARCH
        for (set<Product *>::iterator singleProd = productList_.begin();
             singleProd != productList_.end(); singleProd++) { //CYCLE THROUGH EACH PRODUCT IN THE DATABASE
            set<string> singleProdKeyWords = (*singleProd)->keywords(); //GET KEYWORDS FOR SINGLE PROD
            set<string> outPut;
            outPut = setIntersection(singleProdKeyWords, termsSet); //SEE IF SEARCH TERMS BOTH SHOW UP IN PROD
            if (outPut.size() != 0) { //IF THERE IS ANYTHING IN THE OUTPUT THEN WE FOUND A MATCH
                hits.push_back(*singleProd);
            }
        }
        return hits;
    }

    if (type == 1) { //"OR" SEARCH
        for (set<Product *>::iterator singleProd = productList_.begin();
             singleProd != productList_.end(); singleProd++) { //CYCLE THROUGH EACH PRODUCT IN THE DATABASE
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

void MyDataStore::addToCart(string userName, Product *hit) {
    bool userFound = false;
    for (set<User *>::iterator user = userList_.begin();
         user != userList_.end(); user++) { //LOOP THROUGH ALL USERS IN DATA FILE
        if ((*user)->getName() == userName) { //AND FIND ONE THAT MATCHES SAME USERNAME
            userFound = true;
            map<User *, vector<Product *> >::iterator it;
            it = cart_.find(*user); //FIND THE SPECIFIC CART FOR GIVEN USER
            it->second.push_back(hit); //ADD hit PROD TO CART FOR GIVEN USER
        }
    }
    if (!userFound) {
        cout << "Invalid Request: Invalid Username" << endl;
    }
}

vector<Product *> MyDataStore::viewCart(std::string userName) {
    bool userFound = false;
    for (set<User *>::iterator user = userList_.begin();
         user != userList_.end(); user++) { //LOOP THROUGH ALL USERS IN DATA FILE
        if ((*user)->getName() == userName) { //AND FIND ONE THAT MATCHES SAME USERNAME
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
    for (set<User *>::iterator user = userList_.begin();
         user != userList_.end(); user++) { //LOOP THROUGH ALL USERS IN DATA FILE
        if ((*user)->getName() == userName) { //AND FIND ONE THAT MATCHES SAME USERNAME
            userFound = true;
            map<User *, vector<Product *> >::iterator it;
            it = cart_.find(*user); //LOOK AT SPESIFIC USER CART
            for (vector<Product *>::iterator singleProdFromCart = it->second.begin();
                 singleProdFromCart != it->second.end(); singleProdFromCart++) { //LOOP THROUGH ALL PRODUCTS IN CART
                if ((*user)->getBalance() >= (*singleProdFromCart)->getPrice() && (*singleProdFromCart)->getQty() >= 0) {
                    //CHECK TO SEE IF USER HAS ENOUGH MONEY, AND PRODUCT IS IN STOCK
                    (*user)->deductAmount((*singleProdFromCart)->getPrice()); //TAKE MONEY AWAY FROM USER'S CREDIT
                    set<Product *>::iterator prodFromList;
                    prodFromList = productList_.find(*singleProdFromCart); //GET THE PRODUCT (FROM productList) THAT IS BEING BOUGHT FROM THE CART
                    (*prodFromList)->subtractQty(1); //REDUCE ITS QUANTITY
                    it->second.erase(singleProdFromCart); //TAKE BOUGHT ITEM OUT OF CART
                    singleProdFromCart--; //BECAUSE PRODUCTS IN CART IS ONE SMALLER (DUE TO ONE LINE ABOVE) DON'T SHIFT ITERATOR OR IT GOES OUT OF BOUNDS
                }
            }
        }
    }
    if (!userFound) {
        cout << "Invalid Username" << endl;
        return;
    }
}

void MyDataStore::addReview(Review* r){
    reviewList_.insert(r);
    for(auto onePerson : userList_){
        if(r->username == onePerson->getName()){
            onePerson->addReview(r);
        }
    }
    for(auto oneProd : productList_){
        if(r->prodName == oneProd->getName()){
            oneProd->prodReviews.insert(r);
        }
    }
}

bool MyDataStore::checkPassword(std::string userName, std::string password) {
    unsigned long long hashedPassword = 0;
    hashedPassword = hasher(password);
    for(auto user : userList_){
        if(user->getName() == userName){
            if(user->getPassword() == hashedPassword){
                return true;
            }else{
            return false;
            }
        }
    }
}

User* MyDataStore::nameToUser(string name){
    for(auto user : userList_){
        if(user->getName() == name){
            return user;
        }
    }
    return NULL;
}

bool MyDataStore::userExist(std::string name) {
    for(auto user : userList_){
        if(user->getName() == name){
            return true;
        }
    }
    return false;
}

void MyDataStore::userSimilarity() {
    map<string, int> result;
    map<string, int>::iterator result_it(result.begin() );
    for(auto currUser : userList_){
        for(auto secondaryUser : userList_){
            if(currUser == secondaryUser){
                continue;
            }
            set_intersection( currUser->itemsReviewed.begin(), currUser->itemsReviewed.end(), secondaryUser->itemsReviewed.begin(),
                              secondaryUser->itemsReviewed.end(), inserter( result, result_it ) );
            if(result.empty()){
                currUser->addSimilarity(secondaryUser, 1);
                return;
            }
            double runningTotal = 0;
            vector<double > individalIdemSim;
            for (int i = 0; i < result.size(); ++i) {
                string name = (*result_it).first;
                int rating1 = currUser->itemsReviewed.at(name);
                int rating2 = secondaryUser->itemsReviewed.at(name);
                double temp = abs(rating1-rating2) / 4;
                individalIdemSim.push_back(temp);
            }
            for(auto it : individalIdemSim){
                runningTotal += it;
            }
            runningTotal = runningTotal/individalIdemSim.size();
            currUser->addSimilarity(secondaryUser, runningTotal);
        }
    }
}


void MyDataStore::findShortestPath(User* src, User* target){
    set<User* > path;
    findPath(src, target, src, path, 0);
}

void MyDataStore::findPath(User* src, User* targetUser, User* nextUser, set<User* >& path, double dist){
    if(src == targetUser){
        return;
    }
    for(auto snglUsr : nextUser->similarity){
        if(path.find(nameToUser(snglUsr.first)) != path.end()){
            continue;
        }
        set<User* > temp = path;
        temp.insert(nameToUser(snglUsr.first));
        double distToSib = dist + nextUser->similarity[snglUsr.first];
        if(snglUsr.first == targetUser->getName()){
            src->shortestDistence.insert(make_pair(snglUsr.first, distToSib));
        }else {
            findPath(src, targetUser,  nameToUser(snglUsr.first), temp, distToSib);
        }
    }
}

std::vector<std::pair<double, std::string> > MyDataStore::makeSuggestion(std::string currentUser) {
    vector<pair<double, std::string> > buyThese;
    User *currUser = nameToUser(currentUser);

    set<string> notReviewed;
    for(auto temp : productList_){
        notReviewed.insert(temp->getName());
    }

    for (auto temp1 : currUser->itemsReviewed) {
        notReviewed.erase(temp1.first);
    }




    for (auto singleProd : notReviewed) {
        vector<double> R;
        vector<double> W;
        for (auto singleUser : userList_) {
            for (auto singleReview : singleUser->itemsReviewed) {
                if (singleReview.first == singleProd) {
                    int rating = singleReview.second;
                    findShortestPath(currUser, singleUser);
                    double similarity = currUser->similarity[singleUser->getName()];
                    similarity = 1 - similarity;
                    double a = similarity * rating;
                    R.push_back(a);
                    W.push_back(similarity);
                }
            }
        }
        double rTotal = 0;
        accumulate(R.begin(), R.end(), rTotal);
        double wTotal = 0;
        accumulate(W.begin(), W.end(), rTotal);
        if (wTotal == 0) {
            buyThese.push_back(make_pair(0, singleProd));
        } else {
            double rating = rTotal / wTotal;
            buyThese.push_back((make_pair(rating, singleProd)));
        }
    }
    sort(buyThese.begin(), buyThese.end());
    
    return buyThese;
};
