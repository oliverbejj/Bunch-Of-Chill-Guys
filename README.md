# **Top Down-NukeDown - Running Instructions**

*This project was developed with significant assistance from ChatGPT and was created during ConUHacks IX 2025.*

## **1. System Requirements**
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


## **7. Credits**
- Developed by **A bunch of chill guys**
- Built using **C++ & SFML**
- Special thanks to **OpenAI**
- Created during **ConUHacks IX 2025**

---
