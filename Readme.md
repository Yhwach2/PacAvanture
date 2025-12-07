# PacAvanture - Final Version

A console-based maze chase game where you collect coins, avoid enemies, and use power-ups to reach the exit across multiple levels.

## Features
- **3 Progressive Levels**: Each level gets harder with more complex mazes
- **Power-up System**: Speed boost, Insta-kill, and Ghost mode
- **Save/Load**: Save your progress between sessions
- **Enemy AI**: Enemies patrol with random movement patterns
- **Lives System**: 3 lives to complete all levels
- **Score Tracking**: Points for coins, enemies, and level completion

##  How to Play
1. **Build**: `mkdir build && cd build && cmake .. && make`
2. **Run**: `./PacAvanture`
3. **Controls**:
    - WASD or Arrow Keys: Move
    - P: Save game during play
    - Q: Quit to menu
4. **Goal**: Collect all coins in each level, reach the open gate
5. **Power-ups**:
    - **S**: Speed boost (5 seconds)
    - **K**: Insta-kill (10 seconds) - destroy enemies on touch
    - **G**: Ghost mode (4 seconds) - walk through walls

##  Project Structure