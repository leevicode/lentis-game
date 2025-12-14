#ifndef STATE
#define STATE

#include "ball.h"
#include "input.h"
#include "player.h"
#include "raylib.h"
#include "types.h"
#define TEAM_SIZE 2
#define NUM_TEAMS 2
#define NUM_CONTROLLERS 1 // TEAM_SIZE* NUM_TEAMS
#define GRAVITY 9.807
typedef struct
{
    Player players[TEAM_SIZE];
    unsigned points;
} Team;

typedef struct
{
    Team teams[NUM_TEAMS];
    Ball ball;
    // TODO: net poles
    // TODO: game boundaries
} GameState;

typedef struct
{
    GameState state;
    Controller controllers[NUM_CONTROLLERS];
    InputManager* manager;
} MainState;

void updateState(MainState* state, float deltaTime);
Bool canPlayerTouch(Player* player, Ball* ball);
void interactBall(Player* player, Ball* ball);
void hitBall(Player* playerWhoHit, Ball* ball);
void throwBall(Ball* ball);
void pickupBall(Player* player, Ball* ball);
Team* getPlayerTeam(GameState* state, Player* player);

#endif
