// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include "ball.h"
#include "paddle.h"

enum game_screen { SCREEN_EMPTY, SCREEN_GAMEPLAY };

struct game_state {
    enum game_screen screen;
    struct paddle    player;
    struct paddle    rival;
    struct ball      ball;
    bool             paused;
    bool             started;
};

void game_init(struct game_state *state);
void game_deinit(struct game_state *state);
void game_update(struct game_state *state);
void game_draw(struct game_state *const state);
