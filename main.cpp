#include <iostream>
#include <fstream>
#include "SATInstance.h"

static const int clauseSize = 3;

using namespace std;

int main() {
    srand((unsigned int) time(NULL));

    ifstream file("/users/plech/school/mi-paa/paa-exam/data/CBS_k3_n100_m403_b30_0.cnf");
    if (!file.is_open()) {
        cerr << "Could not open file for reading." << endl;
        exit(EXIT_FAILURE);
    }

    SATInstance instance(clauseSize);
    file >> instance;

    instance.coolingFactor = 0.98;
    instance.solve();

    return 0;
}

