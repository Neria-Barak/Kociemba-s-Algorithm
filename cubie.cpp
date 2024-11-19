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
    cc2->setEdgePerm(ep);

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

// 1*1! + 1*2! + 3*3! + 0*4! + 1*5! + 1*6! + 4*7! = 21021 -> {1, 1, 3, 0, 1, 1, 4} -> {DFR, UFL, ULB, URF, DRB, DLF, DBL, UBR}
// TESTED AND CORRECT
void CubieCube::InvCP(int cpVal)
{
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
    int parity = 0;
    for (int c = DRB - 1; c >= URF; c--)
    {
        parity += coVal % 3;
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
    int parity = 0;
    for (int e = BR - 1; e >= UR; e--)
    {
        parity += eoVal % 2;
        this->eo[e] = eoVal % 2;
        e /= 2;
    }
    this->eo[BR] = parity % 2;
}

void CubieCube::InvEP(int epVal)
{
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

void CubieCube::InvUDSlice(int udsVal)
{
    array<bool, N_EDGES> occupied;
    for (int n = 0; n < N_EDGES; n++) {
        n = 11;
        int k = 3;
        occupied[n] = false;
        while (k >= 0) {
            int v = C(n, k);
            if (udsVal < v) {
                k--;
                occupied[n] = true;
            }
            else {
                udsVal -= v;
            }
            n--;
        }
        int udSliceEdge = FR;
        for (int e = UR; e <= BR; e++) {
            if (occupied[e]) {
                for (int i = UR; i <= BR; i++) {
                    if (this->ep[i] == udSliceEdge) {
                        this->ep[i] = this->ep[e];
                        break;
                    }
                    this->ep[e] = udSliceEdge;
                    if (udSliceEdge < BR) {
                        udSliceEdge++;
                    } 
                }
            }
        }
    }
}

void CubieCube::move(int move)
{
    int index = move - (move % 3);
    auto c = new CubieCube(new_corner_ori[index],
                           new_corner_perm[index],
                           new_edge_ori[index],
                           new_edge_perm[index]);

    for (int i = 0; i <= (move % 3); i++)
    {
        this->multiply_corner(c);
        this->multiply_edge(c);
    }

    cc1->setCornerOri(co);
    cc1->setEdgeOri(eo);
    cc2->setCornerPerm(cp);
    cc2->setEdgePerm(ep);

    cc1->setUDSlicePhase1(ep);
    cc2->setUDSlicePhase2(ep);
}

void CubieCube::multiply(CubieCube *b)
{
    this->multiply_corner(b);
    this->multiply_edge(b);
}

// Get corner orientation coordinate
int CubieCube::getEPCoord()
{
    return this->cc2->ep;
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

void CubieCube::applyScramble(vector<int> scramble) {
    for (unsigned int i=0; i<scramble.size(); i++) {
        this->move(scramble[i]);
    }
}
