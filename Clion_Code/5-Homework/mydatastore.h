#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "review.h"

/**
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 */
class MyDataStore : public DataStore{
public:
    MyDataStore();

    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addToCart(std::string userName, Product* hit);
    std::vector<Product *> viewCart(std::string userName);
    void buyCart(std::string userName);
    void addReview(Review* r);
    std::vector<std::string> userNames();
    void setCurrentUser(std::string userNameInput);

protected:
    User* currentUser_;
    std::set<Product *> productList_;
    std::set<User *> userList_;
    std::set<Review *> reviewList_;
    std::map<User *, std::vector<Product *> > cart_;
};

#endif

