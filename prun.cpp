#include "prun.hpp"

using namespace std;

// TODO:
// (* phase1 *)
// sliceflipPrun = prunTable["sliceflipPrun",sliceMove,495,flipMove,2048];
// slicetwistPrun = prunTable["slicetwistPrun",sliceMove,495,twistMove,2187];
// (* phase2 *)
// edge4edge8Prun = prunTable["edge4edge8Prun",edge4Move,24,edge8Move,40320];
// edge4cornerPrun = prunTable["edge4cornerPrun",edge4Move,24,cornerMove,40320];

// need update for 3x3
void buildTable(const string &name, int size1, const vector<vector<int>> &move1, int size2, const vector<vector<int>> &move2)
{

    vector<vector<int>> p(size1, vector<int>(size2, -1));
    p[0][0] = 0;

    int count = 1;
    int depth = 0;

    cout << "Building " << name << endl;
    cout << depth << " " << count << endl;

    while (count < size1 * size2)
    {
        for (int i = 0; i < size1; i++)
        {
            for (int j = 0; j < size2; j++)
            {
                if (p[i][j] == depth)
                {
                    // iterates over every move
                    // array<array<int, 2> , N_MOVE> m;
                    // for (size_t move = 0; move < N_MOVE; move++) {
                    //     m[move][0] = move1[i][move];
                    //     m[move][1] = move2[j][move];
                    // }

                    // for (int move = 0; move < N_MOVE; move++) {
                    //     int i1 = m[move][0];
                    //     int i2 = m[move][1];
                    //     if (i1 >= 0 && i1 < size1 && i2 >= 0 && i2 < size2 &&  p[i1][i2] == -1) {
                    //         count++;
                    //         p[i1][i2] = depth + 1;
                    //     }
                    // }
                    for (int move = 0; move < N_MOVE; move++)
                    {
                        int i1 = move1[i][move];
                        int i2 = move2[j][move];
                        // if (depth == 6) cout << p[i1][i2] << endl;
                        if (i1 >= 0 && i1 < size1 && i2 >= 0 && i2 < size2 && p[i1][i2] == -1)
                        {
                            count++;
                            p[i1][i2] = depth + 1;
                        }
                        // else if (i1 == 288 && i2 == 577) {
                        //     cout << i << " " << j << " " << move << endl;
                        // }
                    }
                }
            }
        }
        depth++;
        cout << depth << " " << count << endl;
    }

    // Write the p vector to a binary file
    ofstream outFile(name + ".bin", ios::binary);
    if (!outFile)
    {
        cerr << "Error: Could not open file for writing." << endl;
        return;
    }
    
    // Write the dimensions of the 2D vector for reconstruction
    // size_t rows = p.size();
    // size_t cols = rows > 0 ? p[0].size() : 0;
    // outFile.write(reinterpret_cast<const char*>(&rows), sizeof(rows));
    // outFile.write(reinterpret_cast<const char*>(&cols), sizeof(cols));

    // Flatten and write the data
    for (const auto& row : p) {
        outFile.write(reinterpret_cast<const char*>(row.data()), row.size() * sizeof(int));
    }    outFile.close();

    cout << "Table written to " << name << ".bin" << endl;
}
