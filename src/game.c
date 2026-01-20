#include "ball.h"
#include "gamestate.h"
#include "input.h"
#include "player.h"
#include "raymath.h"
#include "types.h"

void updateState(MainState* state, float deltaTime);
Bool canPlayerTouch(Player* player, Ball* ball);
void throwBall(Ball* ball);
void pickupBall(Player* player, Ball* ball);
Team* getPlayerTeam(GameState* state, Player* player);

void updateState(MainState* state, float deltaTime)
{
    InputManager* manager = getManager();
    Ball* ball = &state->state.ball;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        InputDevice device = state->controllers[i].device;
        Player* player = state->controllers[i].player;
        if (!player) {
            continue;
        }
        if (isJumpPressed(manager, device)) {
            jump(player);
        }
        updatePlayer(player, getMovement(manager, device), deltaTime);
        if (isHitPressed(manager, device) && canPlayerTouch(player, ball)) {
            interactBall(
                player,
                ball,
                getAim(manager, device));
        }
    }
    updateBall(ball, deltaTime);
}

Bool canPlayerTouch(Player* player, Ball* ball)
{
    if (player == ball->lastHit && ball->state == IN_AIR && false) { // TODO: remove && false to disallow second touch
        return FALSE;
    }
    Vector3 playerPosition = playerMidpoint(player);
    if (Vector3DistanceSqr(playerPosition, ball->position) < 4) { // TODO: magic number
        return TRUE;
    }
    return FALSE;
}