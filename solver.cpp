#include "solver.hpp"

using namespace std;

bool validPair(int m1, int m2) {
    return m1 / 3 == m2 / 3;
}

vector<int> solution;
void solvePhase1(int co, int togo) {
    if (togo == 0 || co == 0) {
        return;
    }
    for (int i = U1M; i <= B3M; i++) {
        if (solution.size() > 0 && !validPair(i, solution.back())) {
            continue;
        }
        int new_co = coMoveTable[co][i];
        int coPrun = coPrunTable[new_co][0];
        // probably an optimization: && (togo > 5 || coPrun != 0 || togo == 1)
        if (coPrun < togo) {
            solution.push_back(i);
            solvePhase1(new_co, togo - 1);
            solution.pop_back();
        }
    }
}   

void solvePhase2(int cp, int togo) {
    if (togo == 0 || cp == 0) {
        return;
    }
    for (int i = U1M; i <= B3M; i++) {
        if (i == R1M || i == R3M || i == F1M || i == F3M || i == L1M || i == L3M || i == B1M || i == B3M) continue;
        if (solution.size() > 0 && !validPair(i, solution.back())) {
            continue;
        }
        int new_cp = cpMoveTable[cp][i];
        int cpPrun = cpPrunTable[new_cp][0];
        if (cpPrun < togo) {
            solution.push_back(i);
            solvePhase2(new_cp, togo - 1);
            solution.pop_back();
        }
    }
}

vector<int> solveCube(CubieCube* cube) {
    cout << coPrunTable[421][0] << endl;
    solvePhase1(cube->getCOCoord(), 20);
    cube->applyScramble(solution);
    cout << "here" << endl;
    solvePhase2(cube->getCPCoord(), 20);
    return solution;
}