#include "player.h"
#include "ball.h"
#include "gamestate.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

void updatePlayer(Player* player, Vector2 input, float deltaTime)
{
    float speed = (player->position.y > 0) ? AIR_SPEED : WALK_SPEED;
    player->motion = Vector3Add(
        player->motion,
        (Vector3) {
            input.x * deltaTime * speed,
            0,
            input.y * deltaTime * speed });
    player->motion.y -= deltaTime * GRAVITY;

    player->motion.x *= DRAG * deltaTime;
    player->motion.z *= DRAG * deltaTime;
    player->position = Vector3Add(player->position, Vector3Scale(player->motion, deltaTime));
    if (player->position.y < 0) {
        player->position.y = 0;
        player->motion.y = 0;
        player->state = E_STANDING;
    }
}

void jump(Player* player)
{
    if (player->state == E_IN_AIR || player->position.y > 0) {
        return;
    }
    player->state = E_IN_AIR;
    player->motion.y = 7;
}

Vector3 playerMidpoint(Player* player)
{
    return Vector3Add(player->position, (Vector3) { 0, PLAYER_HEIGHT / 2.0, 0 });
}