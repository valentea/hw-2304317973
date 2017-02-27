#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include "product_parser.h"


class Clothing : public Product{
public:
    Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);

    std::set<std::string> keywords() const;

    std::string displayString() const;

    void dump(std::ostream& os) const;



protected:
    std::string name_;
    double price_;
    int qty_;
    std::string category_;
    std::string size_;
    std::string brand_;
};

#endif //INC_4_HOMEWORK_DUE_3_7_2017_CLOTHING_H
