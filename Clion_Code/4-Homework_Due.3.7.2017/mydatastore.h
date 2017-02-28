#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"

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

    std::set<Product> keyWordsToProduct(std::set<std::string> keyWords);

protected:
    std::set<Product *> productList_;
    std::set<User *> userList_;
    std::map<User *, Product *> cart_;
};

#endif

