#include "tables.hpp"

using namespace std;

vector<vector<int>> readBinaryFile(string file, int size1, int size2) {
    vector<vector<int>> table;
    table.resize(size1, vector<int>(size2));

    ifstream inFile(file + ".bin", ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        exit(1);
    }

    if (size2 == 1) {
        // Read data into a vector<int>
        vector<int> p(size1);
        inFile.read(reinterpret_cast<char*>(p.data()), size1 * sizeof(int));
        if (!inFile) {
            cerr << "Error reading data." << endl;
            exit(1);
        }
        // Copy data into table
        for (int i = 0; i < size1; ++i) {
            table[i][0] = p[i];
        }
    } else {
        for (int i = 0; i < size1; ++i) {
            inFile.read(reinterpret_cast<char*>(table[i].data()), size2 * sizeof(int));
            if (!inFile) {
                cerr << "Error reading row " << i << endl;
                break;
            }
        }
    }

    inFile.close();


    // // Print the first 3 lines of the table
    // cout << "First 3 lines of the table:" << endl;
    // for (int i = 0; i < min(3, size1); ++i) { // Ensure we don't go out of bounds
    //     for (int j = 0; j < size2; ++j) {
    //         cout << table[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    cout << file << " loaded successfully." << endl;
    return table;
}


vector<vector<int>> coMoveTable;
vector<vector<int>> cpMoveTable;
vector<vector<int>> eoMoveTable;
vector<vector<int>> UDSOMoveTable;
vector<vector<int>> UDSPMoveTable;
vector<vector<int>> ep8MoveTable;

// vector<vector<int>> coPrunTable;
// vector<vector<int>> cpPrunTable;
vector<vector<int>> sliceFlipPrunTable;
vector<vector<int>> sliceTwistPrunTable;



void init_tables() {
    // Move Tables
    coMoveTable = readBinaryFile("MoveTables/coMoveTable", N_TWIST, N_MOVE);
    cpMoveTable = readBinaryFile("MoveTables/cpMoveTable", N_CORNERS_PERM, N_MOVE);
    eoMoveTable = readBinaryFile("MoveTables/eoMoveTable", N_FLIP, N_MOVE);
    UDSOMoveTable = readBinaryFile("MoveTables/udsoMoveTable", N_SLICE, N_MOVE);

    UDSPMoveTable = readBinaryFile("MoveTables/udspMoveTable", N_PERM_4, N_MOVE);
    ep8MoveTable = readBinaryFile("MoveTables/ep8MoveTable", N_UD_EDGES, N_MOVE);

    // Pruning Tables
    sliceFlipPrunTable = readBinaryFile("PruningTables/sliceFlipPrun", N_SLICE, N_FLIP);
    sliceTwistPrunTable = readBinaryFile("PruningTables/sliceTwistPrun", N_SLICE, N_TWIST);
}