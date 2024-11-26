#include "prun.hpp"

using namespace std;

const int MAX_SIZE = 10000;  // Adjust as necessary based on size1 * size2

// need update for 3x3
void buildTable(const string& name, int size, const vector<vector<int>>& move) {

    vector<int> p(size, -1);
    p[0] = 0;

    int count = 1;
    int depth = 0;

    cout << "Building " << name << endl;
    cout << depth << " " << count << endl;

    while (count < size) {
        for (int i = 0; i < size; ++i) {
            if (p[i] == depth) {
                
                array<int, N_MOVE> m;
                for (size_t j = 0; j < N_MOVE; ++j) {
                    // 3x3: int moveIndex = row + move1[j] * size2 + col + move2[j];
                    int moveIndex = move[i][j];
                    m[j] = moveIndex;
                }

                for (int newIndex : m) {
                    if (newIndex >= 0 && newIndex < size && p[newIndex] == -1) {
                        count++;
                        p[newIndex] = depth + 1;
                        if (newIndex == 1940 && name == "PruningTables/coPruningTable") cout << newIndex << ": " << p[newIndex] << endl;
                    }
                }
            }
        }
        depth++;
        // cout << depth << " " << count << endl;
    }
    
    // Write the p vector to a binary file
    ofstream outFile(name + ".bin", ios::binary);
    if (!outFile) {
        cerr << "Error: Could not open file for writing." << endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(p.data()), p.size() * sizeof(int));
    outFile.close();

    cout << "Table written to " << name << ".bin" << endl;
}
