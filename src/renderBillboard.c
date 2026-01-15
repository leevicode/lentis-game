#include "ball.h"
#include "gamestate.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"

Texture2D playerTexture;
Texture2D ballTexture;
Model backgroundModel;
void loadResources()
{
    playerTexture = LoadTexture("resource/Standing.png");
    ballTexture = LoadTexture("resource/Ball.png");
    backgroundModel = LoadModel("resource/Untitled.glb");
}

void drawState(MainState* state, Camera* camera)
{
    camera->target = Vector3Scale(state->state.ball.position, 0.4);
    DrawModel(backgroundModel, Vector3Zero(), 10, WHITE);
    DrawPlane(Vector3Zero(), (Vector2) { 20, 10 }, BEIGE);
    for (int i = 0; i < NUM_CONTROLLERS; i++) {
        Player* player = state->controllers[i].player;
        DrawBillboard(*camera, playerTexture, playerMidpoint(player), PLAYER_HEIGHT, GREEN);
        DrawSphere(Vector3Multiply(player->position, (Vector3) { 1, 0, 1 }), 0.4, BLACK);
    }
    DrawSphere(Vector3Multiply(state->state.ball.position, (Vector3) { 1, 0, 1 }), 0.4, BLACK);
    DrawBillboard(*camera, ballTexture, state->state.ball.position, 1, WHITE);
}
