#ifndef TABLES_HPP
#define TABLES_HPP

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

extern vector<vector<int>> coMoveTable;
extern vector<vector<int>> cpMoveTable;
extern vector<vector<int>> coPrunTable;
extern vector<vector<int>> cpPrunTable;

void init_tables();

#endif