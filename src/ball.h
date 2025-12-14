#ifndef BALL
#define BALL
#include "player.h"
#include "types.h"

typedef enum {
    IN_AIR,
    ON_GROUND,
    HELD
} BallState;

typedef struct {
    Position position;
    Motion motion;
    BallState state;
    Player* lastHit;
} Ball;

void updateBall(Ball* ball, float deltaTime);
void drawBall(Ball* ball);

#endif
