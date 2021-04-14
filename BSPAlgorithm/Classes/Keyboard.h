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
    const uint8_t *state = NULL;
    SDL_Scancode code = SDL_SCANCODE_UNKNOWN;
public:
    Key(const uint8_t *state): state(state) { }
    Key(SDL_Scancode code): code(code) { }
    friend bool operator==(const Key& key, const SDL_Scancode code);
};

inline bool operator==(const Key& key, const SDL_Scancode code) {
    if (key.state) {
        return key.state[code];
    } else if (key.code != SDL_SCANCODE_UNKNOWN) {
        return key.code == code;
    }
    return false;
}

// MARK: KeyListener
class KeyListener {
public:
    virtual bool onKeyPress(const Key& key) { return false; };
    virtual bool onKeyRelease(const Key& key) { return false; };
};
#endif /* Key_h */
