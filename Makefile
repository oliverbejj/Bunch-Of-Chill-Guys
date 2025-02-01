# Makefile for SFML Gunfight Game

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# SFML libraries to link
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source and output files
SRC = main.cpp
OUT = game

# Default target: build the game
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LIBS)

# Clean up compiled files
clean:
	rm -f $(OUT)
