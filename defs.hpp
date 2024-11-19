#ifndef DEFS_H
#define DEFS_H

using namespace std;

#include "enums.hpp"
#include <array>
#include "cubie.hpp"

// Map the corner positions to facelet positions.
extern array<array<int, 3>, 8> cornerFacelet;

// Map the edge positions to facelet positions.
extern array<array<int, 2>, 12> edgeFacelet;

// Map the corner positions to facelet colors.
extern array<array<int, 3>, 8> cornerColor;

// Map the edge positions to facelet colors.
extern array<array<int, 2>, 12> edgeColor;

#define N_MOVE 18 // number of possible face moves
// Initialize corner_perm and corner_ori arrays with respective data
extern array<array<int, 8>, 18> new_corner_perm;

extern array<array<int, 8>, 18> new_corner_ori;

// Initialize edge_perm, edge_ori, and edge_ori_adjust arrays with respective data
extern array<std::array<int, 12>, 18> new_edge_perm;

extern array<array<int, 12>, 18> new_edge_ori;

extern array<int, N_MOVE> inv_move;

#define N_PERM_4 24
#define N_CHOOSE_8_4 70

#define N_TWIST 2187                        // 3^7 possible corner orientations in phase 1
#define N_FLIP 2048                         // 2^11 possible edge orientations in phase 1
#define N_SLICE_SORTED 11880                // 12*11*10*9 possible positions of the FR, FL, BL, BR edges in phase 1
#define N_SLICE (N_SLICE_SORTED / N_PERM_4) // we ignore the permutation of FR, FL, BL, BR in phase 1
#define N_FLIPSLICE_CLASS 64430             // number of equivalence classes for combined flip+slice concerning symmetry group D4h

#define N_U_EDGES_PHASE2 1680 // number of different positions of the edges UR, UF, UL and UB in phase 2
#define N_D_EDGES_PHASE2 1680 // number of different positions of the edges DR, DF, DL and DB in phase 2
#define N_CORNERS_PERM 40320       // 8! corner permutations in phase 2
#define N_CORNERS_CLASS 2768  // number of equivalence classes concerning symmetry group D4h
#define N_UD_EDGES 40320      // 8! permutations of the edges in the U-face and D-face in phase 2

#define N_SYM 48          // number of cube symmetries of full group Oh
#define N_SYM_D4h 16      // Number of symmetries of subgroup D4h
#define FOLDER "twophase" // Folder name for generated tables

#define N_EDGES 12
#define N_CORNERS 8
#define N_UDS 4

void init_moves();

#endif