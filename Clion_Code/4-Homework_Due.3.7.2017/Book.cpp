#include "product.h"
#include "product_parser.h"
#include "Book.h"
#include <set>
#include <sstream>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author) :
    Product(category, name, price, qty),
    ISBN_(ISBN),
    author_(author)
{

}

std::set<std::string> Book::keyWords(){
    std::set<std::string> keyWord;
    keyWord.insert(category_);

    stringstream name(name_);
    string searchableTermName;
    while(name >> searchableTermName){
        keyWord.insert(searchableTermName);
    }

    keyWord.insert(ISBN_);

    stringstream au(author_);
    string searchableTermAuthor;
    while(name >> searchableTermAuthor){
        keyWord.insert(searchableTermAuthor);
    }

    return keyWord;
}

std::string Book::displayString(){
    std::string output;
    output = category_ + name_ + std::to_string(price_) + qty_ + ISBN_ + author_;
    return output;
}





void Book::dump(std::ostream& os){
    Product::dump(os);
    os << ISBN_ << "\n" << author_ << endl;
}