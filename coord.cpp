#include "coord.hpp"

using namespace std;

class coordCube {
    int co;
    int cp;
    int eo;
    int ep;

    // constructor
    coordCube(int co,
            int cp,
            int eo,
            int ep) {
        
        this->co = co;
        this->cp = cp;
        this->eo = eo;
        this->ep = ep;
    }

    void setEdgeOri(array<int, 12> eo) {
        int s = 0;
        // we use base 2 where each bit coresspondes to an edge orientation
        for (int e = UR; e < BR; e++) {
            // multiplying by two at every iteration to form the number digit by digit
            s = 2 * s + eo[e];
        }
    }
    void setCornerOri(array<int, 8> co) {
        int s = 0;
        // we use base 3 where each bit coresspondes to an edge orientation
        for (int c = URF; c < DRB; c++) {
            // multiplying by two at every iteration to form the number digit by digit
            s = 3 * s + co[c];
        }
    }

    void setEdgePerm(array<int, 12> ep) {
        int x = 0;
        for (int e1 = BR; e1 > UR; e1--) {
            int s = 0;
            for (int e2 = e1 - 1; e2 >= UR; e2--) {
                if (ep[e2] > ep[e1]) s++;
            }
            x = (x+s) * e1;
        }
        this->ep = x;
    }
    void setCornerPerm(array<int, 8> cp) {
        int x = 0;
        for (int c1 = DRB; c1 > URF; c1--) {
            int s = 0;
            for (int c2 = c1 - 1; c2 >= URF; c2--) {
                if (cp[c2] > cp[c1]) s++;
            }
            x = (x+s) * c1;
        }
        this->cp = x;
    }
};

// int main() {
//     cout << setCornerPerm({DFR, UFL, ULB, URF, DRB, DLF, DBL, UBR}) << endl;
// }