#include "gamestate.h"
#include "input.h"
#include "raylib.h"
#include "stdio.h"
#include <iso646.h>

// TODO: move functionality from here to game.c
void mainloop(MainState* state);
int main()
{
    MainState state = { 0 };
    InputManager* manager = getManager();
    state.state.ball.position.y = 5;
    state.state.ball.motion = (Vector3) { 4, 3, -3 };
    printf("hello world!\n");
    mainloop(&state);
    return 0;
}

void resolvePlayers(MainState* state);
Camera3D initializeGame(MainState* state)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InputManager* manager = getManager();
    SetConfigFlags(FLAG_MSAA_4X_HINT); // Set MSAA 4X hint before windows creation
    InitWindow(screenWidth, screenHeight, "volley");
    // Initialize camera
    Camera3D camera = { 0 };
    camera.position = (Vector3) { 0.0f, 13.0f, 18.0f }; // Camera position
    camera.target = (Vector3) { 0.0f, 0.0f, 0.0f }; // Camera looking at point
    camera.up = (Vector3) { 0.0f, 1.0f, 0.0f }; // Camera up vector (rotation towards target)
    camera.fovy = 38.0f; // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
    loadResources();
    SetTargetFPS(60);
    resolvePlayers(state);
    return camera;
}

Player newPlayer()
{
    Player player = { 0 };
    return player;
}
void resolvePlayers(MainState* state)
{
    InputManager* manager = getManager();
    InputDevice* devices = getInputDevices(manager);
    WindowShouldClose();
    state->state.players[0] = newPlayer();
    state->controllers[0] = (Controller) {
        &state->state.players[0],
        devices[0]
    };
    while (!IsKeyPressed(KEY_ENTER)) {
        WindowShouldClose();
        BeginDrawing();
        ClearBackground(WHITE);

        for (int i = 0; i < MAX_PLAYERS; i++) {
            InputDevice device = devices[i];
            Player** controllerPlayer = &(state->controllers[i].player);
            Player* statePlayer = &(state->state.players[i]);

            if (devices[i] != -1 && !IsGamepadAvailable(devices[i])) {
                continue;
            }
            char string[10000];
            if (isJumpPressed(manager, devices[i])) {
                state->state.players[i] = newPlayer();
                *controllerPlayer = statePlayer;
                state->controllers[i].device = devices[i];
            }
            if (isHitPressed(manager, devices[i])) {
                *controllerPlayer = NULL;
            }
            sprintf(string, "controller %d", device);
            DrawText(string, 20, 10 + 20 * i, 20, ORANGE);
            if (state->controllers[i].player) {
                DrawText("+", 5, 10 + 20 * i, 20, GREEN);
            }
        }
        EndDrawing();
    }
    return;
}

void mainloop(MainState* state)
{
    Camera3D camera = initializeGame(state);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        updateState(state, deltaTime);

        // TODO: implement proper rendering
        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode3D(camera);
        drawState(state, &camera, deltaTime);
        EndMode3D();
        EndDrawing();
    }
}