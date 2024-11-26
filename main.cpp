#include "coord.hpp"
#include "prun.hpp"
#include "defs.hpp"
#include "moves.hpp"

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "solver.hpp"
#include "tables.hpp"

using namespace std;

// Function to convert move enums to their string representation
string moveToString(int move)
{
    switch (move)
    {
    case U1M:
        return "U";
    case U2M:
        return "U2";
    case U3M:
        return "U'";
    case R1M:
        return "R";
    case R2M:
        return "R2";
    case R3M:
        return "R'";
    case F1M:
        return "F";
    case F2M:
        return "F2";
    case F3M:
        return "F'";
    case D1M:
        return "D";
    case D2M:
        return "D2";
    case D3M:
        return "D'";
    case L1M:
        return "L";
    case L2M:
        return "L2";
    case L3M:
        return "L'";
    case B1M:
        return "B";
    case B2M:
        return "B2";
    case B3M:
        return "B'";
    default:
        return "";
    }
}

// Function to generate a random scramble
vector<int> generateScramble(int length = 20)
{
    srand(std::time(nullptr)); // Seed for randomness
    vector<int> scramble;      // Store the sequence of moves
    int lastMove = -1;

    for (int i = 0; i < length; ++i)
    {
        int move;
        do
        {
            move = rand() % N_MOVE; // Generate a random move within range
        } while (move / 3 == lastMove / 3); // Avoid consecutive moves on the same face
        scramble.push_back(move); // Add move to scramble
        lastMove = move;
    }
    return scramble;
}

// Function to convert scramble vector to string
string ScrambleToString(vector<int> scramble)
{
    string scrambleStr;
    for (int move : scramble)
    {
        scrambleStr += moveToString(move) + " "; // Use moveToString for each move
    }
    return scrambleStr;
}

void init()
{
    init_moves();
    init_tables();
}

void reBuildPruningTables()
{
    buildTable("PruningTables/coPruningTable", N_TWIST, coMoveTable);
    buildTable("PruningTables/cpPruningTable", N_CORNERS_PERM, cpMoveTable);
}

int main()
{
    // cout << "here" << endl;
    // init();
    // reBuildPruningTables();
    init();
    // for (int i = 1; i < 10; i++)
    // {
    //     cout << i << ": " << coPrunTable[i][0] << endl;
    // }
    // cout << coPrunTable[1940][0] << endl;
    // writeCOTable();
    // writeCPTable();

    CubieCube* cc = new CubieCube();
    // coordCubePhase1* cc1 = new coordCubePhase1(0, 0, 0);
    // // cout << coPrunTable[324][0] << endl;
    // // cout << coPrunTable[1940][0] << endl;
    // // cout << coPrunTable[0][0] << endl;
    // for(int i=345; i<500; i++) {
    //     cc->InvCO(i);
    //     cc1->setCornerOri(cc->co);

    //     cout << (cc1->co == i) << std::endl;
    // }

    vector<int> myScramble = generateScramble(10);
    // vector<int> myScramble = {F3M, L3M, F2M, L2M, D2M, U2M, F3M, L2M, U2M, B1M};
    cout << ScrambleToString(myScramble) << endl;
    cc->applyScramble(myScramble);

    vector<int> solution = solveCube(cc);
    cout << ScrambleToString(solution) << endl;
}