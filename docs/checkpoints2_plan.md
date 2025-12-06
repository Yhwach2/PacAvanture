##### Checkpoint 2: Second Feature Plan

## Feature Name
Enemy Patrol System with Power-up Abilities

## Description
Add enemies that move around the maze with basic AI, plus special power-ups that drop randomly. Three power-up types: Speed Boost (move faster for 5 sec), Insta-Kill (destroy enemies for 10 sec), and Ghost Mode (walk through walls for 4 sec). This makes the game challenging and gives players cool temporary abilities to deal with enemies.

## Why This Feature?
The first checkpoint was just moving around collecting coins which gets boring fast. This adds actual gameplay - you gotta avoid enemies now! And the power-ups give you options instead of just running away. It builds on the map and player systems we already have, and makes the game way more fun to play. Plus it's a good step up in complexity without being too crazy.

## Classes Involved
- **Enemy** (new class): Handles enemy movement and alive/dead state
- **Player** (modified): Add power-up timers and ability checks
- **Map** (modified): Spawn and track power-ups on the grid
- **Game** (new class): Main game loop that ties everything together

## Expected User Workflow
1. Start game, see enemies moving around (E characters)
2. Try to collect coins while avoiding enemies
3. See power-up drop (S, K, or G icon)
4. Run over it to collect
5. Get temporary ability:
    - **Speed** (S): Move faster to escape enemies
    - **Kill** (K): Destroy enemies you touch instead of dying
    - **Ghost** (G): Walk through walls to take shortcuts
6. Use ability strategically, timer counts down on screen
7. Collect all coins, gate opens (G becomes g), reach gate to win

## Estimated Time
About 4-5 hours total:
- 1 hour: Enemy class with movement logic
- 1 hour: Player power-up system
- 1.5 hours: Game loop and integration
- 1 hour: Testing and debugging
- 0.5 hours: Documentation

## Technical Approach
- Game runs at ~10 FPS (100ms per frame)
- Enemies use simple random movement with occasional direction changes
- Power-up timers measured in game ticks (30 ticks = 1 sec)
- Map stores power-ups separate from grid for flexibility
- Cross-platform input handling (WASD/arrows)

## Files to Create/Modify
### New Files:
- `include/Enemy.h` - Enemy class declaration
- `src/Enemy.cpp` - Enemy movement implementation
- `include/Game.h` - Game loop controller
- `src/Game.cpp` - Main game logic
- `tests/test_powerups.cpp` - New test cases

### Modified Files:
- `include/Player.h` - Add power-up enum and methods
- `src/Player.cpp` - Implement power-up logic
- `include/Map.h` - Add power-up tracking
- `src/Map.cpp` - Power-up spawning/management
- `src/main.cpp` - Switch to Game class
- `CMakeLists.txt` - Add new files to build

## Testing Plan
### Automated Tests (CTest):
1. **Power-up collection**: Verify player can collect and store power-ups
2. **Enemy mechanics**: Test enemy creation, movement, and kill state
3. **Power-up timers**: Check that timers decrement properly

### Manual Tests:
1. Full gameplay from start to win
2. Each power-up type functionality
3. Enemy collision with and without insta-kill
4. Ghost mode wall-passing
5. Gate opening when coins collected

## Integration with First Feature
- Uses existing `Map::isWall()` for collision (except ghost mode)
- Builds on `Player` position and movement system
- Extends `Map` rendering to show enemies and power-ups
- Maintains same scoring and coin collection mechanics
- Adds to the "collect coins → open gate → win" core loop

## Success Metrics
- [ ] Game compiles and runs without errors
- [ ] Enemies move autonomously on screen
- [ ] All 3 power-up types work as described
- [ ] Win condition (collect coins, reach open gate) still works
- [ ] Lose condition (touch enemy without insta-kill) works
- [ ] All automated tests pass
- [ ] Code follows same style as checkpoint 1

## Potential Risks
1. **Probably Input lag**: Terminal input might be slow on some systems
2. **Screen flicker**: Clearing screen each frame might look bad
3. **Balance issues**: Power-ups might be too powerful or weak
4. **Cross-platform bugs**: Windows vs Mac/Linux differences

## Mitigation Strategies
1. Use simple input polling, not blocking waits
2. Only redraw when necessary, not every frame
3. Adjust power-up durations during playtesting
4. Use preprocessor directives for platform-specific code

---
