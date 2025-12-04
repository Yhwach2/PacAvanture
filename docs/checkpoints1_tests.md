# Checkpoint 1 Tests - PacAvanture (Map & Player feature)

## Tests included
1. Map initialization: verifies border walls exist.
2. Place-player and collect: places player, optionally collects coin under player.
3. Gate unlock: clears coins and checks gate unlocks.

## tccho run
mkdir -p build
cd build
cmake ..
cmake --build .
ctest --verbose
