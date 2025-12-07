# Final Reflection - PacAvanture

## Section 1: Project Summary
PacAvanture is a maze game where you play as a character who collects coins, avoids enemies, and uses power-ups across 3 levels. It's like Pac-Man but with extra abilities and saving/loading.

What features did I implement:
1. Basic game - map, player movement, coins, walls
2. Enemies that move around and chase you
3. Power-ups that give you special abilities (speed, kill enemies, ghost mode)
4. 3 different levels that get harder
5. Save and load your game progress
6. Menu system with instructions
7. Score tracking and lives system

What does it do well:
- Actually works start to finish - you can play and win
- Looks clean with ASCII graphics
- Saves your game so you can continue later
- Power-ups make it more fun than just collecting coins
- Levels actually get harder like a real game

## Section 2: What Remains

From my original plan, I didn't finish:
- Different types of enemies (wanted fast ones and smart ones)
- High score table that saves between games
- Sound effects (beeps and stuff)
- More than 3 levels
- Power-ups combining together

Bugs/issues that are still there:
- Sometimes the input is laggy (keypress doesn't register right away)
- Enemies sometimes get stuck in corners
- The save file doesn't save everything (like which power-ups are active)
- No way to see how many enemies are left without counting

To make this project "complete" I'd need:
1. Fix the input lag (maybe 2-3 hours)
2. Add at least 2 enemy types with different AI (3-4 hours)
3. Make high scores save to a file (2 hours)
4. Store everything in save files, not just basics (1-2 hours)
5. Add 2 more levels (2 hours)

## Section 3: Time Estimate

Here's how much time I think each remaining thing would take:

**Must-have (need to fix):**
- Fix input lag: 2-3 hours  
  Would need to rewrite how keyboard input works to make it smoother

**Should-have (would make it better):**
- Different enemy types: 3-4 hccours
  Would need to make different enemy classes - maybe a fast one and a smart one
- Better save system: 1-2 hours
  Would need to save more stuff like power-up timers and exact enemy positions

**Nice-to-have (extra features):**
- High score system: 2-3 hours
  Would need a file to save top scores with player names
- 2 more levels: 2 hours
  Would need to design and test new maze layouts
- Sound effects: 1 hour
  Just simple beeping sounds when you collect coins or get hit

## Section 4: What I Learned

C++ concepts I learned or got better at:
- **Classes and objects**: Making Player, Enemy, Map, Game classes that work together
- **File I/O**: Reading and writing to files for save games
- **Vectors and arrays**: Using std::vector for enemies and power-ups
- **Cross-platform stuff**: Making code work on Windows AND Mac/Linux
- **Game loops**: The whole update → draw → input cycle
- **Const correctness**: When to use const and why it matters
- **CMake and testing**: Setting up projects properly with tests

Hardest part of this project:
The cross-platform input handling was SO annoying. Windows uses _getch() and arrow keys are special codes, but Mac/Linux uses termios and it's totally different. I spent hours just trying to get WASD to work everywhere.

What would I do differently if starting over:
1. Start with simpler input (just letters, not arrow keys)
2. Make an InputHandler class from the beginning instead of adding it late
3. Test on both Windows and Mac from day 1
4. Write more comments as I go (not at the end)
5. Make smaller commits instead of big ones

What I'm most proud of:
The save/load system that actually works! It saves to different places on Windows (Documents folder) vs Mac/Linux (home folder) and you can quit the game, come back later, and pick up right where you left off. That feels like a real feature.

How my understanding changed:
I used to think games were super complicated magic. Now I see they're just loops that update positions, check collisions, and draw things. The data structures (vectors for enemies, strings for maps) make way more sense now.

## Section 5: Time Log

- **Planning and design**: 8 hours
    - Figuring out what features to build: 3 hours
    - Drawing class diagrams: 2 hours
    - Planning each checkpoint: 2 hours
    - Setting up GitHub and CMake: 1 hour

- **Implementation**: 32 hours
    - Checkpoint 1 (basic game): 7 hours - Map, Player, movement
    - Checkpoint 2 (enemies and power-ups): 10 hours - This took forever to debug
    - Checkpoint 3 (levels and save/load): 9 hours - File I/O was tricky
    - Checkpoint 4 (polish and fixes): 6 hours - Making it actually fun

- **Testing and debugging**: 12 hours
    - Writing tests: 4 hours - Learned CTest which was cool
    - Playing the game to find bugs: 5 hours - Actually fun but also work
    - Fixing random crashes: 3 hours - So many segfaults early on

- **Documentation**: 8 hours
    - Writing README and comments: 4 hours
    - These reflection documents: 3 hours
    - Preparing submissions: 1 hour

- **Total**: 60 hours (way more than I expected but I learned a lot)

## Final Thoughts
This project went from "I have no idea what I'm doing" to "hey this actually works like a real game!" The progression through checkpoints helped a lot - doing one feature at a time made it manageable.

The game isn't perfect (enemies are dumb, graphics are simple) but it's COMPLETE. You can start at the menu, play through 3 levels, win or lose, and save your progress. That's more than I thought I could make when I started.

Biggest surprise: How satisfying it is to play your own game. Even though I made it, collecting all the coins and beating a level feels good. Also CMake and testing turned out to be really useful, not just busywork.

If I had 2 more weeks: I'd add different enemy types and a high score table. But as it is, PacAvanture is a real, playable game that I'm actually kind of proud of.