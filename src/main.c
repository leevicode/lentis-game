#include "gamestate.h"
#include "input.h"
#include "raylib.h"
#include "raymath.h"
#include "stdio.h"

void mainloop(MainState* state);
int main()
{
    MainState state = { 0 };
    InputManager* manager = getManager();
    state.controllers[0] = (Controller) {
        &state.state.teams[0].players[0],
        getInputDevices(manager)[0]
    };
    state.controllers[1] = (Controller) {
        &state.state.teams[0].players[1],
        getInputDevices(manager)[1]
    };

    printf("hello world!\n");
    mainloop(&state);
    return 0;
}

void mainloop(MainState* state)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InputManager* manager = getManager();
    SetConfigFlags(FLAG_MSAA_4X_HINT); // Set MSAA 4X hint before windows creation
    InitWindow(screenWidth, screenHeight, "volley");
    Texture2D playerImage = LoadTexture("resource/Standing.png");
    Texture2D ballImage = LoadTexture("resource/Ball.png");

    Camera3D camera = { 0 };
    camera.position = (Vector3) { 0.0f, 13.0f, 18.0f }; // Camera position
    camera.target = (Vector3) { 0.0f, 0.0f, 0.0f }; // Camera looking at point
    camera.up = (Vector3) { 0.0f, 1.0f, 0.0f }; // Camera up vector (rotation towards target)
    camera.fovy = 38.0f; // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
    state->state.ball.position.y = 5;
    state->state.ball.motion = (Vector3) { 4, 3, -3 };
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        updateState(state, deltaTime);

        // TODO: implement proper rendering
        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode3D(camera);
        drawState(state, &camera, playerImage, ballImage);
        EndMode3D();
        EndDrawing();
    }
}