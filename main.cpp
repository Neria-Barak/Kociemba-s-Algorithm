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

// TODO:
// (* phase1 *)
// sliceflipPrun = prunTable["sliceflipPrun",sliceMove,495,flipMove,2048];
// slicetwistPrun = prunTable["slicetwistPrun",sliceMove,495,twistMove,2187];
// (* phase2 *)
// edge4edge8Prun = prunTable["edge4edge8Prun",edge4Move,24,edge8Move,40320];  
// edge4cornerPrun = prunTable["edge4cornerPrun",edge4Move,24,cornerMove,40320];

void reBuildPruningTables()
{
    // buildTable("PruningTables/coPruningTable", N_TWIST, coMoveTable);
    // buildTable("PruningTables/cpPruningTable", N_CORNERS_PERM, cpMoveTable);
    // buildTable("PruningTables/sliceTwistPrun", N_SLICE, UDSOMoveTable, N_TWIST, coMoveTable);
    buildTable("PruningTables/sliceFlipPrun", N_SLICE, UDSOMoveTable, N_FLIP, eoMoveTable);

}

int main()
{
    init();
    // writeEOTable();
    reBuildPruningTables();
    // CubieCube* cc = new CubieCube();
    // cout << cc->getEOCoord() << endl;
    // cout << eoMoveTable[1043][U3M] << endl;
    
    
    // cout << UDSOMoveTable[227][U3M] << endl;;
    // int i = 311;
    // cc->InvEO(i);
    // cout << cc->getEOCoord() << endl;
    
    

    // vector<int> myScramble = generateScramble(11);
    // // vector<int> myScramble = {F1M, R1M, U3M, R3M, U3M, R1M, U1M, R3M, F3M, R1M, U1M, R3M, U3M, R3M, F1M, R1M, F3M};
    // cout << "Scramble: " << ScrambleToString(myScramble) << endl;
    // cc->applyScramble(myScramble);

    // vector<int> solution = solveCube(cc, 12);
    // cout << "Solution: " << ScrambleToString(solution) << endl;
}