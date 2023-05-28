#include "InputManager.h"
#include "Camera.h"
#include "SDL.h"

InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

InputManager::InputManager() : updateCounter(0), quitRequested(false), mouseX(0), mouseY(0) {
    for (int i = 0; i < 6; i++) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }
}

InputManager::~InputManager() {}


// process the events
void InputManager::Update() {
    updateCounter++;
    
    SDL_Event event;
    SDL_GetMouseState(&mouseX, &mouseY);

    quitRequested = false;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quitRequested = true;
            break;
        }

        if (!event.key.repeat) {    // if not a repeated event
            switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
                break;
            case SDL_MOUSEBUTTONUP:
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
                break;
            case SDL_KEYDOWN:
                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;
            case SDL_KEYUP:
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;
            default:
                break;
            }
        }

    }

}

// returns true if the key is being pressed in the current frame
bool InputManager::KeyPress(int key) {
    return keyState[key] && (keyUpdate[key] == updateCounter);
}

// returns true if the key has just been released (in this current frame)
bool InputManager::KeyRelease(int key) {
    return !keyState[key] && (keyUpdate[key] == updateCounter);
}

// returns true if the mouse button is being pressed in the current frame
bool InputManager::MousePress(int key) {
    return mouseState[key] && (mouseUpdate[key] == updateCounter);
}

// returns true if the mouse button has just been released (in this current frame)
bool InputManager::MouseRelease(int key) {
    return !mouseState[key] && (mouseUpdate[key] == updateCounter);
}

// returns true if the last state of the key was down
bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

// returns true if the last state of the mouse button was down
bool InputManager::IsMouseDown(int key) {
    return mouseState[key];
}


// returns the current X position of the mouse
int InputManager::GetMouseX() {
    return mouseX + Camera::pos.x;
}

// returns the current Y position of the mouse
int InputManager::GetMouseY() {
    return mouseY + Camera::pos.y;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}

