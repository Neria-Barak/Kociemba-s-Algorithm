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
#include "misc.hpp"

using namespace std;


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
    init();

    CubieCube* cc = new CubieCube();

    vector<int> myScramble = generateScramble(11);
    // vector<int> myScramble = {F1M, R1M, U3M, R3M, U3M, R1M, U1M, R3M, F3M, R1M, U1M, R3M, U3M, R3M, F1M, R1M, F3M};
    cout << "Scramble: " << ScrambleToString(myScramble) << endl;
    cc->applyScramble(myScramble);

    vector<int> solution = solveCube(cc, 12);
    cout << "Solution: " << ScrambleToString(solution) << endl;
}