#include "gamestate.h"
#include "input.h"
#include "raylib.h"
#include "raymath.h"
#include "stdio.h"

void mainloop(MainState *state);
int main() {
  MainState state = {0};
  InputManager *manager = getManager();
  state.controllers[0] = (Controller){&state.state.teams[0].players[0],
                                      getInputDevices(manager)[0]};

  printf("hello world!\n");
  mainloop(&state);
  return 0;
}

void mainloop(MainState *state) {
  const int screenWidth = 800;
  const int screenHeight = 450;
  InputManager *manager = getManager();
  SetConfigFlags(FLAG_MSAA_4X_HINT); // Set MSAA 4X hint before windows creation

  InitWindow(screenWidth, screenHeight, "volley");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    InputDevice device = state->controllers[0].device;
    Player *player = state->controllers[0].player;
    Vector2 input = getMovement(NULL, device);
    player->position =
        Vector3Add(player->position, (Vector3){input.x, input.y, 0});
    BeginDrawing();
    ClearBackground(WHITE);
    DrawCircle(player->position.x, player->position.y, 100.0, RED);
    EndDrawing();
  }
}