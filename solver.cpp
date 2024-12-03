#include "solver.hpp"

using namespace std;

bool validPair(int m1, int m2)
{
    return m1 / 3 != m2 / 3;
}

vector<int> currentSolution = {};
vector<int> optimalSolution = {};
unsigned int maxDepth;

// int solvePhase2(int cp, int togo)
// {
//     if (cp == 0)
//         return 0;
//     if (togo == 0)
//     {
//         return 1;
//     }
//     for (int i = U1M; i < B3M; i++)
//     {
//         if (i == R1M || i == R3M || i == F1M || i == F3M || i == L1M || i == L3M || i == B1M)
//             continue;
//         if (currentSolution.size() > 0 && !validPair(i, currentSolution.back()))
//         {
//             continue;
//         }
//         int new_cp = cpMoveTable[cp][i];
//         int cpPrun = cpPrunTable[new_cp][0];
//         if (cpPrun < togo)
//         {
//             currentSolution.push_back(i);
//             if (!solvePhase2(new_cp, togo - 1))
//                 return 0;
//             currentSolution.pop_back();
//         }
//     }
//     return 1;
// }

// void phase2Start(CubieCube *cube)
// {
    
//     CubieCube *cc = new CubieCube(cube->co, cube->cp, cube->eo, cube->ep);
//     cc->applyScramble(currentSolution);
//     int cp = cc->getCPCoord();
    
//     bool found = false;
//     for (unsigned int i = 0; i <= maxDepth; i++) {
//         // cout << "Done searching depth " << i << " Phase 2" << endl;
//         if (!solvePhase2(cp, i)) {
//             found = true;
//             break;
//         }
//     }
//     if (found == true && (currentSolution.size() < optimalSolution.size() || optimalSolution.size() == 0))
//         optimalSolution = currentSolution;
//     if (optimalSolution.size() > 0 && optimalSolution.size() < maxDepth)
//         return;
// }

// TESTED AND CORRECT
int solvePhase1(int eo, int co, int udso, int togo, CubieCube* cube)
{
    if (togo == 0 && co == 0  && eo == 0 && udso == 0)
    {
        // vector<int> tempSolution = currentSolution;
        // phase2Start(cube);
        // if (optimalSolution.size() > 0 && optimalSolution.size() <= maxDepth)
        return 0;
        // currentSolution = tempSolution;
    }
    for (int i = U1M; i <= B3M; i++)
    {
         if (currentSolution.size() > 0 && !validPair(i, currentSolution.back()))
        {
            continue;
        }
        int new_eo = eoMoveTable[eo][i];
        int new_co = coMoveTable[co][i];
        int new_udso = UDSOMoveTable[udso][i];

        
        int sliceFlipPrun = sliceFlipPrunTable[new_udso][new_eo];
        int sliceTwistPrun = sliceTwistPrunTable[new_udso][new_co];
        // probably an optimization: && (togo > 5 || coPrun != 0 || togo == 1)
        if (max(sliceFlipPrun, sliceTwistPrun) < togo)
        {
            currentSolution.push_back(i);
            if (!solvePhase1(new_eo, new_co, new_udso, togo - 1, cube))
                return 0;
            currentSolution.pop_back();
        }
    }
    return 1;
}

vector<int> solveCube(CubieCube *cube, unsigned int maxLen)
{
    maxDepth = maxLen;
    // cout << cube->toString() << endl;
    for (unsigned int i = 0; i <= maxLen; i++)
    {
        if (!solvePhase1(cube->getEOCoord(), cube->getCOCoord(), cube->getUDSOCoord(), i, cube))
        {
            break;
        }
        cout << "Done searching depth " << i << endl;
    }
    return currentSolution;
}