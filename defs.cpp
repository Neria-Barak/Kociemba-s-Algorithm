#include "defs.hpp"

// Define global arrays
std::array<std::array<int, 3>, 8> cornerFacelet = {{{U9, R1, F3}, {U7, F1, L3}, {U1, L1, B3}, {U3, B1, R3}, {D3, F9, R7}, {D1, L9, F7}, {D7, B9, L7}, {D9, R9, B7}}};

std::array<std::array<int, 2>, 12> edgeFacelet = {{{U6, R2}, {U8, F2}, {U4, L2}, {U2, B2}, {D6, R8}, {D2, F8}, {D4, L8}, {D8, B8}, {F6, R4}, {F4, L6}, {B6, L4}, {B4, R6}}};

std::array<std::array<int, 3>, 8> cornerColor = {{{U, R, F}, {U, F, L}, {U, L, B}, {U, B, R}, {D, F, R}, {D, L, F}, {D, B, L}, {D, R, B}}};

std::array<std::array<int, 2>, 12> edgeColor = {{{U, R}, {U, F}, {U, L}, {U, B}, {D, R}, {D, F}, {D, L}, {D, B}, {F, R}, {F, L}, {B, L}, {B, R}}};

std::array<std::array<int, 8>, 6> new_corner_perm = {{
    {UBR, URF, UFL, ULB, DFR, DLF, DBL, DRB}, // U
    {DFR, UFL, ULB, URF, DRB, DLF, DBL, UBR}, // R
    {UFL, DLF, ULB, UBR, URF, DFR, DBL, DRB}, // F
    {URF, UFL, ULB, UBR, DLF, DBL, DRB, DFR}, // D
    {URF, ULB, DBL, UBR, DFR, UFL, DLF, DRB}, // L
    {URF, UFL, UBR, DRB, DFR, DLF, ULB, DBL}  // B
}};

std::array<std::array<int, 8>, 6> new_corner_ori = {{
    {0, 0, 0, 0, 0, 0, 0, 0}, // U
    {2, 0, 0, 1, 1, 0, 0, 2}, // R
    {1, 2, 0, 0, 2, 1, 0, 0}, // F
    {0, 0, 0, 0, 0, 0, 0, 0}, // D
    {0, 1, 2, 0, 0, 2, 1, 0}, // L
    {0, 0, 1, 2, 0, 0, 2, 1}  // B
}};

std::array<std::array<int, 12>, 6> new_edge_perm = {{
    {UB, UR, UF, UL, DR, DF, DL, DB, FR, FL, BL, BR}, // U
    {FR, UF, UL, UB, BR, DF, DL, DB, DR, FL, BL, UR}, // R
    {UR, FL, UL, UB, DR, FR, DL, DB, UF, DF, BL, BR}, // F
    {UR, UF, UL, UB, DF, DL, DB, DR, FR, FL, BL, BR}, // D
    {UR, UF, BL, UB, DR, DF, FL, DB, FR, UL, DL, BR}, // L
    {UR, UF, UL, BR, DR, DF, DL, BL, FR, FL, UB, DB}  // B
}};

std::array<std::array<int, 12>, 6> new_edge_ori = {{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // U
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // R
    {0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0}, // F
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // D
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // L
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1}  // B
}};
