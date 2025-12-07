# Checkpoint 3 Plan

## Feature Name
Save and Load System with Multiple Levels

## Description
I'm adding the ability to save your game progress and load it back later. Also adding 3 different levels that get harder as you go. You start with 3 lives and if you lose them all, game over.

## Why This Feature?
The first two features gave us a playable game with enemies and power-ups. Now it needs actual progression (levels to beat) and persistence (save your progress). Right now you can only play one session then quit, this lets you continue later.

## Classes Involved
- Game class (where most changes happen)
- Map class (needs different layouts for each level)
- Player class (already has everything needed from last checkpoint)

## Expected User Workflow
1. Start game, see menu
2. Choose "New Game" or "Load Game"
3. Play level 1 (collect coins, avoid enemies)
4. If you die, lose one of your 3 lives
5. Beat level 1, automatically go to level 2 (more enemies)
6. Press 'S' key anytime to save your progress
7. Beat level 2, go to level 3 (even harder)
8. Beat level 3 = win the game
9. Can quit anytime, load later to continue

## Estimated Time
Probably 4-5 hours. The file saving part might take some time to figure out. 