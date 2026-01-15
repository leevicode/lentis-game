#ifndef INPUTS
#define INPUTS
#include "player.h"
#include "raylib.h"
#include "types.h"

typedef int InputDevice;

typedef struct {
    Player* player;
    InputDevice device;
} Controller;

typedef void InputManager;

InputManager* getManager();
InputDevice* getInputDevices(InputManager* manager);
int getNumDevices(InputManager* manager);
Bool isJumpPressed(InputManager* manager, InputDevice device);
Bool isHitPressed(InputManager* manager, InputDevice device);
Vector2 getMovement(InputManager* manager, InputDevice device);
Vector3 getAim(InputManager* manager, InputDevice device);

#endif
