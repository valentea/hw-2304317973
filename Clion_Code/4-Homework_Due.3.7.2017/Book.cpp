#include "product.h"
#include "Book.h"
#include <set>
#include <sstream>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author) :
    Product(category, name, price, qty),
    isbn_(ISBN),
    author_(author)
{

}

std::string Book::displayString() const{
    std::string output;
    output = category_ + name_ + std::to_string(price_) + std::to_string(qty_) + isbn_ + author_;
    return output;
}

std::set<std::string> Book::keywords() const{
    std::set<std::string> keyWord;

    stringstream name(name_);
    string searchableTermName;
    while(name >> searchableTermName){
        keyWord.insert(searchableTermName);
    }

    keyWord.insert(isbn_);

    stringstream au(author_);
    string searchableTermAuthor;
    while(name >> searchableTermAuthor){
        keyWord.insert(searchableTermAuthor);
    }

    return keyWord;
}

void Book::dump(std::ostream& os) const{
    Product::dump(os);
    os << isbn_ << "\n" << author_ << endl;
}
