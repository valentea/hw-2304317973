#ifndef MOVIE_H
#define MOVIE_H

#include "product.h";


class Movie {
public:
    Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);

    std::set<std::string> keyWords();

    std::string displayString();

    void Movie::dump(std::ostream& os);



protected:
    std::string name_;
    double price_;
    int qty_;
    std::string category_;
    std::string genre_;
    std::string rating_;
};


#endif /
