#ifndef STATE
#define STATE

#include "ball.h"
#include "input.h"
#include "player.h"
#include "raylib.h"
#include "types.h"
#define TEAM_SIZE 2
#define NUM_TEAMS 2

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
    Controller controllers[TEAM_SIZE * NUM_TEAMS];
} MainState;

void updateState(GameState* state);
Bool canPlayerHit(Player* player, Ball* ball);
void hitBall(Player* playerWhoHit, Ball* ball);
Team* getPlayerTeam(Player* player);

#endif
