#ifndef BALL
#define BALL
#include "player.h"
#include "types.h"

typedef struct {
    Position position;
    Motion motion;
    Bool inAir;
    Player* lastHit;
} Ball;

void updateBall(Ball* m_ball, float deltaTime);
void drawBall(Ball* ball);

#endif
