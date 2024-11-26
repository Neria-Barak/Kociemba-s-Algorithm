#include "solver.hpp"

using namespace std;

bool validPair(int m1, int m2)
{
    return m1 / 3 != m2 / 3;
}

vector<int> currentSolutionPhase1 = {};
vector<int> currentSolution = {};
vector<int> optimalSolutionPhase1 = {};
vector<int> optimalSolution = {};

// TESTED AND CORRECT
int solvePhase1(int co, int togo)
{
    if (co == 0)
    {
        if (optimalSolutionPhase1.size() > 0 && equal(currentSolution.begin(),  currentSolution.end(),  optimalSolutionPhase1.begin()))
            return 1;
        return 0;
    }
    if (togo == 0)
    {
        return 1;
    }
    for (int i = U1M; i <= B3M; i++)
    {
        if (currentSolution.size() > 0 && !validPair(i, currentSolution.back()))
        {
            continue;
        }
        int new_co = coMoveTable[co][i];
        int coPrun = coPrunTable[new_co][0];
        // probably an optimization: && (togo > 5 || coPrun != 0 || togo == 1)
        if (coPrun < togo)
        {
            currentSolution.push_back(i);
            if (!solvePhase1(new_co, togo - 1))
                return 0;
            currentSolution.pop_back();
        }
    }
    return 1;
}

int solvePhase2(int cp, int togo)
{
    if (cp == 0)
        return 0;
    if (togo == 0)
    {
        return 1;
    }
    for (int i = U1M; i < B3M; i++)
    {
        if (i == R1M || i == R3M || i == F1M || i == F3M || i == L1M || i == L3M || i == B1M)
            continue;
        if (currentSolution.size() > 0 && !validPair(i, currentSolution.back()))
        {
            continue;
        }
        int new_cp = cpMoveTable[cp][i];
        int cpPrun = cpPrunTable[new_cp][0];
        if (cpPrun < togo)
        {
            currentSolution.push_back(i);
            if (!solvePhase2(new_cp, togo - 1))
                return 0;
            currentSolution.pop_back();
        }
    }
    return 1;
}

vector<int> solveCube(CubieCube *cube, unsigned int maxLen)
{   
    CubieCube* cc = new CubieCube(cube->co, cube->cp, cube->eo, cube->ep);
    do
    {
        for (unsigned int i = 1; i <= maxLen; i++)
        {
            if (!solvePhase1(cube->getCOCoord(), i))
                break;
            // cout << "Done searching depth " << i << endl;
        }
        currentSolutionPhase1 = currentSolution;
        cube->applyScramble(currentSolution);
        for (unsigned int i = 1; i <= maxLen; i++)
        {
            if (!solvePhase2(cube->getCPCoord(), i))
                break;
        }
        if (optimalSolution.size() == 0 || optimalSolution.size() > currentSolution.size()) {
            optimalSolution = vector<int> (currentSolution);
            optimalSolutionPhase1 = vector<int> (currentSolutionPhase1);
            cout << ScrambleToString(currentSolution) << endl;
        }
        currentSolution = {};
        currentSolutionPhase1 = {};
        cube = new CubieCube(cc->co, cc->cp, cc->eo, cc->ep);
    } while (optimalSolution.size() > maxLen);
    
    return optimalSolution;
}