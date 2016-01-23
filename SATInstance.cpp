//
// Created by Dominik Plíšek on 22/01/16.
//

#include <string>
#include <istream>
#include <iostream>
#include <sstream>
#include <math.h>
#include "SATInstance.h"
#include "SATEvaluation.h"

istream &operator>>(istream &in, SATInstance &instance) {
    string line;
    if (!instance.getLine(in, line)) {
        cerr << "Input is empty." << endl;
        exit(EXIT_FAILURE);
    }
    if (line.substr(0, 6) != "p cnf ") {
        cerr << "Missing header line in input." << endl;
        exit(EXIT_FAILURE);
    }
    istringstream iss(line);
    string temp;
    iss >> temp >> temp >> instance.variableCount >> instance.clauseCount;
    instance.clauses = new SATClause *[instance.clauseCount];
    instance.clausePresence = new vector<SATClause *>[instance.variableCount];
    for (int i = 0; i < instance.clauseCount; ++i) {
        SATClause *clause = new SATClause(instance.clauseSize, i);
        in >> *clause;
        for (int j = 0; j < instance.clauseSize; ++j) {
            bool alreadyNotedVariable = false;
            for (int k = 0; k < j; ++k) {
                if (clause->variables[k] == clause->variables[j]) {
                    alreadyNotedVariable = true;
                    break;
                }
            }
            if (!alreadyNotedVariable) {
                instance.clausePresence[clause->variables[j]].push_back(clause);
            }
        }
        instance.clauses[i] = clause;
    }
    instance.weights = new int[instance.variableCount];
    for (int l = 0; l < instance.variableCount; ++l) {
        instance.weights[l] = (rand() % maxWeight) + 1;
    }
    return in;
}

bool SATInstance::getLine(istream &in, string &lineOut) {
    string line;
    while (getline(in, line)) {
        if (line.substr(0, 1) != "c") {
            lineOut = line;
            return true;
        }
    }
    return false;
}

SATInstance::SATInstance(int clauseSize) : clauseSize(clauseSize) {
}

SATInstance::~SATInstance() {
    if (clausePresence != NULL) {
        delete [] clausePresence;
    }
    if (clauses != NULL) {
        for (int i = 0; i < clauseCount; ++i) {
            delete clauses[i];
        }
        delete [] clauses;
    }
    if (weights != NULL) {
        delete [] weights;
    }
}

void SATInstance::solve() {
    SATEvaluation best(this);
    SATEvaluation current(this);
    current.randomize();

    int accepted, processed;
    double temp = 0.0000000001;
    do {
        temp *= warmingFactor;
        considerEvaluation(current, best, temp, accepted, processed, true);
    } while (!acceptingEnough(accepted, processed));

    cerr << "Found starting temperature: " << temp << endl;

    clock_t tt1 = clock();

    do {
        considerEvaluation(current, best, temp, accepted, processed, false);
        temp *= coolingFactor;
    } while (!isFrozen(accepted, processed));

    clock_t tt2 = clock();

    cout << "Solve time: " << ((double) tt2 - tt1) / (CLOCKS_PER_SEC / 1000) << endl;
}

void SATInstance::considerEvaluation(SATEvaluation &current, SATEvaluation &best, double temp, int &accepted, int &processed, bool simulation) {
    accepted = 0;
    processed = 0;
    while (processed < variableCount * 2 && accepted < variableCount) {
        double origValue = getValueToOptimize(current);
        int index = rand() % variableCount;
        current.toggleVariable(index);
        double diff = getValueToOptimize(current) - origValue;
        double randFloat = ((double) rand()) / RAND_MAX;
        if (diff > 0 && randFloat > exp(-diff / temp)) {
            ++processed;
            revert(current, index);
        } else {
            if (simulation) {
                if (diff > 0) {
                    ++processed;
                    ++accepted;
                }
            } else {
                ++processed;
                ++accepted;
                if (current.isSatisfied() && getValueToOptimize(current) < getValueToOptimize(best)) {
                    best = current;
                    cerr << "Found new best result: " << best.weight << endl;
                }
            }
        }
    }
}

void SATInstance::revert(SATEvaluation &evaluation, int index) {
    evaluation.toggleVariable(index);
}

double SATInstance::getValueToOptimize(SATEvaluation &evaluation) {
    if (evaluation.weight == 0 || evaluation.satisfiedClauseCount == 0) return 1;
    return 1.0 / pow(evaluation.satisfiedClauseCount, 2) * evaluation.weight;
}

bool SATInstance::acceptingEnough(int accepted, int processed) {
    double ratio = ((double) accepted) / processed;
    return ratio > 0.5;
}

bool SATInstance::isFrozen(int accepted, int processed) {
    double ratio = ((double) accepted) / processed;
    return ratio < 0.05;
}
