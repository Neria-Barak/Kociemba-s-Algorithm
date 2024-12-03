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
    // buildTable("PruningTables/sliceFlipPrun", N_SLICE, UDSOMoveTable, N_FLIP, eoMoveTable);
    buildTable("PruningTables/udspEp8Prun", N_PERM_4, UDSPMoveTable, N_UD_EDGES, ep8MoveTable);
    buildTable("PruningTables/udspCpPrun", N_PERM_4, UDSPMoveTable, N_CORNERS_PERM, cpMoveTable);

}

int main()
{
    init();
    // writeUDSPTable();
    // reBuildPruningTables();


    // CubieCube* cc = new CubieCube();
    
    // vector<int> myScramble = generateScramble(20);
    // // vector<int> myScramble = {R3M};
    // cout << "Scramble: " << ScrambleToString(myScramble) << endl;
    // cc->applyScramble(myScramble);

    // vector<int> solution = solveCube(cc, 20);
    // cout << "Solution: " << ScrambleToString(solution) << endl;
}