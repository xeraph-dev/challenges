// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "game.h"
#include "screen.h"
#include <assert.h>

void game_init(struct game_state *state) {
    state->screen = SCREEN_EMPTY;
    change_screen(state, SCREEN_GAMEPLAY);
}

void game_deinit(struct game_state *state) { screen_deinit(state); }

void game_update(struct game_state *state) {
    assert(state);

    screen_input(state);
    screen_update(state);
}

void game_draw(struct game_state *const state) {
    assert(state);

    screen_draw(state);

    DrawFPS(10, 10);
}
