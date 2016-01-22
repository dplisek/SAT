//
// Created by Dominik Plíšek on 22/01/16.
//

#include <iostream>
#include "SATClause.h"

istream &operator>>(istream &in, SATClause &clause) {
    for (int i = 0; i < clause.clauseSize; ++i) {
        int var;
        in >> var;
        clause.variables[i] = abs(var) - 1; // we index from 0
        clause.positive[i] = var > 0;
    }
    int term;
    in >> term;
    if (term != 0) {
        cerr << "Error while reading clause, missing terminator 0." << endl;
        exit(EXIT_FAILURE);
    }
    return in;
}

SATClause::SATClause(int clauseSize, int index) : clauseSize(clauseSize), index(index) {
    variables = new int[clauseSize];
    positive = new bool[clauseSize];
}

SATClause::~SATClause() {
    delete [] variables;
    delete [] positive;
}
