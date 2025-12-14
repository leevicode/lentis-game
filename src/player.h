
#ifndef PLAYER
#define PLAYER
#include "types.h"
#define WALK_SPEED 180
#define AIR_SPEED 60
#define DRAG 0.001
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

void updatePlayer(Player* player, Vector2 input, float deltaTime);
void jump(Player* player);
void drawPlayer(Player* player);

#endif