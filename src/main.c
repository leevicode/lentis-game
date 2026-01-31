#include "gamestate.h"
#include "input.h"
#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "types.h"

// TODO: move functionality from here to game.c
void mainloop(GameState* state, Camera3D camera);
void setupTeams(GameState* state);
Camera3D initializeGame(GameState* state);
Player newPlayer();
int main()
{
    GameState state = { 0 };
    state.net = (BoundingBox) {
        (Vector3) { -0.2, 0, -5 },
        (Vector3) { 0.2, 3, 5 }
    };
    state.manager = getManager();
    state.ball.position = (Vector3) { -0.7, 3.5, -1 };
    state.ball.motion = (Vector3) { 1.4, 0.1, -0.1 };
    state.ball.position = (Vector3) { -7, 1, -1 };
    state.ball.motion = (Vector3) { 10, 5, -3 };

    printf("hello world!\n");
    Camera3D camera = initializeGame(&state);
    setupTeams(&state);
    mainloop(&state, camera);
    return 0;
}

Camera3D initializeGame(GameState* state)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    SetConfigFlags(FLAG_MSAA_4X_HINT); // Set MSAA 4X hint before windows creation
    InitWindow(screenWidth, screenHeight, "volley");
    // Initialize camera
    Camera3D camera = { 0 };
    camera.position = (Vector3) { 0.0f, 23.0f, 30.0f }; // Camera position
    camera.target = (Vector3) { 0.0f, 0.0f, 0.0f }; // Camera looking at point
    camera.up = (Vector3) { 0.0f, 1.0f, 0.0f }; // Camera up vector (rotation towards target)
    camera.fovy = 30.0f; // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
    loadResources();
    SetTargetFPS(60);
    return camera;
}

void setupTeams(GameState* state)
{
    InputManager* manager = state->manager;
    InputDevice* devices = getInputDevices(manager);
    state->teams[0] = (Team) { 0, RED };
    state->teams[1] = (Team) { 0, BLUE };
    WindowShouldClose();
    state->controllers[0] = (Controller) {
        NULL,
        devices[0]
    };
    while (!IsKeyPressed(KEY_ENTER)) {
        WindowShouldClose();
        BeginDrawing();
        ClearBackground(WHITE);
        for (int i = 0; i < MAX_PLAYERS; i++) {
            InputDevice device = devices[i];
            Player** controllerPlayer = &(state->controllers[i].player);
            if (devices[i] != -1 && !IsGamepadAvailable(devices[i])) {
                continue;
            }
            char string[10000];

            if (isJumpPressed(manager, devices[i])) {
                if (!*controllerPlayer) {
                    *controllerPlayer = malloc(sizeof(Player));
                    **controllerPlayer = newPlayer();
                    (*controllerPlayer)->team = state->teams;
                    state->controllers[i].device = devices[i];
                }
            }

            if (isHitPressed(manager, devices[i]) && *controllerPlayer) {
                free(*controllerPlayer);
                *controllerPlayer = NULL;
            }

            // change color
            if (*controllerPlayer) {
                float x = getMovement(manager, device).x;
                if (x > 0.2 || x < -0.2) {
                    (*controllerPlayer)->team = (*controllerPlayer)->team == state->teams ? state->teams + 1 : state->teams;
                }
            }

            sprintf(string, "controller %d", device);
            Color color;
            if (*controllerPlayer && (*controllerPlayer)->team) {
                color = (*controllerPlayer)->team->color;
            } else {
                color = BLACK;
            }

            DrawText(string, 20, 10 + 20 * i, 20, color);
            if (state->controllers[i].player) {
                DrawText("+", 5, 10 + 20 * i, 20, GREEN);
            }
        }
        EndDrawing();
    }
    ToggleBorderlessWindowed();
    return;
}

void mainloop(GameState* state, Camera3D camera)
{
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

Player newPlayer()
{
    Player p = { 0 };
    return p;
}
