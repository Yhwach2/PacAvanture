# Pac advanture
A console-based maze game where the player moves freely in 4 directions, collects coins, avoids enemies, and reaches the exit gate to win.

## Features
- Player movement in 4 directions using arrow keys
- Collectible coins scattered across the map
- Enemies that patrol in fixed movement patterns
- Gate/exit that opens once all coins are collected
- Game over when the player is caught by an enemy
- Console map rendering showing player, enemies, walls, coins, and gate

## What is postponed
- Power-ups (invincibility, speed boost)
- Multiple levels or maps
- Saving/loading game state

## Building
```bash
mkdir build
cd build
cmake ..
cmake --build 
