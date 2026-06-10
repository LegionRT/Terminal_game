# Terminal Game: Labyrinth Escape

A text-based terminal RPG where you must navigate through 5 labyrinth locations, battle monsters, solve puzzles, and defeat the final boss.

##Key Features
- **5 unique locations** with procedurally generated enemies and items.
- **Combat system**: attack, use potions, view stats, and **escape** (50% chance).
- **Save system**: full progress tracking (HP, inventory, location state, defeated enemies, opened doors and chests).
- **NPCs and dialogue**: interact with merchants and hermits. You can obtain items, open doors, or **jump straight into combat** from the dialogue menu.
- **Locked chests and doors**: to open them, you must solve a math problem, answer a riddle, or pick the lock. Making a mistake causes damage.

## Controls
The game is controlled entirely by entering numbers (selecting menu options).
- `1, 2, 3...` — select an action (movement, combat, chest, NPC).
- In inventory: equip weapons, use potions.
- In combat: attack, potion, stats, escape.

## Build and Run

### Option 1: Visual Studio (Windows)
1. Open the `Terminal_game.sln` file in Visual Studio.
2. Ensure the `Debug` or `Release` configuration and `x64` platform are selected.
3. Press **Ctrl + Shift + B** (Build Solution) or **F5** (Start Debugging).

### Option 2: Using Makefile (GCC / MinGW / Linux / macOS)
If you have the `g++` compiler and `make` utility installed:
1. Open a terminal in the source code folder (where all `.cpp` files are located).
2. Run the build command:
   make or mingw32-make
### Option 3:How to run
1. On Windows you just run `terminal_game.exe`.
2. On Linux you need:
   2.1. Run terminal in folder where saved `terminal_game` (same folder where `Makefile`).
   2.2. Print `./terminal_game`

### Option 4:GOOD LUCK
Thank's for playing! That's my first game on C++ (and i now, this is peace of ... bad)
