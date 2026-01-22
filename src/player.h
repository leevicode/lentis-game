#ifndef PLAYER
#define PLAYER
#include "raylib.h"
#include "types.h"

void updatePlayer(Player* player, Vector2 input, float deltaTime);
void jump(Player* player);
void drawPlayer(Player* player);
Vector3 playerMidpoint(Player* player);
#endif