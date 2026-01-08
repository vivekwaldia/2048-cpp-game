# 🎮 2048 Game

A terminal-based C++ implementation of the classic 2048 puzzle game with smooth gameplay mechanics and intelligent tile merging!

## ✨ Features

* **Classic 2048 Gameplay**
  + Authentic tile sliding and merging mechanics
  + 4×4 grid with clean terminal interface
  + Real-time score tracking

* **Smart Game Logic**
  + Intelligent tile spawning (90% chance for 2, 10% chance for 4)
  + Automatic game over detection
  + Move validation to prevent invalid actions

* **User-Friendly Design**
  + Clear visual board with borders
  + Simple WASD controls
  + Dynamic screen updates after each move
  + Instant feedback for invalid moves

## 🎓 What I Learned

Building this project helped me understand several important C++ programming concepts:

* **Object-Oriented Programming**: Designed a complete `Game` class with encapsulated data and methods, demonstrating how OOP principles create maintainable code
* **STL Containers**: Used `vector<vector<int>>` for dynamic 2D board representation and `pair` for coordinate storage
* **Random Number Generation**: Implemented the Mersenne Twister engine (`mt19937`) with proper seeding for high-quality randomness
* **Algorithm Optimization**: Created a single `swipeRight()` function that's cleverly adapted for all four directions, reducing code duplication and potential bugs
* **Game State Management**: Developed logic to detect valid moves and end-game conditions by checking for empty spaces and possible merges
* **User Input Handling**: Processed keyboard input with case-insensitive controls and provided clear feedback for invalid actions
* **Terminal UI Design**: Used ANSI escape codes for screen clearing and `setw()` for aligned grid formatting
* **Memory Management**: Efficiently handled dynamic data structures without memory leaks

This project taught me that elegant code isn't just about making things work - it's about designing systems that are efficient, maintainable, and user-friendly.

## 🚀 Getting Started

### Prerequisites

* C++ compiler with C++11 support or higher (g++, clang++)
* Terminal/Command prompt

### Compilation

```bash
g++ -std=c++11 game.cpp -o 2048
```

### Running the Game

```bash
./2048
```

On Windows:

```bash
g++ -std=c++11 game.cpp -o 2048.exe
2048.exe
```

## 🎯 How to Play

1. Launch the game to see a 4×4 grid with two random tiles
2. Use **W/A/S/D** keys to slide all tiles in the chosen direction
3. When two tiles with the same number touch, they merge into one
4. Each merge adds the new tile's value to your score
5. After each valid move, a new tile (2 or 4) appears
6. Keep playing until no moves remain or you reach 2048!
7. Press **Q** to quit anytime

## 🎮 Controls

| Key | Action |
|-----|--------|
| `W` | Move tiles up |
| `A` | Move tiles left |
| `S` | Move tiles down |
| `D` | Move tiles right |
| `Q` | Quit game |

## 🛠️ Technical Details

* **Language:** C++ (C++11 standard)
* **Design Pattern:** Object-Oriented Programming with encapsulation
* **Random Generation:** Mersenne Twister engine for quality randomness
* **Core Algorithm:** Optimized single-direction merge logic adapted for all movements
* **Data Structure:** 2D vector for dynamic board management

## 📊 Game Mechanics

### Tile Spawning
* 90% probability to spawn a `2`
* 10% probability to spawn a `4`

### Game Over Conditions
1. Board is completely full
2. No adjacent tiles can merge

### Scoring System
* Score increases by the value of each newly merged tile
* Example: Merging two `4`s creates an `8` and adds 8 points

## 🧩 Code Structure

```cpp
class Game {
    - 4×4 board representation
    - Score tracking
    - Random number generation (Mersenne Twister)
    - Movement methods (up, down, left, right)
    - swipeRight() - Core merge algorithm
    - Game state validation
    - Display rendering with ANSI codes
}
```

## 🤝 Contributing

Feel free to fork this project and add your own features! Some ideas:

* Add undo functionality
* Implement best score tracking with file I/O
* Add color support for different tile values
* Create animations for tile movements
* Add difficulty modes (6×6 grid, goal of 4096, etc.)

## 📝 License

This project is licensed under the MIT License - feel free to use and modify for personal and educational purposes.

## 👨‍💻 Author

Created with ❤️ as a learning project during my 2nd semester of Computer Science Engineering

**GitHub:** [@vivekwaldia](https://github.com/vivekwaldia)

---

**Enjoy the game and aim for 2048!** 🎉
