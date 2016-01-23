//
// Created by Dominik Plíšek on 22/01/16.
//

#ifndef PAA_EXAM_SATINSTANCE_H
#define PAA_EXAM_SATINSTANCE_H


static const int maxWeight = 10;
static const double warmingFactor = 1.5;

#include <vector>
#include "SATClause.h"

using namespace std;

class SATEvaluation;

class SATInstance {

    bool getLine(istream &in, string &line);

    void considerEvaluation(SATEvaluation &current, SATEvaluation &best, double temp, int &accepted, int &processed, bool simulation);
    bool acceptingEnough(int accepted, int processed);
    bool isFrozen(int accepted, int processed);

public:
    SATClause **clauses;
    vector<SATClause *> *clausePresence;
    int variableCount;
    int clauseCount;
    int clauseSize;
    int *weights;
    double coolingFactor;

    SATInstance(int clauseSize);
    virtual ~SATInstance();
    friend istream& operator >> (istream& in, SATInstance &instance);
    void solve();

    double getValueToOptimize(SATEvaluation &evaluation);

    void revert(SATEvaluation &evaluation, int index);
};


#endif //PAA_EXAM_SATINSTANCE_H
