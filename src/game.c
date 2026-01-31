#include "ball.h"
#include "gamestate.h"
#include "input.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include "types.h"

void updateState(GameState* state, float deltaTime);
Bool canPlayerTouch(Player* player, Ball* ball);
void throwBall(Ball* ball);
void pickupBall(Player* player, Ball* ball);

void updateState(GameState* state, float deltaTime)
{
    if (state->freezeFrames > 0) {
        state->freezeFrames -= deltaTime;
        if (state->freezeFrames < 0) {
            state->freezeFrames = 0;
        }
        return;
    }
    InputManager* manager = getManager();
    Ball* ball = &state->ball;
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
            if (interactBall(
                    player,
                    ball,
                    getAim(manager, device))) {
                state->freezeFrames = FREEZE_FRAMES;
            }
        }
    }
    Vector3 previousPosition = ball->position;
    updateBall(ball, deltaTime);
    Ray ballTrajectory = (Ray) {
        previousPosition,
        Vector3Subtract(ball->position, previousPosition)
    };
    RayCollision collision = GetRayCollisionBox(ballTrajectory, state->net);
    if (collision.hit && collision.distance < 1) { // check if the ray collision is close enough that the ball actually also hits
        ball->motion = Vector3Add(
            ball->motion,
            Vector3Scale(
                collision.normal,
                Vector3Length(ball->motion) / 2.0));
        ball->position = previousPosition;
    }
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