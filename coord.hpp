#ifndef COORD
#define COORD

#include "defs.hpp"
#include "enums.hpp"
#include <array>
#include <iostream>

using namespace std;

#define N_CORNERS 8
#define N_EDGES 12

class coordCubePhase1
{
public:
    int co;  // Corner Orientation Coordinate
    int eo;  // Edge Orientation Coordinate
    int uds; // UDSlice Coordinate
    coordCubePhase1(int co, int eo, int uds);

    // constructor
    coordCubePhase1(array<int, N_CORNERS> co, array<int, N_EDGES> eo, array<int, N_EDGES> uds);

    void setEdgeOri(array<int, N_EDGES> eo);

    void setCornerOri(array<int, N_CORNERS> co);

    void setUDSlicePhase1(array<int, N_EDGES> ep);

    static int getUDSliceCoord(array<int, N_EDGES> ep);
};

class coordCubePhase2
{
public:
    int cp;  // Corner Permutation Coordinate
    int ep;  // Edge Permutation Coordinate
    int uds; // UDSlice Coordinate

    coordCubePhase2(int cp, int ep, int uds);

    // constructor
    coordCubePhase2(array<int, N_CORNERS> cp, array<int, N_EDGES> ep, array<int, N_EDGES> uds);

    void setEdgePerm(array<int, N_EDGES> ep);

    void setCornerPerm(array<int, N_CORNERS> cp);

    void setUDSlicePhase2(array<int, N_EDGES> ep);

    int getUDSliceCoord(array<int, N_EDGES> ep);

    int UDSliceCoordSorted(array<int, N_EDGES> ep);
};


#endif