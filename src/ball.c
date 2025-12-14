#include "ball.h"
#include "gamestate.h"
#include "player.h"
#include "raymath.h"
#include <stdio.h>

void updateGroundedBall(Ball* ball, float deltaTime);
void updateHeldBall(Ball* ball, float deltaTime);
void updateAirBall(Ball* ball, float deltaTime);

void updateBall(Ball* ball, float deltaTime)
{
    switch (ball->state) {
    case ON_GROUND:
        updateGroundedBall(ball, deltaTime);
        break;
    case HELD:
        updateHeldBall(ball, deltaTime);
        break;
    case IN_AIR:
        updateAirBall(ball, deltaTime);
        break;
    }
}

void updateGroundedBall(Ball* ball, float deltaTime)
{
    return;
}

void updateHeldBall(Ball* ball, float deltaTime)
{
    ball->position = playerMidpoint(ball->lastHit);
}

void updateAirBall(Ball* ball, float deltaTime)
{
    ball->motion.y -= deltaTime * GRAVITY;
    ball->position = Vector3Add(
        ball->position,
        Vector3Scale(ball->motion, deltaTime));
    if (ball->position.y < 0) {
        ball->state = ON_GROUND;
        ball->motion = Vector3Zero();
        ball->position.y = 0;
    }
}

void pickupBall(Player* player, Ball* ball)
{
    ball->state = HELD;
    ball->lastHit = player;
}

void throwBall(Ball* ball)
{
    ball->state = IN_AIR;
    ball->motion = Vector3Add(ball->lastHit->motion, (Vector3) { 0, 3, 0 }); // TODO: magic number
    ball->lastHit = NULL;
}

void hitBall(Player* playerWhoHit, Ball* ball)
{
    ball->motion = Vector3Subtract(
        ball->position,
        playerMidpoint(playerWhoHit));
    ball->motion = Vector3Scale(ball->motion, 5); // TODO: magic numbers
    ball->motion.y += 4; // TODO <:^}
    ball->state = IN_AIR;
    ball->lastHit = playerWhoHit;
}

void interactBall(Player* player, Ball* ball)
{
    switch (ball->state) {
    case ON_GROUND:
        pickupBall(player, ball);
        break;
    case IN_AIR:
        hitBall(player, ball);
        break;
    case HELD:
        throwBall(ball);
        break;
    }
}