// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "../screen.h"
#include <assert.h>
#include <raylib.h>
#include <stdio.h>

static const int FONT_SIZE = 30;

static void draw_line(bool paused) {
    const int x = GetScreenWidth() / 2;

    if (!paused) {
        const int y = GetScreenHeight();
        DrawLine(x, 0, x, y, WHITE);
    } else {
        Vector2 text_size = MeasureTextEx(GetFontDefault(), "+", FONT_SIZE,
                                          (float)FONT_SIZE / 10);

        int top_start    = 0;
        int top_end      = GetScreenHeight() / 2 - (int)text_size.y;
        int bottom_start = GetScreenHeight() / 2 + (int)text_size.y;
        int bottom_end   = GetScreenHeight();

        DrawLine(x, top_start, x, top_end, WHITE);
        DrawLine(x, bottom_start, x, bottom_end, WHITE);
    }
}

static void draw_message(const char *text) {
    Vector2 text_size =
        MeasureTextEx(GetFontDefault(), text, FONT_SIZE, (float)FONT_SIZE / 10);

    DrawText(text, GetScreenWidth() / 2 - (int)text_size.x / 2,
             GetScreenHeight() / 2 - (int)text_size.y / 2, FONT_SIZE, WHITE);
}

static void screen_gameplay_restart(struct game_state *state) {
    screen_gameplay_init(state);
    state->started = true;
    state->paused  = false;
}

void screen_gameplay_init(struct game_state *state) {
    assert(state);

    state->paused  = true;
    state->started = false;
    state->player  = make_paddle(PADDLE_LEFT);
    state->rival   = make_paddle(PADDLE_RIGHT);
    state->ball    = make_ball();
}

void screen_gameplay_deinit(struct game_state *state) {
    assert(state);

    state->paused  = true;
    state->started = false;
    state->player  = (struct paddle){0};
    state->rival   = (struct paddle){0};

    ball_deinit(&state->ball);
    state->ball = (struct ball){0};
}

void screen_gameplay_input(struct game_state *state) {
    assert(state);

    if (IsKeyPressed(KEY_R)) screen_gameplay_restart(state);
    if (IsKeyPressed(KEY_SPACE)) {
        state->paused = !state->paused;
        if (!state->started && !state->paused) state->started = true;
    }

    if (!state->paused) {
        if (IsKeyDown(KEY_W)) paddle_move_up(&state->player);
        if (IsKeyDown(KEY_S)) paddle_move_down(&state->player);
        if (IsKeyDown(KEY_UP)) paddle_move_up(&state->rival);
        if (IsKeyDown(KEY_DOWN)) paddle_move_down(&state->rival);
    }
}

void screen_gameplay_update(struct game_state *state) {
    assert(state);

    if (!state->paused) {
        paddle_update(&state->player);
        paddle_update(&state->rival);
        ball_update(&state->ball, &state->player, &state->rival);
    }

    if (paddle_win(&state->player) || paddle_win(&state->rival)) {
        state->paused = true;
    }
}

void screen_gameplay_draw(struct game_state *const state) {
    assert(state);

    paddle_draw_score(&state->player);
    paddle_draw_score(&state->rival);
    draw_line(state->paused);
    if (state->paused) {
        if (paddle_win(&state->player) || paddle_win(&state->rival)) {
            draw_message("PRESS R TO RESTART");
        } else if (!state->started) {
            draw_message("PRESS SPACE TO START");
        } else {
            draw_message("PAUSED");
        }
    }

    paddle_draw(&state->player);
    paddle_draw(&state->rival);

    if (state->started && !paddle_win(&state->player) &&
        !paddle_win(&state->rival)) {
        ball_draw(&state->ball);
    }
}
