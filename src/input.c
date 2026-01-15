#include "input.h"
#include "math.h"
#include "raylib.h"
#define NUM_INPUTS 5

#define DEVICE_KEYBOARD -1

float max(float a, float b);
int num_devices = 1;
bool isInitialized = FALSE;
InputDevice devices[NUM_INPUTS];
Bool keypad1_isjumpPressed()
{
    return IsGamepadButtonPressed(1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
}

InputManager* getManager()
{
    if (isInitialized) {
        return &getManager;
    }
    devices[0] = DEVICE_KEYBOARD;
    for (int i = 0; i < NUM_INPUTS; i++) {
        if (IsGamepadAvailable(i)) {
            devices[num_devices] = i;
            num_devices++;
        }
    }

    return &getManager;
}

InputDevice* getInputDevices(InputManager* manager) { return devices; }

int getNumDevices(InputManager* manager) { return num_devices; }

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