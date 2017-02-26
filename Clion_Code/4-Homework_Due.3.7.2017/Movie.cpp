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

std::set<std::string> Movie::keyWords(){
    std::set<std::string> keyWord;
    keyWord.insert(category_);

    stringstream name(name_);
    string searchableTermName;
    while(name >> searchableTermName){
        keyWord.insert(searchableTermName);
    }

    keyWord.insert(genre_);

    return keyWord;
}

std::string Movie::displayString(){
    std::string output;
    output = category_ + name_ + std::to_string(price_) + qty_ + ISBN_ + author_;
    return output;
}





void Book::dump(std::ostream& os){
    Product::dump(os);
    os << ISBN_ << "\n" << author_ << endl;
}