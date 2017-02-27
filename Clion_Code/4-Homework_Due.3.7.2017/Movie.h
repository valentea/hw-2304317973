#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include "product_parser.h"


class Movie : public Product{
public:
    Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);

    std::set<std::string> keywords() const;

    std::string displayString() const;

    void dump(std::ostream& os) const;



protected:
    std::string name_;
    double price_;
    int qty_;
    std::string category_;
    std::string genre_;
    std::string rating_;
};


#endif
