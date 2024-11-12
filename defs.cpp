#include "defs.hpp"

// Define global arrays
std::array<std::array<int, 3>, N_CORNERS> cornerFacelet = {{{U9, R1, F3}, {U7, F1, L3}, {U1, L1, B3}, {U3, B1, R3}, {D3, F9, R7}, {D1, L9, F7}, {D7, B9, L7}, {D9, R9, B7}}};

std::array<std::array<int, 2>, N_EDGES> edgeFacelet = {{{U6, R2}, {U8, F2}, {U4, L2}, {U2, B2}, {D6, R8}, {D2, F8}, {D4, L8}, {D8, B8}, {F6, R4}, {F4, L6}, {B6, L4}, {B4, R6}}};

std::array<std::array<int, 3>, N_CORNERS> cornerColor = {{{U, R, F}, {U, F, L}, {U, L, B}, {U, B, R}, {D, F, R}, {D, L, F}, {D, B, L}, {D, R, B}}};

std::array<std::array<int, 2>, N_EDGES> edgeColor = {{{U, R}, {U, F}, {U, L}, {U, B}, {D, R}, {D, F}, {D, L}, {D, B}, {F, R}, {F, L}, {B, L}, {B, R}}};

std::array<std::array<int, N_CORNERS>, 18> new_corner_perm = {{
    {UBR, URF, UFL, ULB, DFR, DLF, DBL, DRB}, // U
    {0, 0, 0, 0, 0, 0, 0, 0}, // U2
    {0, 0, 0, 0, 0, 0, 0, 0}, // U3
    {DFR, UFL, ULB, URF, DRB, DLF, DBL, UBR}, // R
    {0, 0, 0, 0, 0, 0, 0, 0}, // R2
    {0, 0, 0, 0, 0, 0, 0, 0}, // R3
    {UFL, DLF, ULB, UBR, URF, DFR, DBL, DRB}, // F
    {0, 0, 0, 0, 0, 0, 0, 0}, // F2
    {0, 0, 0, 0, 0, 0, 0, 0}, // F3
    {URF, UFL, ULB, UBR, DLF, DBL, DRB, DFR}, // D
    {0, 0, 0, 0, 0, 0, 0, 0}, // D2
    {0, 0, 0, 0, 0, 0, 0, 0}, // D3
    {URF, ULB, DBL, UBR, DFR, UFL, DLF, DRB}, // L
    {0, 0, 0, 0, 0, 0, 0, 0}, // L2
    {0, 0, 0, 0, 0, 0, 0, 0}, // L3
    {URF, UFL, UBR, DRB, DFR, DLF, ULB, DBL}, // B
    {0, 0, 0, 0, 0, 0, 0, 0}, // B2
    {0, 0, 0, 0, 0, 0, 0, 0} // B3
    
    
    
    
    
}};

std::array<std::array<int, N_CORNERS>, 18> new_corner_ori = {{
    {0, 0, 0, 0, 0, 0, 0, 0}, // U
    {0, 0, 0, 0, 0, 0, 0, 0}, // U2
    {0, 0, 0, 0, 0, 0, 0, 0}, // U3
    {2, 0, 0, 1, 1, 0, 0, 2}, // R
    {0, 0, 0, 0, 0, 0, 0, 0}, // R2
    {0, 0, 0, 0, 0, 0, 0, 0}, // R3
    {1, 2, 0, 0, 2, 1, 0, 0}, // F
    {0, 0, 0, 0, 0, 0, 0, 0}, // F2
    {0, 0, 0, 0, 0, 0, 0, 0}, // F3
    {0, 0, 0, 0, 0, 0, 0, 0}, // D
    {0, 0, 0, 0, 0, 0, 0, 0}, // D2
    {0, 0, 0, 0, 0, 0, 0, 0}, // D3
    {0, 1, 2, 0, 0, 2, 1, 0}, // L
    {0, 0, 0, 0, 0, 0, 0, 0}, // L2
    {0, 0, 0, 0, 0, 0, 0, 0}, // L3
    {0, 0, 1, 2, 0, 0, 2, 1}, // B
    {0, 0, 0, 0, 0, 0, 0, 0}, // B2
    {0, 0, 0, 0, 0, 0, 0, 0}  // B3
}};

std::array<std::array<int, N_EDGES>, 18> new_edge_perm = {{
    {UB, UR, UF, UL, DR, DF, DL, DB, FR, FL, BL, BR}, // U
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // U2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // U3
    {FR, UF, UL, UB, BR, DF, DL, DB, DR, FL, BL, UR}, // R
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // R2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // R3
    {UR, FL, UL, UB, DR, FR, DL, DB, UF, DF, BL, BR}, // F
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // F2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // F3
    {UR, UF, UL, UB, DF, DL, DB, DR, FR, FL, BL, BR}, // D
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // D2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // D3
    {UR, UF, BL, UB, DR, DF, FL, DB, FR, UL, DL, BR}, // L
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // L2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // L3
    {UR, UF, UL, BR, DR, DF, DL, BL, FR, FL, UB, DB},  // B
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // B2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // B3
}};

std::array<std::array<int, N_EDGES>, 18> new_edge_ori = {{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // U
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // U2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // U3
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // R
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // R2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // R3
    {0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0}, // F
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // F2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // F3
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // D
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // D2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // D3
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // L
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // L2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // L3
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1}, // B
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // B2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // B3
}};

void init_moves() {

    for (int m = U1M; m <= B3M; m += 3) {
        CubieCube* cc1 = new CubieCube(new_corner_ori[m], new_corner_perm[m], new_edge_ori[m], new_edge_perm[m]);
        CubieCube* cc2 = new CubieCube(new_corner_ori[m], new_corner_perm[m], new_edge_ori[m], new_edge_perm[m]);
        cc2->multiply(cc1);
        new_corner_ori[m+1] = cc2->co;
        new_corner_perm[m+1] = cc2->cp;
        new_edge_ori[m+1] = cc2->eo; 
        new_edge_perm[m+1] = cc2->ep;
        cc2->multiply(cc1);
        new_corner_ori[m+2] = cc2->co;
        new_corner_perm[m+2] = cc2->cp;
        new_edge_ori[m+2] = cc2->eo;
        new_edge_perm[m+2] = cc2->ep;
    }
}

// int main() {
//     init_moves();
// }