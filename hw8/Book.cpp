#include "product.h"
#include "Book.h"
#include "util.h"
#include <set>
#include <sstream>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author) :
    Product(category, name, price, qty),
    category_(category),
    name_(name),
    price_(price),
    qty_(qty),
    isbn_(ISBN),
    author_(author)
{

}

std::string Book::displayString() const{
    std::string output;
    string priceS = to_string(price_);
    priceS.resize(5);
    output = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" +  priceS + " " + to_string(qty_) + " left.";
    return output;
}

std::set<std::string> Book::keywords() const{
    std::set<std::string> keyWord;

    set<string> searchableName;
    searchableName = parseStringToWords(name_); //TURN ALL PARTS OF THE NAME IN TO SEARCHABLE TERMS
    for (set<string>::iterator itN = searchableName.begin(); itN != searchableName.end(); itN++) {
        keyWord.insert(*itN); //INSERT ALL SEARCHABLE TERMS TO KEYWORDS FOR MOVIE
    }

    set<string> searchableAuthor;
    searchableAuthor = parseStringToWords(author_); //TURN ALL PARTS OF THE AUTHOR IN TO SEARCHABLE TERMS
    for (set<string>::iterator itG = searchableAuthor.begin(); itG != searchableAuthor.end(); itG++) {
        keyWord.insert(*itG); //INSERT ALL SEARCHABLE TERMS TO KEYWORDS FOR MOVIE
    }

    keyWord.insert(isbn_); //INSERT ISBN AS IS

    return keyWord;
}

void Book::dump(std::ostream& os) const{
    Product::dump(os);
    os << isbn_ << "\n" << author_ << endl;
}
