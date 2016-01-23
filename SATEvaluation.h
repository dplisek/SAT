//
// Created by Dominik Plíšek on 22/01/16.
//

#ifndef PAA_EXAM_SATVALUES_H
#define PAA_EXAM_SATVALUES_H


#include "SATInstance.h"

class SATEvaluation {

    bool *values;
    bool *clausesTrue;
    SATInstance *instance;

    bool isClauseTrue(const SATClause *clause) const;

public:

    int satisfiedClauseCount;
    int weight;

    SATEvaluation(SATInstance *instance);
    virtual ~SATEvaluation();

    void randomize();
    void toggleVariable(int index);
    bool isSatisfied();

    SATEvaluation& operator=(const SATEvaluation &other);

    friend istream& operator >> (istream& in, SATClause &clause);
};


#endif //PAA_EXAM_SATVALUES_H
