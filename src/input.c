#include "input.h"
#include "gamestate.h"
#include "math.h"
#include "raylib.h"
#include "stdio.h"
#define DEVICE_KEYBOARD -1
/***
 * TODO: inputManager should be reworked entirely.
 * not sure if it makes sense at all.
 *
 */

float max(float a, float b);
bool isInitialized = FALSE;
InputDevice devices[] = { DEVICE_KEYBOARD, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

InputManager* getManager()
{
    return &getManager;
}

InputDevice* getInputDevices(InputManager* manager) { return devices; }

Bool isJumpPressed(InputManager* manager, InputDevice device)
{

    if (device == DEVICE_KEYBOARD) {

        return IsKeyPressed(KEY_Z);
    }
    return IsGamepadButtonPressed(device, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
}

Bool isHitPressed(InputManager* manager, InputDevice device)
{
    if (device == DEVICE_KEYBOARD) {
        return IsKeyPressed(KEY_X);
    }
    return IsGamepadButtonPressed(device, GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
}

Vector2 getMovement(InputManager* manager, InputDevice device)
{
    if (device == DEVICE_KEYBOARD) {
        float axisY = IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP);
        float axisX = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
        return (Vector2) {
            axisX,
            axisY
        };
    }
    return (Vector2) {
        GetGamepadAxisMovement(device, GAMEPAD_AXIS_LEFT_X),
        GetGamepadAxisMovement(device, GAMEPAD_AXIS_LEFT_Y),
    };
}

Vector3 getAim(InputManager* manager, InputDevice device)
{
    if (device == DEVICE_KEYBOARD) {
        return (Vector3) {
            0,
            1,
            0
        };
    }
    float x = GetGamepadAxisMovement(device, GAMEPAD_AXIS_RIGHT_X);
    float z = GetGamepadAxisMovement(device, GAMEPAD_AXIS_RIGHT_Y);
    float y = sqrt(max(0,
        1 - x * x - z * z));
    return (Vector3) {
        x,
        y,
        z
    };
}

float max(float x, float y)
{
    return x > y ? x : y;
}