# **Gunfight Game - Running Instructions**

*This project was developed with significant assistance from ChatGPT and was created during ConUHacks IX 2025.*

## **1. System Requirements**
- **Operating System:** Linux
- **Dependencies:**
  - [SFML Library](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library)
  - A C++ compiler supporting C++11 or higher (e.g., `g++`)
  - `make` for build automation

---

## **2. Installation of Dependencies**
Before running the game, ensure that **SFML, a C++ compiler, and make** are installed on your system.

---

## **3. Building the Game**
### **Option 1: Using `runmake.sh` (Recommended)**
1. Open a terminal in the game directory.
2. Run the following command:
   ```sh
   chmod +x runmake.sh
   ./runmake.sh
   ```
   - This script will **clean, build, and run** the game.

### **Option 2: Manually Using `Makefile`**
1. Open a terminal in the project directory.
2. Run:
   ```sh
   make clean
   make
   ```
   - This will compile the source code into an executable.

---

## **4. Running the Game**
Once compiled, run:
```sh
./game
```

The game will launch in **fullscreen mode**. You can **exit anytime** using `Esc`.

---

## **5. Controls**
### **Player 1 (Green)**
- **Move:** `W, A, S, D`
- **Shoot:** `Spacebar`

### **Player 2 (Red)**
- **Move:** `Arrow Keys`
- **Shoot:** `Enter`

### **Additional Controls**
- **Open/Close Menu:** `Esc`
- **Navigate Menu:** `Up/Down Arrows`
- **Select Option:** `Enter`

---

## **6. Game Features**
- **Multiplayer**: Two-player local battle.
- **Health System**: Players lose health when hit by bullets.
- **Score & Rounds**: Each round ends when a player dies; the score updates.
- **Obstacles & Map Layout**: Dynamic environment with walls and obstacles.
- **Background Music & Sound Effects**.

---

## **7. Troubleshooting**
### **Issue: SFML Not Found**
If you get an error about missing SFML, ensure it is installed correctly:
```sh
ldd ./game | grep sfml
```
If the output shows missing SFML libraries, reinstall SFML.

### **Issue: Game Won't Start**
Check if the game binary has execution permissions:
```sh
chmod +x game
./game
```

### **Issue: Graphics Lag**
Run the game in **windowed mode** by modifying `Game.cpp`:
Change:
```cpp
window(sf::VideoMode::getDesktopMode(), "SFML Gunfight Game", sf::Style::Fullscreen)
```
To:
```cpp
window(sf::VideoMode(800, 600), "SFML Gunfight Game", sf::Style::Default)
```

---

## **8. Credits**
- Developed by **A bunch of chill guys**
- Built using **C++ & SFML**
- Special thanks to **open-source contributors**
- Created during **ConUHacks IX 2025**

---
