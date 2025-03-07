# Makefile for SFML Gunfight Game

CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC = src/main.cpp src/Game.cpp src/Player.cpp src/Bullet.cpp src/Map.cpp src/Menu.cpp
OUT = game

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LIBS)

clean:
	rm -f game