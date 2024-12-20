#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "coord.hpp"
#include "prun.hpp"
#include "defs.hpp"
#include "moves.hpp"
#include "tables.hpp"

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include "misc.hpp"
#include <unordered_set>

vector<int> solveCube(CubieCube* cube, unsigned int maxLen);

#endif
