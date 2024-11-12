#include "coord.hpp"

int main() {
    
    coordCubePhase1* cc1 = new coordCubePhase1(0,0,0); 
    cc1->setCornerOri({2, 0, 0, 1, 1, 0, 0, 2});
    CubieCube* cc = new CubieCube();
    cc->InvCO(cc1->co);
    for (int i = 0; i < N_CORNERS; i++) {
        cout << cc->co[i] << " ";
    }
    cout << endl;

    return 0;
}