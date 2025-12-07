# Checkpoint 3 Reflection

## What I Implemented
Added a save/load system that writes to a simple text file (pacsave.txt) with your current level, score, and lives. Also added 3 levels that get harder each time - more enemies, trickier mazes. You start with 3 lives for the whole game.

## How This Integrates with Features 1 and 2
This builds on the enemy and power-up system from last time. Now those enemies are spread across 3 levels instead of just one map. The save system lets you stop playing and come back later, which makes the levels actually matter. Power-ups from checkpoint 2 still work in all levels.

## Challenges I Faced
1. The file saving part was confusing at first. Had to figure out how to write and read from files in C++.
2. GitHub gave me problems again. Thought my commits weren't going through because of token/password issues. Because of that I thought all my files are being sent to github, but in reality only few files were sent and all the files from
include and src files were not gone through and were empty . But I had backout logs so i got toload them all in and re push them again . It turned out that github stopped using username and password eventhough it requires it . But now since i connected it through token now I feel more comfortable with git . 
3. Balancing the levels - making level 3 actually hard but not impossible.
4. The save system is basic. It doesn't save everything (like power-up timers or exact enemy positions) but it saves enough to continue playing.

## What I Learned
- Basic file handling in C++ (fstream stuff)
- How to save game state by just writing numbers to a text file
- That I should make things simpler first instead of trying to make them perfect
- GitHub token authentication is different from password authentication (learned this the hard way)

## Testing Results
- Save/load works: Can save game, quit, load, continue
- Levels work: Beat level 1, go to level 2, etc.
- Lives system works: Lose a life when you die
- Integration mostly works: Old features still work with new ones

## Overall Project Completion Progress
Original plan had 8 features
Now completed: 6 features (75% done)

Done so far:
1. Basic game (checkpoint 1)
2. Enemies and power-ups (checkpoint 2)
3. Levels and save system (checkpoint 3)

Still to do:
1. High score system
2. Different enemy types (maybe)

Am I on track? Yeah, I think so. Game is playable from start to finish now.

Biggest problem left: The high score system needs to save between games too (more file stuff).

Need to adjust anything? Maybe skip different enemy types if I run out of time. High scores are more important.

## Time Spent
- Planning: 30 min
- Coding save/load: 2 hours
- Coding levels: 1.5 hours
- Debugging (including GitHub issues): 1.5 hours
- Documentation: 30 min
- Total: About 6 hours

## GitHub Issues Note
Had authentication problems again. Thought my commits weren't pushing because of token issues. 