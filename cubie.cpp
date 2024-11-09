#include "cubie.h"

using namespace std;

class CubieCube {
    array<int, 8> co;
    array<int, 8> cp;
    array<int, 12> eo;
    array<int, 12> ep;

    // constructor
    CubieCube(array<int, 8> co,
          array<int, 8> cp,
          array<int, 12> eo,
          array<int, 12> ep) {
        
        this->co = co;
        this->cp = cp;
        this->eo = eo;
        this->ep = ep;
    }

    void multipy_edge(CubieCube* other) {
        for (int e = UR; e <= BR; e++) {
            array<int, 12> eo = {0,0,0,0,0,0,0,0,0,0,0,0};
            array<int, 12> ep = {0,0,0,0,0,0,0,0,0,0,0,0};
            
            for (int  e = UR; e <= BR; e++) {
                ep[e] = this->ep[other->ep[e]];
                eo[e] = (this->eo[other->ep[e]] + other->eo[e]) % 2;
            }

            for (int e = UR; e <= BR; e++) {
                this->ep[e] = ep[e];
                this->eo[e] = eo[e];
            }
        }
    }

    void multipy_corner(CubieCube* other) {
        for (int e = UR; e <= BR; e++) {
            array<int, 12> co = {0,0,0,0,0,0,0,0};
            array<int, 12> cp = {0,0,0,0,0,0,0,0};
            
            for (int  c = URF; e <= DRB; e++) {
                ep[c] = this->ep[other->ep[e]];
                int oriThis = this->eo[other->ep[e]];
                int oriOther = other->eo[e];

                if (oriThis < 3 && oriOther < 3) {
                    co[e] = (oriThis + oriOther) % 3;
                }else if (oriThis < 3 && oriOther >= 3) {
                    co[e] = (oriThis + oriOther) % 3 + 3;
                }else if (oriThis >= 3 && oriOther < 3) {
                    co[e] = (oriThis - oriOther) % 3 + 3;
                } else {
                    co[e] = (oriThis - oriOther) % 3;
                }
            }

            for (int c = URF; c <= DRB; c++) {
                this->cp[c] = cp[c];
                this->co[c] = co[c];
            }
        }
    }
};