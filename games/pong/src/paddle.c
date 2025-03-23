// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "paddle.h"
#include "assert.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>

static const int SCORES_TO_WIN = 10;

static const Vector2 PADDLE_SIZE   = {10, 50};
static const Color   PADDLE_COLOR  = WHITE;
static const float   PADDLE_OFFSET = 10;
static const float   PADDLE_SPEED  = 500;

struct paddle make_paddle(enum paddle_position position) {
    struct paddle paddle = {0};
    paddle_init(&paddle, position);
    return paddle;
}

void paddle_init(struct paddle *paddle, enum paddle_position position) {
    assert(paddle);

    paddle->rec.width  = PADDLE_SIZE.x;
    paddle->rec.height = PADDLE_SIZE.y;
    paddle->rec.y      = (float)(GetScreenHeight()) / 2 - PADDLE_SIZE.y / 2;
    switch (position) {
    case PADDLE_LEFT:
        paddle->rec.x = PADDLE_OFFSET;
        break;
    case PADDLE_RIGHT:
        paddle->rec.x = (float)(GetScreenWidth())-PADDLE_SIZE.x - PADDLE_OFFSET;
        break;
    }

    paddle->color = PADDLE_COLOR;
    paddle->speed = PADDLE_SPEED;
    paddle->score = 0;
}

void paddle_update(struct paddle *const _) {}

void paddle_draw(struct paddle *const paddle) {
    assert(paddle);

    DrawRectangleRec(paddle->rec, paddle->color);
}

void paddle_draw_score(struct paddle *const paddle) {
    assert(paddle);

    bool is_right = paddle->rec.x > (float)(GetScreenWidth()) / 2;

    int  score_font_size = 48;
    char score_str[2];
    sprintf(score_str, "%d", paddle->score);
    Vector2 score_size =
        MeasureTextEx(GetFontDefault(), "+", (float)score_font_size,
                      (float)score_font_size / 10);
    int score_x = GetScreenWidth() / 4 - (int)score_size.x / 2;
    int score_y = 50;
    if (is_right) score_x += GetScreenWidth() / 2 + (int)score_size.x;
    DrawText(score_str, score_x, score_y, score_font_size, WHITE);

    if (paddle_win(paddle)) {
        const char *win_str       = "WIN";
        int         win_font_size = 30;
        Vector2     win_size =
            MeasureTextEx(GetFontDefault(), win_str, (float)win_font_size,
                          (float)win_font_size / 10);
        int win_x = score_x + (int)score_size.x / 2 - (int)win_size.x / 2;
        int win_y = score_y + (int)score_size.y + 4;
        DrawText(win_str, win_x, win_y, win_font_size, WHITE);
    }
}

void paddle_move_up(struct paddle *paddle) {
    assert(paddle);

    paddle->rec.y = fmaxf(paddle->rec.y - paddle->speed * GetFrameTime(), 0);
}

void paddle_move_down(struct paddle *paddle) {
    assert(paddle);

    paddle->rec.y = fminf(paddle->rec.y + paddle->speed * GetFrameTime(),
                          (float)(GetScreenHeight())-paddle->rec.height);
}

void paddle_score_up(struct paddle *paddle) {
    assert(paddle);

    paddle->score++;
}

bool paddle_win(struct paddle *const paddle) {
    assert(paddle);

    return paddle->score >= SCORES_TO_WIN;
}
