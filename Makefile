# Variables
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -Wpedantic -pedantic -I/usr/include/SDL2 -D_REENTRANT
LDFLAGS  := -lSDL2 -lSDL2_image -lSDL2_ttf -pthread
SRC_DIR   := src
OBJ_DIR   := build
BIN       := pong_game

# All source files
SOURCES := $(wildcard $(SRC_DIR)/**/*.cpp) # Recursively find all .cpp files in src
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Default rule
all: $(BIN)

# Build binary
$(BIN): $(OBJECTS)
	@echo "[Linking] $@"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "[Compiling] $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	@echo "[Cleaning] Removing build files..."
	@rm -rf $(OBJ_DIR) $(BIN)

# Run the game
run: all
	./$(BIN)
