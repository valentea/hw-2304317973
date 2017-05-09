#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "review.h"

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    User(std::string name, double balance, int type, unsigned long long password);
    virtual ~User();

    double getBalance() const;
    std::string getName() const;
    void deductAmount(double amt);
    virtual void dump(std::ostream& os);
    unsigned long long getPassword();
    void addReview(Review *);
    void addSimilarity(User*, double);

    std::map<std::string, int> itemsReviewed;
    std::map<std::string, double> similarity;
    std::map<std::string, double> shortestDistence;

private:
    std::string name_;
    double balance_;
    int type_;
    unsigned long long password_;
};
#endif
