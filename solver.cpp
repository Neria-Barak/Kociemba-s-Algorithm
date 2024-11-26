#include "solver.hpp"

using namespace std;

bool validPair(int m1, int m2) {
    return m1 / 3 != m2 / 3;
}

vector<int> solution = {};

// TESTED AND CORRECT
int solvePhase1(int co, int togo) {
    if (co == 0) {
        return 0;
    }
    if (togo == 0) {
        return 1;
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
            if (!solvePhase1(new_co, togo - 1))
                return 0;
            solution.pop_back();
        }
    }
    return 1;
}   

int solvePhase2(int cp, int togo) {
    if (cp == 0)
        return 0;
    if (togo == 0) {
        return 1;
    }
    for (int i = U1M; i < B3M; i++) {
        if (i == R1M || i == R3M || i == F1M || i == F3M || i == L1M || i == L3M || i == B1M) continue;
        if (solution.size() > 0 && !validPair(i, solution.back())) {
            continue;
        }
        int new_cp = cpMoveTable[cp][i];
        int cpPrun = cpPrunTable[new_cp][0];
        if (cpPrun < togo) {
            solution.push_back(i);
            if (!solvePhase2(new_cp, togo - 1))
                return 0;
            solution.pop_back();
        }
    }
    return 1;
}

vector<int> solveCube(CubieCube* cube) {
    for (int i = 1; i <= 20; i++) {
        if (!solvePhase1(cube->getCOCoord(), i))
            break;
        
    }
    cube->applyScramble(solution);
    for (int i = 1; i <= 20; i++) {
        if (!solvePhase2(cube->getCPCoord(), i))
            break;
        cout << "Done searching depth " << i << endl; 
    }
    return solution;
}