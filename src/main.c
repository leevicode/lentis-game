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
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        updateState(state, deltaTime);

        // TODO: implement proper rendering
        BeginDrawing();
        ClearBackground(WHITE);
        Ball* ball = &state->state.ball;
        DrawCircle(ball->position.x, ball->position.z, 100.0, RED);
        for (int i = 0; i < NUM_CONTROLLERS; i++) {
            Player* player = state->controllers[i].player;
            DrawCircle(player->position.x, player->position.z, 50, BLUE);
        }
        EndDrawing();
    }
}