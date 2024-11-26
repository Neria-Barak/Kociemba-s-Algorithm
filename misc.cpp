#include "misc.hpp"

// Function to convert move enums to their string representation
string moveToString(int move)
{
    switch (move)
    {
    case U1M:
        return "U";
    case U2M:
        return "U2";
    case U3M:
        return "U'";
    case R1M:
        return "R";
    case R2M:
        return "R2";
    case R3M:
        return "R'";
    case F1M:
        return "F";
    case F2M:
        return "F2";
    case F3M:
        return "F'";
    case D1M:
        return "D";
    case D2M:
        return "D2";
    case D3M:
        return "D'";
    case L1M:
        return "L";
    case L2M:
        return "L2";
    case L3M:
        return "L'";
    case B1M:
        return "B";
    case B2M:
        return "B2";
    case B3M:
        return "B'";
    default:
        return "";
    }
}

// Function to generate a random scramble
vector<int> generateScramble(int length)
{
    srand(std::time(nullptr)); // Seed for randomness
    vector<int> scramble;      // Store the sequence of moves
    int lastMove = -1;

    for (int i = 0; i < length; ++i)
    {
        int move;
        do
        {
            move = rand() % N_MOVE; // Generate a random move within range
        } while (move / 3 == lastMove / 3); // Avoid consecutive moves on the same face
        scramble.push_back(move); // Add move to scramble
        lastMove = move;
    }
    return scramble;
}

// Function to convert scramble vector to string
string ScrambleToString(vector<int> scramble)
{
    string scrambleStr;
    for (int move : scramble)
    {
        scrambleStr += moveToString(move) + " "; // Use moveToString for each move
    }
    return scrambleStr;
}