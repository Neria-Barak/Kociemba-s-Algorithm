#ifndef CUBIE_HPP
#define CUBIE_HPP

#include <array>
#include "defs.hpp"
#include "enums.hpp"
#include "coord.hpp"

class CubieCube
{
public:
    std::array<int, 8> co;
    std::array<int, 8> cp;
    std::array<int, 12> eo;
    std::array<int, 12> ep;

    coordCubePhase1 *cc1;
    coordCubePhase2 *cc2;

    CubieCube(std::array<int, 8> co,
              std::array<int, 8> cp,
              std::array<int, 12> eo,
              std::array<int, 12> ep);

    CubieCube();

    void multiply_edge(CubieCube *other);
    void multiply_corner(CubieCube *other);
    void InverseCO(int co);
    void move(int move);
    int getCOCoord();
};

#endif // CUBIE_HPP
