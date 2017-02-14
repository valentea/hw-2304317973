#include "cnf.h"
using namespace std;

/**
 * Helper function to take the absolute value of an integer
 */
int intabs(int a)
{
    if(a < 0) return -a;
    return a;
}


Clause::Clause() : isTrue_(false)
{
}

Clause::Clause(const vector<int>& vars)
    : vars_(vars), isTrue_(false)
{

}
int Clause::eval(std::map<int,int>& varValues)
{
    /* You complete */



}


CNFFormula::CNFFormula(int nVars, const vector<Clause*>& clauses)
    : clauses_(clauses), numSatisfied_(0)
{
    /* You complete */


}

CNFFormula::~CNFFormula()
{
    /* You complete */


}

bool CNFFormula::isSatisfied() const
{
    return numSatisfied_ == clauses_.size();
}

void CNFFormula::printVarValues() const
{
    /* You complete */


}
void CNFFormula::assignVar(int var, int val)
{
    /* You complete */


}

