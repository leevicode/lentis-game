#ifndef INPUTS
#define INPUTS
#include "player.h"
#include "types.h"

typedef Bool (*IsJumpPressed)();
typedef Bool (*IsHitPressed)();
typedef Vector2 (*GetMovement)();
typedef struct {
  IsJumpPressed *isJumpPressed;
  IsHitPressed *isHitPressed;
  GetMovement *getMovement;
} InputDevice;

typedef struct {
  Player *player;
  InputDevice device;
} Controller;

typedef void InputManager;

InputManager *getManager();
InputDevice *getInputDevices(InputManager *manager);
int getNumDevices(InputManager *manager);

#endif
