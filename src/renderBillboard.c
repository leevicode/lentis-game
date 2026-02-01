#include "ball.h"
#include "gamestate.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include "types.h"

Texture2D playerTexture;
Texture2D ballTexture;
Model backgroundModel;
void loadResources()
{
    playerTexture = LoadTexture("resource/Standing.png");
    ballTexture = LoadTexture("resource/Ball.png");
    backgroundModel = LoadModel("resource/Untitled.glb");
}

void drawState(GameState* state, Camera* camera, float deltaTime)
{
    Vector3 ballMidPoint = Vector3Multiply(state->ball.position, (Vector3) { 1, 0.5, 1 });
    camera->target = Vector3Add(
        Vector3Scale(camera->target, 1 - (2 * deltaTime)),
        Vector3Scale(ballMidPoint, 2 * deltaTime));
    float distance = Vector3Distance(
        state->ball.position,
        Vector3Multiply(
            state->ball.position,
            (Vector3) { 1, 0, 1 }));
    distance /= 10;
    distance *= distance;
    camera->fovy = 30.0 - 11.0 / (distance + 1);
    DrawModel(backgroundModel, Vector3Zero(), 10, WHITE);
    DrawPlane(Vector3Zero(), (Vector2) { 20, 10 }, BEIGE);
    DrawBoundingBox(state->net, ORANGE);

    for (int i = 0; i < NUM_TEAMS; i++) {
        DrawBoundingBox(state->teams[i].playerBounds, state->teams[i].color);
        DrawBoundingBox(state->teams[i].teamBounds, PURPLE);
    }
    for (int i = 0; i < MAX_PLAYERS; i++) {
        Player* player = state->controllers[i].player;
        if (!player) {
            continue;
        }
        DrawBillboard(*camera, playerTexture, playerMidpoint(player), PLAYER_HEIGHT, player->team->color);
        DrawSphere(Vector3Multiply(player->position, (Vector3) { 1, 0, 1 }), 0.4, BLACK);
    }
    DrawSphere(Vector3Multiply(state->ball.position, (Vector3) { 1, 0, 1 }), 0.4, BLACK);
    DrawBillboard(*camera, ballTexture, state->ball.position, 1, WHITE);
}
