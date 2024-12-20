#include "cubie.hpp"
#include <iostream>

// Constructor with parameters
CubieCube::CubieCube(std::array<int, N_CORNERS> co,
                     std::array<int, N_CORNERS> cp,
                     std::array<int, N_EDGES> eo,
                     std::array<int, N_EDGES> ep)
    : co(co), cp(cp), eo(eo), ep(ep)
{

    cc1 = new coordCubePhase1(co, eo, ep);
    cc2 = new coordCubePhase2(cp, ep, ep);
}

// CubieCube::CubieCube(CubieCube* other) {
//     this->co = array<int>(other->co);
//     this->cp = array<int>(other->cp);
//     this->eo = array<int>(other->eo);
//     this->ep = array<int>(other->ep);
// }

// Default constructor
CubieCube::CubieCube()
{
    this->co = {0, 0, 0, 0, 0, 0, 0, 0};
    this->cp = {URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB};
    this->eo = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    this->ep = {UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR};

    cc1 = new coordCubePhase1(this->co, this->eo, this->ep);
    cc2 = new coordCubePhase2(this->cp, this->ep, this->ep);
}

// procedure EdgeMult(a,b:EdgeCubie; var prod:EdgeCubie);
// var ed: Edge; ori:ShortInt;
// begin
//   for ed:=UR to BR do
//   begin
//     prod[ed].e:= a[b[ed].e].e;
//     ori:= b[ed].o+a[b[ed].e].o;
//     if ori=2 then ori:=0
//     else if ori>=6 then ori:=6;//unknown orientation
//     prod[ed].o:=ori;
//   end;
// end;

// CHECKED AND PROBABLY CORRECT
// Multiply edges
void CubieCube::multiply_edge(CubieCube *other)
{
    std::array<int, N_EDGES> eoTemp{};
    std::array<int, N_EDGES> epTemp{};

    for (int e = 0; e < N_EDGES; e++)
    {
        epTemp[e] = this->ep[other->ep[e]];
        eoTemp[e] = (this->eo[other->ep[e]] + other->eo[e]) % 2;
    }

    ep = epTemp;
    eo = eoTemp;

    cc1->setEdgeOri(eo);
    cc2->setEP8(ep);

    cc1->setUDSlicePhase1(ep);
    cc2->setUDSlicePhase2(ep);
}

// Multiply corners
void CubieCube::multiply_corner(CubieCube *other)
{
    std::array<int, N_CORNERS> coTemp{};
    std::array<int, N_CORNERS> cpTemp{};

    for (int c = 0; c < N_CORNERS; c++)
    {
        cpTemp[c] = this->cp[other->cp[c]];
        int oriThis = this->co[other->cp[c]];
        int oriOther = other->co[c];

        if (oriThis < 3 && oriOther < 3)
        {
            coTemp[c] = (oriThis + oriOther) % 3;
        }
        else if (oriThis < 3)
        {
            coTemp[c] = (oriThis + oriOther) % 3 + 3;
        }
        else if (oriOther < 3)
        {
            coTemp[c] = (oriThis - oriOther + 3) % 3 + 3;
        }
        else
        {
            coTemp[c] = (oriThis - oriOther + 3) % 3;
        }
    }

    cp = cpTemp;
    co = coTemp;

    cc1->setCornerOri(co);
    cc2->setCornerPerm(cp);
}

void CubieCube::InvUDSO(int udsoVal) {
    this->cc1->uds = udsoVal;
    std::array<bool, 12> occupied = {false};
    int n = 11, k = 3;

    // Determine the occupied edges based on the rank 'udsoVal'
    while (k >= 0) {
        int v = C(n, k);
        if (udsoVal < v) {
            --k;
            occupied[n] = true;
        } else {
            udsoVal -= v;
        }
        --n;
    }

    // Assign edges
    int udSliceEdge = FR; // Start with FR edge
    for (int ed = UR; ed <= BR; ++ed) {
        if (occupied[ed]) {
            // Replace the edge in ep
            for (int i = UR; i <= BR; ++i) {
                if (this->ep[i] == udSliceEdge) {
                    this->ep[i] = this->ep[ed];
                    break;
                }
            }
            this->ep[ed] = udSliceEdge;

            if (udSliceEdge < BR) {
                udSliceEdge++;
            }
        }
    }
}

// 1*1! + 1*2! + 3*3! + 0*4! + 1*5! + 1*6! + 4*7! = 21021 -> {1, 1, 3, 0, 1, 1, 4} -> {DFR, UFL, ULB, URF, DRB, DLF, DBL, UBR}
// TESTED AND CORRECT
void CubieCube::InvCP(int cpVal)
{
    this->cc2->cp = cpVal;
    array<bool, N_CORNERS> used;
    array<int, N_CORNERS> order;

    for (int i = URF; i <= DRB; i++)
    {
        used[i] = false;
        order[i] = cpVal % (i + 1);
        cpVal /= i + 1;
    }
    for (int i = DRB; i >= URF; i--)
    {
        int k = DRB;
        while (used[k])
            k--;
        while (order[i] > 0)
        {
            order[i]--;
            do
            {
                k--;
            } while (used[k]);
        }
        this->cp[i] = k;
        used[k] = true;
    }
}
// TESTED AND CORRECT
void CubieCube::InvCO(int coVal) {
    this->cc1->co = coVal;
    int parity = 0;
    
    for (int c = DRB - 1; c >= URF; c--)
    {
        parity = parity + (coVal) % 3;
        this->co[c] = coVal % 3;
        coVal /= 3;
    }
    parity %= 3;
    switch (parity)
    {
    case 0:
        this->co[DRB] = 0;
        break;
    case 1:
        this->co[DRB] = 2;
        break;
    case 2:
        this->co[DRB] = 1;
        break;
    }
}

void CubieCube::InvEO(int eoVal)
{
    this->cc1->eo = eoVal;
    int parity = 0;
    for (int e = BR - 1; e >= UR; e--)
    {
        parity += eoVal % 2;
        this->eo[e] = eoVal % 2;
        eoVal /= 2;
    }
    this->eo[BR] = parity % 2;
}

void CubieCube::InvEP8(int epVal) {
    this->cc2->ep8 = epVal;

    array<bool, N_EDGES> used;
    array<int, N_EDGES> order;

    for (int i = UR; i <= BR; i++)
    {
        used[i] = false;
        order[i] = epVal % (i + 1);
        epVal /= i + 1;
    }
    for (int i = BR; i >= UR; i--)
    {
        int k = BR;
        while (used[k])
            k--;
        while (order[i] > 0)
        {
            order[i]--;
            do
            {
                k--;
            } while (used[k]);
        }
        this->ep[i] = k;
        used[k] = true;
    }
}

int C(int n, int k)
{
    if (k > n)
        return 0;
    if (k == 0 || n == k)
        return 1;
    return C(n - 1, k - 1) + C(n - 1, k);
}

// void CubieCube::InvUDSP(int udsVal)
// {
//     array<bool, N_EDGES> occupied;
//     for (int n = 0; n < N_EDGES; n++) {
//         n = 11;
//         int k = 3;
//         occupied[n] = false;
//         while (k >= 0) {
//             int v = C(n, k);
//             if (udsVal < v) {
//                 k--;
//                 occupied[n] = true;
//             }
//             else {
//                 udsVal -= v;
//             }
//             n--;
//         }
//         int udSliceEdge = FR;
//         for (int e = UR; e <= BR; e++) {
//             if (occupied[e]) {
//                 for (int i = UR; i <= BR; i++) {
//                     if (this->ep[i] == udSliceEdge) {
//                         this->ep[i] = this->ep[e];
//                         break;
//                     }
//                     this->ep[e] = udSliceEdge;
//                     if (udSliceEdge < BR) {
//                         udSliceEdge++;
//                     } 
//                 }
//             }
//         }
//     }
// }

void CubieCube::InvUDSP(int udsVal) {
    array<int, 12> used;
    array<int, 4> order;
    int x = udsVal;
    // remember for debug x = w mod 24?
    for (int j = FR; j <= BR; j++) {
        used[j] = false;
    }
    for (int i = 0; i <= 3; i++) {
        order[i] = x % (i+1);
        x /= i + 1;
    }

    for (int i = 3; i >= 0; i--) {
        int k = BR;
        while (used[k]) k--;
        while(order[i] > 0) {
            order[i]--;
            do {
                k--;
            } while(used[k]);
        }
        
        int m = -1;
        for (int j = UR; j <= BR; j++) {
            // debug why use ep???
            int e = this->ep[j];
            if (e == FR || e == FL || e == BL || e == BR) {
                m++;
            }
            if (m == i) {
                this->ep[j] = k;
                used[k] = true;
                break;
            }
        }
    }
}

void CubieCube::move(int move)
{
    // int index = move - (move % 3);
    // auto c = new CubieCube(new_corner_ori[index],
    //                        new_corner_perm[index],
    //                        new_edge_ori[index],
    //                        new_edge_perm[index]);

    // for (int i = 0; i <= (move % 3); i++)
    // {
    //     this->multiply_corner(c);
    //     this->multiply_edge(c);
    // }
    auto c = new CubieCube(new_corner_ori[move],
                           new_corner_perm[move],
                           new_edge_ori[move],
                           new_edge_perm[move]);

    this->multiply_corner(c);
    this->multiply_edge(c);


    // cc1->setCornerOri(co);
    // cc1->setEdgeOri(eo);
    // cc2->setCornerPerm(cp);
    // cc2->setEdgePerm(ep);

    // cc1->setUDSlicePhase1(ep);
    // cc2->setUDSlicePhase2(ep);
}

void CubieCube::multiply(CubieCube *b)
{
    this->multiply_corner(b);
    this->multiply_edge(b);
}

// Get corner orientation coordinate
int CubieCube::getEP8Coord()
{
    return this->cc2->ep8;
}
int CubieCube::getEOCoord() {
    return this->cc1->eo;
}
int CubieCube::getCPCoord()
{
    return this->cc2->cp;
}
int CubieCube::getCOCoord() {
    return this->cc1->co;
}
int CubieCube::getUDSOCoord() {
    return this->cc1->uds;
}
int CubieCube::getUDSPCoord() {
    return this->cc2->uds;
}


void CubieCube::applyScramble(vector<int> scramble) {
    for (unsigned int i=0; i<scramble.size(); i++) {
        this->move(scramble[i]);
    }
}

void CubieCube::undoScramble(vector<int> scramble) {
    for (unsigned int i = 0; i < scramble.size(); i++) {
        this->move(inv_move[scramble[i]]);
    }
}

std::string CubieCube::toString() {
    std::string result;

    // Corner Orientation
    result += "Corner Orientation (co): [";
    for (size_t i = 0; i < co.size(); ++i) {
        result += std::to_string(co[i]);
        if (i < co.size() - 1) {
            result += ", ";
        }
    }
    result += "]\n";

    // Corner Permutation
    result += "Corner Permutation (cp): [";
    for (size_t i = 0; i < cp.size(); ++i) {
        result += std::to_string(cp[i]);
        if (i < cp.size() - 1) {
            result += ", ";
        }
    }
    result += "]\n";

    // Edge Orientation
    result += "Edge Orientation (eo): [";
    for (size_t i = 0; i < eo.size(); ++i) {
        result += std::to_string(eo[i]);
        if (i < eo.size() - 1) {
            result += ", ";
        }
    }
    result += "]\n";

    // Edge Permutation
    result += "Edge Permutation (ep): [";
    for (size_t i = 0; i < ep.size(); ++i) {
        result += std::to_string(ep[i]);
        if (i < ep.size() - 1) {
            result += ", ";
        }
    }
    result += "]\n";

    // Phase 1 and Phase 2 Coordinates
    result += "Phase 1 UDSlice (cc1->uds): " + std::to_string(cc1->uds) + "\n";
    result += "Phase 2 UDSlice (cc2->uds): " + std::to_string(cc2->uds) + "\n";
    result += "Phase 1 Edge Orientation (cc1->eo): " + std::to_string(cc1->eo) + "\n";
    result += "Phase 2 Edge Permutation (cc2->ep): " + std::to_string(cc2->ep8) + "\n";
    result += "Phase 1 Corner Orientation (cc1->co): " + std::to_string(cc1->co) + "\n";
    result += "Phase 2 Corner Permutation (cc2->cp): " + std::to_string(cc2->cp) + "\n";

    return result;
}
