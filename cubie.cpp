#include "cubie.hpp"
#include <iostream>

// Constructor with parameters
CubieCube::CubieCube(std::array<int, 8> co,
                     std::array<int, 8> cp,
                     std::array<int, 12> eo,
                     std::array<int, 12> ep)
    : co(co), cp(cp), eo(eo), ep(ep)
{

    cc1 = new coordCubePhase1(co, eo, ep);
    cc2 = new coordCubePhase2(cp, ep, ep);
}

// Default constructor
CubieCube::CubieCube()
{
    this->co = {0,0,0,0,0,0,0,0};
    this->cp = {0,0,0,0,0,0,0,0};
    this->eo = {0,0,0,0,0,0,0,0,0,0,0,0};
    this->ep = {0,0,0,0,0,0,0,0,0,0,0,0};

    cc1 = new coordCubePhase1(this->co, this->eo, this->ep);
    cc2 = new coordCubePhase2(this->cp, this->ep, this->ep);
}

// Multiply edges
void CubieCube::multiply_edge(CubieCube *other)
{
    std::array<int, 12> eoTemp{};
    std::array<int, 12> epTemp{};

    for (int e = 0; e < 12; e++)
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
    std::array<int, 8> coTemp{};
    std::array<int, 8> cpTemp{};

    for (int c = 0; c < 8; c++)
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

// Inverse eorner permutation
void CubieCube::InverseEP(int epVal) {
    array<int, 12> edges;
    array<bool, 12> used;

    for (int i = 11; i >= 0; i--) {
        edges[i] = epVal % (12 - i);
        epVal /= (12 - i);

        // Find the correct edge based on available values
        int count = 0;
        for (int j = 0; j < 12; j++) {
            if (!used[j]) {
                if (count == edges[i]) {
                    edges[i] = j;
                    used[j] = true;
                    break;
                }
                count++;
            }
        }
    }

    this->cc2->setEdgePerm(edges);  // Assuming setEdgePerm is a method to apply an edge permutation
}



// Inverse edge orientation
// void CubieCube::InverseEO(int eoVal) {
//     int parity = 0;
//     for (int e = 11; e >= 0; e--) {
//         this->eo[e] = eoVal % 2;  // Edge orientation is binary (0 or 1)
//         parity += this->eo[e];
//         eoVal /= 2;
//     }
//     // Last edge orientation is determined by parity
//     this->eo[11] = (parity % 2 == 0) ? 0 : 1;

//     this->cc1->setEdgeOri(this->eo);  // Assuming setEdgeOri is a method to apply the edge orientation
// }


// Inverse corner permutation
// void CubieCube::InverseCP(int cpVal) {
//     array<int, 8> corners;
//     array<bool, 8> used;

//     for (int i = 7; i >= 0; i--) {
//         corners[i] = cpVal % (8 - i);
//         cpVal /= (8 - i);

//         // Find the correct corner based on available values
//         int count = 0;
//         for (int j = 0; j < 8; j++) {
//             if (!used[j]) {
//                 if (count == corners[i]) {
//                     corners[i] = j;
//                     used[j] = true;
//                     break;
//                 }
//                 count++;
//             }
//         }
//     }
//     this->cp = corners;
//     this->cc2->setCornerPerm(corners);
// }

// Inverse corner orientation
// void CubieCube::InverseCO(int coVal)
// {
//     int parity = 0;
//     for (int c = 7; c >= 0; c--)
//     {
//         parity += coVal % 3;
//         this->co[c] = coVal % 3;
//         coVal /= 3;
//     }
//     this->co[7] = (3 - parity % 3) % 3;

//     cc1->setCornerOri(co);
// }


// Apply move
void CubieCube::move(int move)
{
    auto c = new CubieCube(new_corner_ori[move / 3],
                           new_corner_perm[move / 3],
                           new_edge_ori[move / 3],
                           new_edge_perm[move / 3]);

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

// Get corner orientation coordinate
int CubieCube::getEPCoord()
{
    return this->cc2->ep;
}
