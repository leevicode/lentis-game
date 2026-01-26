#ifndef STATE
#define STATE
#include "input.h"
#include "player.h"
#include "raylib.h"
#include "types.h"

#define FREEZE_FRAMES 0.1f
void updateState(GameState* state, float deltaTime);
Bool canPlayerTouch(Player* player, Ball* ball);
Bool interactBall(Player* player, Ball* ball, Vector3 dir);
void hitBall(Player* playerWhoHit, Ball* ball, Vector3 dir);
void throwBall(Ball* ball);
void pickupBall(Player* player, Ball* ball);
void drawState(GameState* state, Camera* camera, float deltaTime);
void loadResources();
#endif
