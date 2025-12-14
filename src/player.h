
#ifndef PLAYER
#define PLAYER
#include "raylib.h"
#include "types.h"
#define WALK_SPEED 100
#define AIR_SPEED 66
#define DRAG 50
#define PLAYER_HEIGHT 2
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
Vector3 playerMidpoint(Player* player);
#endif