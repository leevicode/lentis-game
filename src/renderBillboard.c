#include "ball.h"
#include "gamestate.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"

void drawState(MainState* state, Camera* camera, Texture2D playerImage, Texture2D ballImage)
{
    camera->target = Vector3Scale(state->state.ball.position, 0.4);
    DrawPlane(Vector3Zero(), (Vector2) { 20, 10 }, BEIGE);
    for (int i = 0; i < NUM_CONTROLLERS; i++) {
        Player* player = state->controllers[i].player;
        DrawBillboard(*camera, playerImage, playerMidpoint(player), PLAYER_HEIGHT, GREEN);
    }
    DrawBillboard(*camera, ballImage, state->state.ball.position, 1, ORANGE);
}
