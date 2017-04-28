#include "Movie.h"
#include "product.h"
#include "util.h"
#include <set>
#include <sstream>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
        Product(category, name, price, qty),
        category_(category),
        name_(name),
        price_(price),
        qty_(qty),
        genre_(genre),
        rating_(rating)
{

}

std::set<std::string> Movie::keywords() const{
    std::set<std::string> keyWord; //INITIALIZE SET WITH ALL KEYWORDS


    set<string> searchableName;
    searchableName = parseStringToWords(name_); //TURN ALL PARTS OF THE NAME IN TO SEARCHABLE TERMS
    for (set<string>::iterator itN = searchableName.begin(); itN != searchableName.end(); itN++) {
        keyWord.insert(*itN); //INSERT ALL SEARCHABLE TERMS TO KEYWORDS FOR MOVIE
    }

    set<string> searchableGenre;
    searchableGenre = parseStringToWords(genre_); //TURN ALL PARTS OF THE GENRE IN TO SEARCHABLE TERMS
    for (set<string>::iterator itG = searchableGenre.begin(); itG != searchableGenre.end(); itG++) {
        keyWord.insert(*itG); //INSERT ALL SEARCHABLE TERMS TO KEYWORDS FOR MOVIE
    }

    return keyWord;
}

std::string Movie::displayString() const{
    std::string output;
    string priceS;
    priceS = to_string(price_);
    priceS.resize(5);
    output = name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + priceS + " " + std::to_string(qty_) + " left.";
    return output;
}

void Movie::dump(std::ostream& os) const{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}