# Implementation Plan for Pac advanture

## Overview
Console maze game: move, collect coins, avoid enemies, reach gate.

---

## Feature 1: Player movement (arrow keys)
**Trigger:** Player presses an arrow key during the game loop.
**Input:** Arrow key sequence read by InputHandler.
**Flow:**
1. Game::update() calls input.getMovementDelta().
2. If delta non-zero, Game asks Player::move(dx,dy,mapWidth,mapHeight).
3. Player::move checks Map::isWall() to prevent walking into walls.
4. If moved, Game calls handleCollisions() to resolve coin/enemy/gate interactions.
   **Data modified:** Player position updated.
   **Completion:** Player is in new tile, render will show new position.

---

## Feature 2: Coin collection
**Trigger:** Player moves onto a tile containing a coin.
**Input:** Player position after move.
**Flow:**
1. Game::handleCollisions checks Map::hasCoin(playerX, playerY).
2. If true, call Map::removeCoin() and Player::collectCoin().
3. Increment Game::score and decrement remaining coins.
4. If remainingCoins == 0, call Map::openGate().
   **Data modified:** Map coin removed, Player score updated, Game remainingCoins updated.
   **Completion:** Coin disappears, score updated in UI.

---

## Feature 3: Enemy patrols
**Trigger:** Each game tick (Game::update).
**Input:** Enemy objects with patrol patterns.
**Flow:**
1. For each Enemy, call Enemy::update() to advance patternIndex and move.
2. After enemy moves, Game checks collision: if enemy position equals player position → set gameOver.
   **Data modified:** Enemy positions updated.
   **Completion:** If collision, Game sets gameOver and stops loop.

---

## Feature 4: Gate / victory
**Trigger:** All coins collected; player reaches gate position.
**Flow:**
1. When remainingCoins == 0 Map::openGate() sets the gate to open state.
2. If player moves to gate tile and gateOpen == true, set victory = true and stop running.
   **Completion:** Victory message printed.

---

## Feature 5: Rendering
**Trigger:** Each tick after update.
**Flow:**
1. Game::render calls Map::render(playerX, playerY, enemyPositions, gateOpen).
2. Map::render returns vector<string> rows; Game prints rows to console.
   **Data displayed:** Walls '#', coins 'o', player '@', enemies 'E', closed gate 'G', open gate 'g'.

---

## Tick / Loop
- Game::run() loop:
    - read input
    - update player
    - update enemies
    - handle collisions
    - render
    - check win/loss
