#include "cnf.h"

using namespace std;

/**
 * Helper function to take the absolute value of an integer
 */
int intabs(int a) {
    if (a < 0) return -a;
    return a;
}


Clause::Clause() : isTrue_(false) {
}

Clause::Clause(const vector<int> &vars)
        : vars_(vars), isTrue_(false) {

}

int Clause::eval(std::map<int, int> &varValues) {
    /* You complete */
    bool preChangeTruthVal = isTrue_;
    for (auto &variableInput: varValues) {
        for(auto statement: vars_){
            if(variableInput.first == intabs(statement)){
                if(variableInput.second == 0 && statement < 0){
                    isTrue_ = true;
                }
                if(variableInput.second == 1 && statement > 0){
                    isTrue_ = true;
                }
                if(variableInput.second == 0 && statement > 0){
                    isTrue_ = false;
                }
                if(variableInput.second == 1 && statement < 0){
                    isTrue_ = false;
                }
            }
        }
    }
    if(preChangeTruthVal == isTrue_){
        return UNK;
    }else if(isTrue_){
        return VAL1;
    }else{return VAL0;}
}


CNFFormula::CNFFormula(int nVars, const vector<Clause *> &clauses)
        : clauses_(clauses), numSatisfied_(0) {
    /* You complete */
    for(auto singleClause: clauses){
        vector<int> clauseVals = singleClause->vars();
        for(int trueVal: clauseVals){
            if(varToClauses_.size() == 0) {
                set<Clause *> temp;
                temp.insert(singleClause);
                varToClauses_.insert(make_pair(intabs(trueVal), temp));
            }else if(varToClauses_.find(intabs(trueVal)) == varToClauses_.end()){
                set<Clause *> temp;
                temp.insert(singleClause);
                varToClauses_.insert(make_pair(intabs(trueVal), temp));
            }else{for (auto &step: varToClauses_) {
                    if (step.first == intabs(trueVal)) {
                        step.second.insert(singleClause);
                    }
                }
            }
        }
    }

}

CNFFormula::~CNFFormula() {
    /* You complete */


}

bool CNFFormula::isSatisfied() const {
    return numSatisfied_ == clauses_.size();
}

void CNFFormula::printVarValues() const {
    /* You complete */
    for(auto sine: varValues_){
        std::cout << "Var " << sine.first << " : " << sine.second << std::endl;
    }
}

void CNFFormula::assignVar(int var, int val) {
    /* You complete */
    for(auto varClauses: varToClauses_.at(var)){
        varValues_.insert(make_pair(var,val));
        numSatisfied_ += varClauses->eval(varValues_);
    }
}

