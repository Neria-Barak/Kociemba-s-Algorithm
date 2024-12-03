#ifndef CUBIE_HPP
#define CUBIE_HPP

#include <array>
#include "defs.hpp"
#include "enums.hpp"
#include "coord.hpp"
#include <vector>

// DO NOT REMOVE
class coordCubePhase1;
class coordCubePhase2;

#define N_CORNERS 8
#define N_EDGES 12

class CubieCube
{
public:
    std::array<int, N_CORNERS> co;
    std::array<int, N_CORNERS> cp;
    std::array<int, N_EDGES> eo;
    std::array<int, N_EDGES> ep;

    coordCubePhase1 *cc1;
    coordCubePhase2 *cc2;

    CubieCube(std::array<int, N_CORNERS> co,
              std::array<int, N_CORNERS> cp,
              std::array<int, N_EDGES> eo,
              std::array<int, N_EDGES> ep);

    CubieCube();

    // CubieCube(CubieCube* other);

    void multiply_edge(CubieCube *other);
    void multiply_corner(CubieCube *other);
    void multiply(CubieCube* b);
    void InverseEP(int co);
    void move(int move);
    int getEPCoord();
    int getEOCoord();
    int getCPCoord();
    int getCOCoord();
    string toString();
    int getUDSOCoord();
    void InvEO(int eoVal);
    void InvCO(int coVal);
    void InvCP(int cpVal);
    void InvEP(int epVal);
    void InvUDSlice(int udsVal);
    void InvUDSO(int udsoVal);

    void applyScramble(vector<int> scramble);
    void undoScramble(vector<int> scramble);
};

// Combination function C(n, k)
int C(int n, int k);

#endif // CUBIE_HPP
