#ifndef COORD
#define COORD

#include "defs.hpp"
#include "enums.hpp"
#include <array>
#include <iostream>

class coordCubePhase1
{
public:
    int co;  // Corner Orientation Coordinate
    int eo;  // Edge Orientation Coordinate
    int uds; // UDSlice Coordinate
    coordCubePhase1(int co, int eo, int uds);

    // constructor
    coordCubePhase1(array<int, 8> co, array<int, 12> eo, array<int, 12> uds);

    void setEdgeOri(array<int, 12> eo);

    void setCornerOri(array<int, 8> co);

    void setUDSlicePhase1(array<int, 12> ep);

    static int getUDSliceCoord(array<int, 12> ep);
};

class coordCubePhase2
{
public:
    int cp;  // Corner Permutation Coordinate
    int ep;  // Edge Permutation Coordinate
    int uds; // UDSlice Coordinate

    coordCubePhase2(int cp, int ep, int uds);

    // constructor
    coordCubePhase2(array<int, 8> cp, array<int, 12> ep, array<int, 12> uds);

    void setEdgePerm(array<int, 12> ep);

    void setCornerPerm(array<int, 8> cp);

    void setUDSlicePhase2(array<int, 12> ep);

    int getUDSliceCoord(array<int, 12> ep);

    int UDSliceCoordSorted(array<int, 12> ep);
};


#endif