#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include "product_parser.h"

class Book : public Product{
public:
    Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author);

    std::set<std::string> keyWords();

    std::string displayString();

    void Book::dump(std::ostream& os);



protected:
    std::string name_;
    double price_;
    int qty_;
    std::string category_;
    std::string ISBN_;
    std::string author_;
};


#endif //BOOK_H

