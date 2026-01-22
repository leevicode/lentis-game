#ifndef INPUTS
#define INPUTS
#include "raylib.h"
#include "types.h"

InputManager* getManager();
InputDevice* getInputDevices(InputManager* manager);
Bool isJumpPressed(InputManager* manager, InputDevice device);
Bool isHitPressed(InputManager* manager, InputDevice device);
Vector2 getMovement(InputManager* manager, InputDevice device);
Vector3 getAim(InputManager* manager, InputDevice device);

#endif
