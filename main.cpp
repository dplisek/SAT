#include <iostream>
#include <fstream>
#include "SATInstance.h"
#include "SATEvaluation.h"

static const int clauseSize = 3;
static const int runCount = 100;

using namespace std;

int main() {
    srand((unsigned int) time(NULL));

    ifstream file("/users/plech/school/mi-paa/paa-exam/data/CBS_k3_n100_m403_b90_7.cnf");
    if (!file.is_open()) {
        cerr << "Could not open file for reading." << endl;
        exit(EXIT_FAILURE);
    }

    SATInstance instance(clauseSize);
    file >> instance;

    SATEvaluation solution(&instance);

    ofstream restart("/users/plech/school/mi-paa/paa-exam/data/topCalcBottomCalcRestart.dat");
    ofstream time("/users/plech/school/mi-paa/paa-exam/data/topCalcBottomCalcTime.dat");

    clock_t tt1, tt2;
    long millis, restarts;

    millis = 0;
    restarts = 0;
    for (int i = 0; i < runCount; i++) {
        tt1 = clock();
        instance.coolingFactor = 0.80;
        while (!instance.solve(solution)) {
            cerr << "Couldn't find a valid result, restarting. Restart count: " << ++restarts << endl;
        }
        tt2 = clock();
        millis += ((double) tt2 - tt1) / (CLOCKS_PER_SEC / 1000);
    }
    restart << "0.80 " << restarts / runCount << endl;
    time << "0.80 " << millis / runCount << endl;

    millis = 0;
    restarts = 0;
    for (int i = 0; i < runCount; i++) {
        tt1 = clock();
        instance.coolingFactor = 0.85;
        while (!instance.solve(solution)) {
            cerr << "Couldn't find a valid result, restarting. Restart count: " << ++restarts << endl;
        }
        tt2 = clock();
        millis += ((double) tt2 - tt1) / (CLOCKS_PER_SEC / 1000);
    }
    restart << "0.85 " << restarts / runCount << endl;
    time << "0.85 " << millis / runCount << endl;

    millis = 0;
    restarts = 0;
    for (int i = 0; i < runCount; i++) {
        tt1 = clock();
        instance.coolingFactor = 0.90;
        while (!instance.solve(solution)) {
            cerr << "Couldn't find a valid result, restarting. Restart count: " << ++restarts << endl;
        }
        tt2 = clock();
        millis += ((double) tt2 - tt1) / (CLOCKS_PER_SEC / 1000);
    }
    restart << "0.90 " << restarts / runCount << endl;
    time << "0.90 " << millis / runCount << endl;

    millis = 0;
    restarts = 0;
    for (int i = 0; i < runCount; i++) {
        tt1 = clock();
        instance.coolingFactor = 0.95;
        while (!instance.solve(solution)) {
            cerr << "Couldn't find a valid result, restarting. Restart count: " << ++restarts << endl;
        }
        tt2 = clock();
        millis += ((double) tt2 - tt1) / (CLOCKS_PER_SEC / 1000);
    }
    restart << "0.95 " << restarts / runCount << endl;
    time << "0.95 " << millis / runCount << endl;

    millis = 0;
    restarts = 0;
    for (int i = 0; i < runCount; i++) {
        tt1 = clock();
        instance.coolingFactor = 0.99;
        while (!instance.solve(solution)) {
            cerr << "Couldn't find a valid result, restarting. Restart count: " << ++restarts << endl;
        }
        tt2 = clock();
        millis += ((double) tt2 - tt1) / (CLOCKS_PER_SEC / 1000);
    }
    restart << "0.99 " << restarts / runCount << endl;
    time << "0.99 " << millis / runCount << endl;


    return 0;
}

