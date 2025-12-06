## Current Status (Checkpoint 2)

### Implemented Features
- **Complete Map System**: 20x12 grid with walls, random coins, power-ups, and gate
- **Player System**: Movement, scoring, and power-up collection (speed, insta-kill, ghost)
- **Enemy System**: 3 enemies with random patrol patterns
- **Power-up System**: Temporary abilities that change gameplay
- **Game Loop**: Full continuous gameplay with win/lose conditions
- **Automated Testing**: 6 total tests (3 from checkpoint 1, 3 new)

###  How to Play
1. Build: `mkdir build && cd build && cmake .. && make`
2. Run: `./PacAvanture`
3. Controls: WASD or arrow keys to move, Q to quit
4. Goal: Collect all coins while avoiding enemies
5. Power-ups:
    - **S** = Speed boost (5 sec)
    - **K** = Insta-kill (10 sec) - destroy enemies!
    - **G** = Ghost mode (4 sec) - walk through walls!

###  Planned Features (maybe in future)
1. Different enemy types (fast, smart, etc.)
2. Multiple levels with increasing difficulty
3. Sound effects and better visuals
4. High score tracking
5. Power-up combinations

###  Known Issues
- Input might be laggy on some systems
- No level progression yet (one maze only)
- Simple enemy AI (random moves)
- Screen flickers during redraw

###  Running Tests
```bash
cd build
ctest --verbose
# Runs both MapTests and PowerUpTests