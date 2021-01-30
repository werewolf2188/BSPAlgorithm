//
//  Key.h
//  BSPAlgorithm
//
//  Created by Enrique on 1/27/21.
//

#ifndef Key_h
#define Key_h
#include <stdint.h>
#include <SDL2/SDL_scancode.h>
// MARK: Keys

class Key {
private:
    const uint8_t *state;
public:
    Key(const uint8_t *state): state(state) { }
    friend bool operator==(const Key& key, const SDL_Scancode code);
};

inline bool operator==(const Key& key, const SDL_Scancode code) {
    return key.state[code];
}

// MARK: KeyListener
class KeyListener {
public:
    virtual bool onKeyPress(const Key& key) = 0;
};
#endif /* Key_h */
