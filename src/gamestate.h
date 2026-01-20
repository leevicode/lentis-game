#ifndef STATE
#define STATE

#include "ball.h"
#include "input.h"
#include "player.h"
#include "raylib.h"
#include "types.h"
#define TEAM_SIZE 2
#define NUM_TEAMS 2
#define NUM_CONTROLLERS 12
#define MAX_PLAYERS 12
#define GRAVITY 9.807
typedef struct
{
    // Player players[TEAM_SIZE];
    unsigned points;
    Color color;
} Team;

typedef struct
{
    Player players[MAX_PLAYERS];
    Team teams[NUM_TEAMS];
    Ball ball;
    // TODO: net poles
    // TODO: game boundaries
} GameState;

typedef struct
{
    GameState state;
    InputManager* manager;
    Controller controllers[MAX_PLAYERS];
} MainState;

void updateState(MainState* state, float deltaTime);
Bool canPlayerTouch(Player* player, Ball* ball);
void interactBall(Player* player, Ball* ball, Vector3 dir);
void hitBall(Player* playerWhoHit, Ball* ball, Vector3 dir);
void throwBall(Ball* ball);
void pickupBall(Player* player, Ball* ball);
Team* getPlayerTeam(GameState* state, Player* player);
void drawState(MainState* state, Camera* camera, float deltaTime);
void loadResources();
#endif
