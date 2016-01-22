//
// Created by Dominik Plíšek on 22/01/16.
//

#include "SATEvaluation.h"

SATEvaluation::SATEvaluation(SATInstance *instance) : instance(instance) {
    values = new bool[instance->variableCount];
    clausesTrue = new bool[instance->clauseCount];
}

SATEvaluation::~SATEvaluation() {
    delete [] values;
    delete [] clausesTrue;
}

void SATEvaluation::randomize() {
    satisfiedClauseCount = 0;
    weight = 0;
    for (int i = 0; i < instance->variableCount; ++i) {
        values[i] = (bool) (rand() % 2);
        if (values[i]) weight += instance->weights[i];
    }
    for (int j = 0; j < instance->clauseCount; ++j) {
        SATClause *clause = instance->clauses[j];
        bool clauseTrue = isClauseTrue(clause);
        clausesTrue[j] = clauseTrue;
        if (clauseTrue) satisfiedClauseCount++;
    }
}

bool SATEvaluation::isClauseTrue(const SATClause *clause) const {
    bool clauseTrue = false;
    for (int i = 0; i < instance->clauseSize; ++i) {
        bool variableValue = values[clause->variables[i]];
        clauseTrue = clauseTrue || clause->positive[i] == variableValue;
    }
    return clauseTrue;
}

void SATEvaluation::toggleVariable(int index) {
    if (values[index]) {
        weight -= instance->weights[index];
    } else {
        weight += instance->weights[index];
    }
    values[index] = !values[index];
    for (vector<SATClause *>::iterator it = instance->clausePresence[index].begin(); it != instance->clausePresence[index].end(); ++it) {
        SATClause *clause = *it;
        bool clauseTrue = isClauseTrue(clause);
        if (clausesTrue[clause->index] != clauseTrue) {
            clausesTrue[clause->index] = clauseTrue;
            if (clauseTrue) {
                satisfiedClauseCount++;
            } else {
                satisfiedClauseCount--;
            }
        }
    }
}
