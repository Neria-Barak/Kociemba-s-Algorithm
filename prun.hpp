#ifndef PRUN_HPP
#define PRUN_HPP

#include <string>
#include <array>
#include "moves.hpp"
#include "defs.hpp"
#include <vector>

void buildTable(const string& name, int size1, const vector<vector<int>>& move1, int size2, const vector<vector<int>>& move2);

#endif