#include <iostream>
#include <fstream>
#include <array>

using namespace std;

const int N_CORNERS = 40320; // Replace with actual value
const int N_MOVE = 18;       // Replace with actual value
array<array<int, N_MOVE>, N_CORNERS> coMoveTable; // Use of std::array

void readBinaryFile() {
    ifstream inFile("cpMoveTable.bin", ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    // Read the entire std::array from the binary file
    inFile.read(reinterpret_cast<char*>(coMoveTable.data()), N_CORNERS * N_MOVE * sizeof(int));

    inFile.close();
}

// int main() {
//     readBinaryFile();

//     // Example output to verify
//     cout << "First row of coMoveTable: ";
//     for (int j = 0; j < N_MOVE; j++) {
//         cout << coMoveTable[0][j] << " ";
//     }
//     cout << endl;

//     return 0;
// }
