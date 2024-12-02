#include "moves.hpp"

using namespace std;
// cp co eo

//TODO:
// TwistMove: array[0..2187-1,Ux1..Fsx3] of Word;              - DONE
// FlipMove: array[0..2048-1,Ux1..Fsx3] of Word;               - DONE
// UDSliceMove: array[0..495-1,Ux1..Fsx3] of Word;             - DONE
// CentOriMove: array[0..4096-1,Ux1..Fsx3] of Word;

// CentOriRFLBMod2Move: array[0..16-1,Ux1..Fsx3] of Word;
// TetraMove: array[0..70-1,Ux1..Fsx3] of Word;
// CornPermMove: array[0..40320-1,Ux1..Fsx3] of Word;          - DONE
// UDSliceSortedMove: array[0..11880-1,Ux1..Fsx3] of Word;     - TODO
// UDSliceSortedSymMove: array[0..788-1,Ux1..Fsx3] of Integer;
// Edge8PermMove: array[0..40320-1,Ux1..Fsx3] of Word;         - TODO


// TODO:
// (* phase1 *)
// sliceflipPrun = prunTable["sliceflipPrun",sliceMove,495,flipMove,2048];
// slicetwistPrun = prunTable["slicetwistPrun",sliceMove,495,twistMove,2187];
// (* phase2 *)
// edge4edge8Prun = prunTable["edge4edge8Prun",edge4Move,24,edge8Move,40320];  
// edge4cornerPrun = prunTable["edge4cornerPrun",edge4Move,24,cornerMove,40320];


array<array<int, N_MOVE>, N_SLICE> UDSOMoveTable2;
void generateUDSOMoveTable() {
    CubieCube* c = new CubieCube();
    for (int i = 0; i < N_SLICE; i++) {
        c->InvUDSO(i);
        for (int j = U1M; j <= B3M; j++) {
            c->move(j);
            UDSOMoveTable2[i][j] = c->getUDSOCoord();
            c->move(inv_move[j]);
        }
    }
}

array<array<int, N_MOVE>, N_FLIP> eoMoveTable2;
void generateEOMoveTable() {
    CubieCube* c = new CubieCube();
    for (int i = 0; i < N_FLIP; i++) {
        c->InvEO(i);
        for (int j = U1M; j <= B3M; j++) {
            c->move(j);
            eoMoveTable2[i][j] = c->getEOCoord();
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

void writeEOTable() {
    generateEOMoveTable();

    ofstream outFile("MoveTables/eoMoveTable.bin", ios::binary);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(eoMoveTable2.data()), N_FLIP * N_MOVE * sizeof(int));
    
    if (!outFile) {  // Verify that the write operation was successful
        cerr << "Error writing to file." << endl;
    } else {
        cout << "eoMoveTable successfully written to eoMoveTable.bin" << endl;
    }

    outFile.close();
}

void writeUDSOTable() {
    generateUDSOMoveTable();

    ofstream outFile("MoveTables/udsoMoveTable.bin", ios::binary);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(UDSOMoveTable2.data()), N_SLICE * N_MOVE * sizeof(int));
    
    if (!outFile) {  // Verify that the write operation was successful
        cerr << "Error writing to file." << endl;
    } else {
        cout << "udsoMoveTable successfully written to udsoMoveTable.bin" << endl;
    }

    outFile.close();
}