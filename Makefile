# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11 -g

# Output binary name
TARGET = main

# Source files
SRC = coord.cpp cubie.cpp moves.cpp defs.cpp

# Header files
HEADERS = coord.hpp cubie.hpp defs.hpp enums.hpp moves.hpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Compile each source file into an object file
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
