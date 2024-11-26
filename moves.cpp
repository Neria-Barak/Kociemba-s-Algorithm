#include "moves.hpp"

using namespace std;
// cp co eo

//TODO:
// TwistMove: array[0..2187-1,Ux1..Fsx3] of Word;              - DONE
// FlipMove: array[0..2048-1,Ux1..Fsx3] of Word;               - DONE
// UDSliceMove: array[0..495-1,Ux1..Fsx3] of Word;             - TODO
// CentOriMove: array[0..4096-1,Ux1..Fsx3] of Word;

// CentOriRFLBMod2Move: array[0..16-1,Ux1..Fsx3] of Word;
// TetraMove: array[0..70-1,Ux1..Fsx3] of Word;
// CornPermMove: array[0..40320-1,Ux1..Fsx3] of Word;          - DONE
// UDSliceSortedMove: array[0..11880-1,Ux1..Fsx3] of Word;     - TODO
// UDSliceSortedSymMove: array[0..788-1,Ux1..Fsx3] of Integer;
// Edge8PermMove: array[0..40320-1,Ux1..Fsx3] of Word;         - TODO


array<array<int, N_MOVE>, 2048> eoMoveTable;
void generateEOMoveTable() {
    CubieCube* c = new CubieCube();
    for (int i = 0; i < 2048; i++) {
        c->InvEO(i);
        for (int j = U1M; j <= B3M; j++) {
            c->move(j);
            eoMoveTable[i][j] = c->getEOCoord();
            c->move(inv_move[j]);
        }
    }
}

array<array<int, N_MOVE>, N_TWIST> coMoveTable2;
void generateCOMoveTable() {
    CubieCube* c = new CubieCube();
    for (int i = 0; i < N_TWIST; i++) {
        c->InvCO(i);
        for (int j = U1M; j <= B3M; j++) {
            c->move(j);
            coMoveTable2[i][j] = c->getCOCoord();
            if (i == 1940 && j == F2M) cout << coMoveTable2[i][j] <<  endl;
            c->move(inv_move[j]);
        }
    }
}

array<array<int, N_MOVE>, N_CORNERS_PERM> cpMoveTable2;
void generateCPMoveTable() {
    CubieCube* c = new CubieCube();
    for (int i = 0; i < N_CORNERS_PERM; i++) {
        c->InvCP(i);
        for (int j = U1M; j <= B3M; j++) {
            c->move(j);
            cpMoveTable2[i][j] = c->getCPCoord();
            c->move(inv_move[j]);
        }
    }
}

// array<array<int, N_MOVE>, N_FLIP> eoMoveTable;
// void createEPMoveTable() {
//     CubieCube* c = new CubieCube();
//     for (int i = 0; i < N_FLIP; i++) {
//         c->InvEP(i);
//         for (int j = U1M; j <= B3M; j++) {
//             c->move(j);
//             eoMoveTable[i][j] = c->getEPCoord();
//         }
//     }
// }

void writeCPTable() {
    generateCPMoveTable();

    ofstream outFile("MoveTables/cpMoveTable.bin", ios::binary);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(cpMoveTable2.data()), N_CORNERS_PERM * N_MOVE * sizeof(int));
    
    if (!outFile) {  // Verify that the write operation was successful
        cerr << "Error writing to file." << endl;
    } else {
        cout << "cpMoveTable successfully written to cpMoveTable.bin" << endl;
    }

    outFile.close();
}

void writeCOTable() {
    generateCOMoveTable();

    ofstream outFile("MoveTables/coMoveTable.bin", ios::binary);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(coMoveTable2.data()), N_TWIST * N_MOVE * sizeof(int));
    
    if (!outFile) {  // Verify that the write operation was successful
        cerr << "Error writing to file." << endl;
    } else {
        cout << "coMoveTable successfully written to coMoveTable.bin" << endl;
    }

    outFile.close();
}