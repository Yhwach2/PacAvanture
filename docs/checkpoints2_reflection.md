# Checkpoint 2 Reflection

## What I Implemented
Added power-up system with 3 types (speed, insta-kill, ghost mode) and basic enemy AI. The enemies patrol randomly and players can now collect power-ups to get temporary advantages. When you have insta-kill active, you can destroy enemies instead of just avoiding them. Ghost mode lets you walk through walls briefly which is pretty cool.

## How It Integrates with First Feature
Builds directly on the map and player from checkpoint 1. The map now spawns power-ups alongside coins. Player class got expanded with power-up timers. Enemies use the same coordinate system and collision checks. It all fits together - you still collect coins to open the gate, but now there's enemies to avoid and power-ups to help you.

## Challenges Faced
1. **Input handling across platforms** - Windows uses _getch(), Linux/Mac different. Made a simple hybrid system
2. **Power-up spawning** - Making sure they don't spawn on walls or coins
3. **Game timing** - Power-ups need to expire after X seconds, had to figure out the tick system
4. **Screen clearing** - Different commands for Windows (cls) vs Linux/Mac (clear)

## What I Learned
- How to make simple game loop with update/render cycles
- Cross-platform terminal stuff is annoying but doable
- Timing systems for temporary effects
- Better way to structure game classes (Game class as coordinator)

## Testing Results
All 3 automated tests pass. Manually tested and the gameplay feels good. Power-ups work, enemies move, collisions detected properly. The speed boost makes you zoom, ghost mode is fun for shortcuts, insta-kill feels powerful.

## Design Decisions
1. Made power-ups part of Player class instead of separate class - simpler
2. Enemies move every 3 ticks to not be too fast
3. Power-ups spawn when coins collected (25% chance) to keep them appearing
4. Simple arrow/WASD controls that work everywhere

## Questions for Next Checkpoint
1. Should I add different enemy types with behaviors?
2. Add sound effects maybe? (beep boop console sounds)
3. Level progression - harder mazes after winning?
4. High score system that saves between games?

## Time Spent
- Planning: 30 mins
- Coding: 3.5 hours
- Testing/debugging: 1 hour
- Documentation: 30 mins
- **Total: ~5.5 hours**