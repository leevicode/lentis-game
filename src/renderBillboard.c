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

void drawState(MainState* state, Camera* camera, float deltaTime)
{
    Vector3 ballMidPoint = Vector3Multiply(state->state.ball.position, (Vector3) { 1, 0.5, 1 });
    camera->target = Vector3Add(
        Vector3Scale(camera->target, 1 - (2 * deltaTime)),
        Vector3Scale(ballMidPoint, 2 * deltaTime));
    DrawModel(backgroundModel, Vector3Zero(), 10, WHITE);
    DrawPlane(Vector3Zero(), (Vector2) { 20, 10 }, BEIGE);
    for (int i = 0; i < MAX_PLAYERS; i++) {
        Player* player = state->controllers[i].player;
        if (!player) {
            continue;
        }
        DrawBillboard(*camera, playerTexture, playerMidpoint(player), PLAYER_HEIGHT, GREEN);
        DrawSphere(Vector3Multiply(player->position, (Vector3) { 1, 0, 1 }), 0.4, BLACK);
    }
    DrawSphere(Vector3Multiply(state->state.ball.position, (Vector3) { 1, 0, 1 }), 0.4, BLACK);
    DrawBillboard(*camera, ballTexture, state->state.ball.position, 1, WHITE);
}
