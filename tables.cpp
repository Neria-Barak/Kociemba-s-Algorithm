#include "tables.hpp"

using namespace std;

vector<vector<int>> readBinaryFile(string file, int size1, int size2) {
    // size1 = N_CORNERS_PERM, size2 = N_MOVE
    vector<vector<int>> table;
    table.resize(size1, vector<int>(size2)); // Allocate memory for table

    ifstream inFile(file + ".bin", ios::binary); // Ensure the path is correct
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        exit(1);
    }

    for (int i = 0; i < size1; ++i) {
        inFile.read(reinterpret_cast<char*>(table[i].data()), size2 * sizeof(int));
        if (!inFile) {
            cerr << "Error reading row " << i << endl;
            break;
        }
    }

    inFile.close();

    cout << "table loaded successfully." << endl;
    return table;
}

vector<vector<int>> coMoveTable;
vector<vector<int>> cpMoveTable;
vector<vector<int>> coPrunTable;
vector<vector<int>> cpPrunTable;

void init_tables() {
    coMoveTable = readBinaryFile("MoveTables/coMoveTable", N_TWIST, N_MOVE);
    cpMoveTable = readBinaryFile("MoveTables/cpMoveTable", N_CORNERS_PERM, N_MOVE);
    coPrunTable = readBinaryFile("PruningTables/coPruningTable", N_TWIST, 1);
    cpPrunTable = readBinaryFile("PruningTables/cpPruningTable", N_CORNERS_PERM, 1);
}