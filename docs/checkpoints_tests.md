# Checkpoint 3 Test Results

## Feature Being Tested
Save/load system and level progression

## Test 1: Can We Create a Save File
What it tests: Does the save function actually create a file
How to test: Run the game, press 'S' to save, look for pacsave.txt file
Expected result: File gets created with game data inside
Actual result: Works, file appears with level number, score, and lives

## Test 2: Can We Load a Saved Game
What it tests: Loading function works correctly
How to test: Save a game, quit, restart, choose "Load Game" from menu
Expected result: Game continues from where we saved
Actual result: Works for level, score, and lives. Power-up timers don't save though

## Test 3: Level Progression Works
What it tests: Do levels actually advance properly
How to test: Beat level 1, see if level 2 starts
Expected result: Level 2 starts with more enemies
Actual result: Works, enemy count increases each level

## Test 4: Lives System Functions
What it tests: Do we actually lose lives when we die
How to test: Let an enemy kill you, check lives counter
Expected result: Lives go from 3 to 2 to 1 to 0 (game over)
Actual result: Works correctly

## Issues Found During Testing
1. Save file doesn't save power-up timers, they reset when you load
2. No error message if the save file is missing or corrupted
3. Level 3 might be too difficult but that's intentional

## Overall Test Summary
All the main functions work. Save and load works, levels work, lives system works. Could be improved but meets what we need for this checkpoint.