#include "Movie.h"
#include "product.h"
#include "product_parser.h"
#include <set>
#include <sstream>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
        Product(category, name, price, qty),
        genre_(genre),
        rating_(rating)
{

}

std::set<std::string> Movie::keywords() const{
    std::set<std::string> keyWord;

    stringstream name(name_);
    string searchableTermName;
    while(name >> searchableTermName){
        keyWord.insert(searchableTermName);
    }

    keyWord.insert(genre_);

    return keyWord;
}

std::string Movie::displayString() const{
    std::string output;
    output = category_ + name_ + std::to_string(price_) + std::to_string(qty_) + genre_ + rating_;
    return output;
}

void Movie::dump(std::ostream& os) const{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}