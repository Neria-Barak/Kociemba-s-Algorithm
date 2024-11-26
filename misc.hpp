#ifndef MISC_H
#define MISC_H

#include "coord.hpp"
#include "prun.hpp"
#include "defs.hpp"
#include "moves.hpp"

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "solver.hpp"
#include "tables.hpp"

using namespace std;


string moveToString(int move);
vector<int> generateScramble(int length);
string ScrambleToString(vector<int> scramble);


#endif