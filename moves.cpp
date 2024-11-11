#include "moves.hpp"

using namespace std;

array<array<int, N_MOVE>, N_TWIST> coMoveTable;
void createCOMoveTable() {

    CubieCube* c = new CubieCube();
    for (int i = 0; i < N_TWIST; i++) {
        c->InverseCO(i);
        for (int j = U1M; j <= B3M; j++) {
            c->move(j);
            coMoveTable[i][j] = c->getCOCoord();
        }
    }
}

int main() {
    cout << "hey" << endl;
    
    // Create CO move table
    createCOMoveTable();

    cout << "hey" << endl;

    // Write the move table to a file
    ofstream outFile("coMoveTable.txt");
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return 1;
    }

    for (int i = 0; i < N_TWIST; i++) {
        for (int j = 0; j < N_MOVE; j++) {
            outFile << coMoveTable[i][j] << (j == N_MOVE - 1 ? '\n' : ' ');
        }
    }

    outFile.close();
    cout << "coMoveTable successfully written to coMoveTable.txt" << endl;

    return 0;
}