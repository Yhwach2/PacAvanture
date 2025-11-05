#ifndef PACAVANTURE_INPUTHANDLER_H
#define PACAVANTURE_INPUTHANDLER_H


#include <utility>

/**
 * InputHandler reads keyboard input and translates to movement deltas.
 * Implementation may use platform-specific code (conio.h / termios).
 */
class InputHandler {
public:
    InputHandler();

    // Blocks/waits for a keypress and returns movement delta (dx,dy).
    // Arrow keys map to (0,-1),(0,1),(-1,0),(1,0) or (0,0) for none.
    std::pair<int,int> getMovementDelta() const;

    // Non-blocking optional variant can be added later
};

#endif //PACAVANTURE_INPUTHANDLER_H