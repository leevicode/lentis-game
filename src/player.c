#include "player.h"
#include "gamestate.h"
#include "raylib.h"
#include "raymath.h"

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
    Vector3 horizontalMotion = Vector3Multiply(player->motion, (Vector3) { 1, 0, 1 });
    Vector3 drag = Vector3Scale(horizontalMotion, -1.0 * DRAG * deltaTime);
    player->motion = Vector3Add(player->motion, drag);

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