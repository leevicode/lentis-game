
#ifndef PLAYER
#define PLAYER
#include "types.h"
#define WALK_SPEED 180
#define AIR_SPEED 60

typedef enum {
    E_STANDING,
    E_WALKING,
    E_IN_AIR,
} PlayerState;

typedef struct {
    Position position;
    Motion motion;
    PlayerState state;
} Player;

void updatePlayer(Player* m_player, float deltaTime);
void drawPlayer(Player* player);

#endif