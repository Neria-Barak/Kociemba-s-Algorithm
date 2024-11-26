# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11 -g -o3

# Output binary name
TARGET = main

# Source files
SRC = coord.cpp cubie.cpp defs.cpp main.cpp prun.cpp moves.cpp solver.cpp tables.cpp misc.cpp

# Header files
HEADERS = coord.hpp cubie.hpp defs.hpp enums.hpp prun.hpp moves.hpp solver.hpp tables.hpp misc.hpp

# Object directory
OBJ_DIR = build

# Object files in the OBJ_DIR directory
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

# Default target
all: $(OBJ_DIR) $(TARGET)

# Ensure the object directory exists
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Compile each source file into an object file in OBJ_DIR
$(OBJ_DIR)/%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)
	rm -rf $(OBJ_DIR)

# Run the program
run: $(TARGET)
	./$(TARGET)
