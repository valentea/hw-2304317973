#include "Clothing.h"
#include "product.h"
#include "util.h"
#include <set>
#include <sstream>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
        Product(category, name, price, qty),
        category_(category),
        name_(name),
        price_(price),
        qty_(qty),
        size_(size),
        brand_(brand)
{

}

std::set<std::string> Clothing::keywords() const{
    std::set<std::string> keyWord;


    set<string> searchableName;
    searchableName = parseStringToWords(name_); //TURN ALL PARTS OF THE NAME IN TO SEARCHABLE TERMS
    for (set<string>::iterator itN = searchableName.begin(); itN != searchableName.end(); itN++) {
        keyWord.insert(*itN); //INSERT ALL SEARCHABLE TERMS TO KEYWORDS FOR MOVIE
    }

    set<string> searchableBrand;
    searchableBrand = parseStringToWords(brand_); //TURN ALL PARTS OF THE BRAND IN TO SEARCHABLE TERMS
    for (set<string>::iterator itG = searchableBrand.begin(); itG != searchableBrand.end(); itG++) {
        keyWord.insert(*itG); //INSERT ALL SEARCHABLE TERMS TO KEYWORDS FOR MOVIE
    }

    return keyWord;
}

std::string Clothing::displayString() const{
    std::string output;
    string priceS;
    priceS = to_string(price_);
    priceS.resize(5);
    output = name_ + "\nBrand: " + brand_ + " Size: " + size_ + "\n" + priceS + " " + std::to_string(qty_) + " left.";

    return output;
}





void Clothing::dump(std::ostream& os) const{
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
}