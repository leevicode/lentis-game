#ifndef TYPES
#define TYPES
#include "raylib.h"
#define Bool int
#define TRUE 1
#define FALSE 0

// player defines
#define WALK_SPEED 80
#define AIR_SPEED 40
#define DRAG 5
#define PLAYER_HEIGHT 2

// game state
#define TEAM_SIZE 2
#define NUM_TEAMS 2
#define NUM_CONTROLLERS 12
#define MAX_PLAYERS 12
#define GRAVITY 9.807

typedef Vector3 Position;
typedef Vector3 Motion;

typedef struct
{
    unsigned points;
    Color color;
} Team;

typedef enum {
    E_STANDING,
    E_WALKING,
    E_IN_AIR,
} PlayerState;

typedef struct {
    Position position;
    Motion motion;
    Team* team;
    PlayerState state;
} Player;

typedef enum {
    IN_AIR,
    ON_GROUND,
    HELD
} BallState;

typedef struct {
    Position position;
    Motion motion;
    BallState state;
    Player* lastHit;
} Ball;

typedef int InputDevice;
typedef void InputManager;

typedef struct {
    Player* player;
    InputDevice device;
} Controller;

typedef struct
{
    Team teams[NUM_TEAMS];
    Ball ball;
    InputManager* manager;
    Controller controllers[MAX_PLAYERS];
} GameState;

#endif
