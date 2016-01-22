//
// Created by Dominik Plíšek on 22/01/16.
//

#ifndef PAA_EXAM_CLAUSE_H
#define PAA_EXAM_CLAUSE_H

#import <istream>

using namespace std;

class SATClause {

    int clauseSize;

public:

    int index;
    int *variables;
    bool *positive;

    SATClause(int clauseSize, int index);
    virtual ~SATClause();

    friend istream& operator >> (istream& in, SATClause &clause);

};


#endif //PAA_EXAM_CLAUSE_H
