# Add Map.cpp to the source files
SRC = src/main.cpp src/Game.cpp src/Player.cpp src/Bullet.cpp src/Map.cpp

# Build target
game: $(SRC)
	g++ -Wall -std=c++17 -Iinclude $(SRC) -o game -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f game