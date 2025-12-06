# Checkpoint 2 Test Results

## Feature: Power-up System with Enemy Interactions

### Test Setup
- Test file: `tests/test_powerups.cpp`
- Build command: `mkdir build && cd build && cmake .. && make`
- Run tests: `ctest --verbose`

### Test 1: Power-up Collection
- **What it tests:** Player can collect different power-up types
- **Expected result:** `hasPowerUp()` returns true for collected type
- **Result:** passed

### Test 2: Enemy Kill Mechanics
- **What it tests:** Enemy can be killed and `isAlive()` updates
- **Expected result:** Enemy alive state changes from true to false
- **Result:**  passed

### Test 3: Power-up Timers
- **What it tests:** Power-ups have active timers when collected
- **Expected result:** Timer value > 0 immediately after collection
- **Result:**  passed

### CTest Output

