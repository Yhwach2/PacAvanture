## Checkpoint 3: Save/Load System and Levels

### New Features Added
- 3 levels with increasing difficulty
- Save system (saves to pacsave.txt)
- Load system to continue games
- 3 lives total for the whole game

### How to Use
1. Save during game: Press 'S' key
2. Load saved game: Choose option 2 from main menu
3. File location: pacsave.txt in game folder

### Project Progress
Checkpoint 1: Done
Checkpoint 2: Done  
Checkpoint 3: Done
Checkpoint 4: Remaining

Overall: 75% complete (6/8 features done)

### Current Issues
- Save file doesn't save power-up timers
- No error if save file is missing
- Level 3 might be too hard
- Ghost mode looks weird

### Running Tests
```bash
cd build
ctest --verbose