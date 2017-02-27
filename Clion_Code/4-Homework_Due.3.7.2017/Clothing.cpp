#include "Clothing.h"
#include "product.h"
#include "product_parser.h"
#include <set>
#include <sstream>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
        Product(category, name, price, qty),
        size_(size),
        brand_(brand)
{

}

std::set<std::string> Clothing::keywords() const{
    std::set<std::string> keyWord;

    stringstream name(name_);
    string searchableTermName;
    while(name >> searchableTermName){
        keyWord.insert(searchableTermName);
    }

    stringstream name1(brand_);
    string searchableTermBrand;
    while(name1 >> searchableTermBrand){
        keyWord.insert(searchableTermBrand);
    }

    return keyWord;
}

std::string Clothing::displayString() const{
    std::string output;
    output = category_ + name_ + std::to_string(price_) + std::to_string(qty_) + size_ + brand_;
    return output;
}





void Clothing::dump(std::ostream& os) const{
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
}