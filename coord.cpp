#include "coord.hpp"

using namespace std;

// constructor
coordCubePhase1::coordCubePhase1(int co,
                                 int eo,
                                 int uds)
{
    this->co = co;
    this->eo = eo;
    this->uds = uds;
}

// constructor
coordCubePhase1::coordCubePhase1(array<int, N_CORNERS> co,
                                 array<int, N_EDGES> eo,
                                 array<int, N_EDGES> uds)
{

    this->setEdgeOri(eo);
    this->setCornerOri(co);
    this->setUDSlicePhase1(uds);
}

void coordCubePhase1::setEdgeOri(array<int, N_EDGES> eo)
{
    int s = 0;
    // we use base 2 where each bit coresspondes to an edge orientation
    for (int e = UR; e < BR; e++)
    {
        // multiplying by two at every iteration to form the number digit by digit
        s = 2 * s + eo[e];
    }
    this->eo = s;
}
void coordCubePhase1::setCornerOri(array<int, N_CORNERS> co)
{
    int s = 0;
    // we use base 3 where each bit coresspondes to an edge orientation
    for (int c = URF; c < DRB; c++)
    {
        // multiplying by two at every iteration to form the number digit by digit
        s = 3 * s + co[c];
    }
    this->co = s;
}

// CHECKED AND PROBABLY CORRECT
int coordCubePhase1::getUDSliceCoord(array<int, N_EDGES> ep)
{
    array<bool, N_EDGES> occupied = {false};
    for (int ed = UR; ed <= BR; ed++)
    {
        if (ep[ed] >= FR)
        {
            occupied[ed] = true;
        }
    }

    int s = 0;
    int k = 3;  // 4 pieces for UDSlice - 1 since we're using 0-based index
    int n = 11; // Start from the end

    while (k >= 0)
    {
        if (occupied[n])
        {
            k--;
        }
        else
        {
            s += C(n, k);
        }
        n--;
    }
    return s;
}

void coordCubePhase1::setUDSlicePhase1(array<int, N_EDGES> ep)
{
    this->uds = coordCubePhase1::getUDSliceCoord(ep);
}
// constructor
coordCubePhase2::coordCubePhase2(int cp,
                                 int ep8,
                                 int uds)
{

    this->cp = cp;
    this->ep8 = ep8;
    this->uds = uds;
}

coordCubePhase2::coordCubePhase2(array<int, N_CORNERS> cp, array<int, N_EDGES> ep, array<int, N_EDGES> uds)
{
    this->setEP8(ep);
    this->setCornerPerm(cp);
    this->UDSliceCoordSorted(uds);
}

void coordCubePhase2::setCornerPerm(array<int, N_CORNERS> cp)
{
    int x = 0;
    for (int c1 = DRB; c1 > URF; c1--)
    {
        int s = 0;
        for (int c2 = c1 - 1; c2 >= URF; c2--)
        {
            if (cp[c2] > cp[c1])
                s++;
        }
        x = (x + s) * c1;
    }
    this->cp = x;
}

int coordCubePhase2::UDSliceCoordSorted(array<int, N_EDGES> ep)
{
    array<int, 4> arr;
    int j = 0;
    for (int e = UR; e <= BR; e++)
    {
        int ed = ep[e];
        if (ed == FR || ed == FL || ed == BL || ed == BR)
        {
            arr[j] = ed;
            j++;
        }
    }

    // mapping every order of UDSlice to a unique coordinate
    int x = 0;
    for (int j = 3; j > 0; j--)
    {
        int s = 0;
        for (int k = j - 1; k >= 0; k--)
        {
            if (arr[k] > arr[j])
            {
                s++;
            }
        }
        x = (x + s) * j;
    }
    // Result:= UDSliceCoord*24 + x;
    return coordCubePhase1::getUDSliceCoord(ep) * 24 + x;
}

void coordCubePhase2::setUDSlicePhase2(array<int, N_EDGES> ep)
{
    this->uds = UDSliceCoordSorted(ep) % 24;
}

void coordCubePhase2::setEP8(array<int, N_EDGES> ep8)
{
    int x = 0;
    for (int i = DB; i > UR; i--)
    {
        int s = 0;
        for (int j = i - 1; j >= UR; j--)
        {
            if (ep8[j] > ep8[i])
                s++;
        }
        x = (x + s) * i;
    }
    this->ep8 = x;
}

void coordCubePhase2::setUDS(array<int, N_EDGES> uds)
{
    int j = 0;
    array<int, 4> arr;
    for (int i = UR; i <= BR; i++)
    {
        int e = uds[i];
        if (e == FR || e == BL || e == BR) {
            arr[j] = e;
            j++;
        }
    }
    int x = 0;
    for (j = 3; j >= 1; j--) {
        int s = 0;
        for (int k = j-1; k >= 0; k--) {
            if(arr[k] > arr[j]) {
                s++;
            }
        }
        x = (x+s)*j;
    }
    // for when we have bugs remember this:
    // this->uds = getUDSliceCoord(this->ep)*24+x;
    this->uds = x;
}