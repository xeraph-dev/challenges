// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <raylib.h>

enum paddle_position { PADDLE_LEFT, PADDLE_RIGHT };

struct paddle {
    Rectangle rec;
    Color     color;
    float     speed;
    int       score;
};

struct paddle make_paddle(enum paddle_position position);
void          paddle_init(struct paddle *paddle, enum paddle_position position);
void          paddle_update(struct paddle *paddle);
void          paddle_draw(struct paddle *const paddle);
void          paddle_draw_score(struct paddle *const paddle);
void          paddle_move_up(struct paddle *paddle);
void          paddle_move_down(struct paddle *paddle);
void          paddle_score_up(struct paddle *paddle);
bool          paddle_win(struct paddle *const paddle);
