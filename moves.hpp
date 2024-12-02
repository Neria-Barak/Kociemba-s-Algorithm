#ifndef MOVES
#define MOVES

#include <array>
#include "cubie.hpp"
#include <iostream>
#include <fstream>
#include "defs.hpp"

void generateCOMoveTable();

void writeCOTable();
void writeCPTable();
void writeEOTable();
void writeUDSOTable();

#endif