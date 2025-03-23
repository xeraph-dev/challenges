// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include "paddle.h"
#include <raylib.h>

struct ball {
    Vector2 center;
    Vector2 speed;
    float   radius;
    Color   color;
    Sound   impact_sound;
    Sound   destroy_sound;
};

struct ball make_ball(void);
void        ball_init(struct ball *ball);
void        ball_deinit(struct ball *ball);
void        ball_restart(struct ball *ball);
void        ball_update(struct ball *ball, struct paddle *player,
                        struct paddle *rival);
void        ball_draw(struct ball *const ball);
