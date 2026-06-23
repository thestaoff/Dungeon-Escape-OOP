# Dungeon Escape — C++ OOP Project

A terminal-based dungeon adventure game written in C++. The player explores rooms, fights enemies, collects treasures, completes challenges, manages a limited move count, and tries to reach the exit.

## Features

- Linked-list dungeon made of connected `Room` objects
- Combat against randomly damaging enemies
- Treasure collection and inventory management
- Random challenge outcomes and rewards
- Score, health, attack, and move tracking
- Backtracking using a stack
- Challenges served in order using a queue
- Input validation for menu choices

## OOP Concepts Demonstrated

| Concept | Used in |
|---|---|
| Classes and objects | `Game`, `Player`, `Dungeon`, `Room`, `Enemy`, `Treasure` |
| Encapsulation | Private data members with public methods/getters |
| Composition | `Game` manages a `Player` and a `Dungeon`; rooms contain enemies/treasures |
| Dynamic memory | Rooms, enemies, treasures, player, and dungeon are created dynamically |
| Constructors/destructors | Each game entity initializes and cleans up its own resources |
| STL containers | `vector`, `stack`, and `queue` |
| Header guards | All header files |

## Project Structure

```text
Dungeon-Escape-OOP/
├── include/
│   ├── Dungeon.h
│   ├── Enemy.h
│   ├── Game.h
│   ├── Player.h
│   ├── Room.h
│   └── Treasure.h
├── src/
│   └── main.cpp
├── docs/
│   └── CLASS_DIAGRAM.md
├── .gitignore
├── CMakeLists.txt
├── LICENSE
├── Makefile
└── README.md
```

## Build and Run

### Option 1 — g++

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude src/main.cpp -o dungeon_escape
./dungeon_escape
```

### Option 2 — Make

```bash
make
make run
```

### Option 3 — CMake

```bash
cmake -S . -B build
cmake --build build
./build/dungeon_escape
```

## How to Play

1. Enter a player name.
2. Deal with any enemy, treasure, or challenge in the current room.
3. Choose to move forward, backtrack, or rest.
4. Reach the final room before your moves run out and without losing all health.

## Notes

This is a console project, so it has no external libraries or special installation requirements. A C++17-compatible compiler is all that is needed.
