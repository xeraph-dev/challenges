// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "game.h"
#include <raylib.h>

static const int   SCREEN_WIDTH  = 854;
static const int   SCREEN_HEIGHT = 480;
static const char *WINDOW_TITLE  = "PONG";
static const int   TARGET_FPS    = 60;

int main(void) {
    struct game_state state = {0};

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitAudioDevice();

    game_init(&state);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        game_update(&state);
        game_draw(&state);

        EndDrawing();
    }

    game_deinit(&state);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
