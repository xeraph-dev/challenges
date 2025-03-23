// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "screen.h"
#include <assert.h>

void change_screen(struct game_state *state, enum game_screen screen) {
    assert(state);

    screen_deinit(state);
    state->screen = screen;
    screen_init(state);
}

void screen_init(struct game_state *state) {
    assert(state);

    switch (state->screen) {
    case SCREEN_EMPTY:
        break;
    case SCREEN_GAMEPLAY:
        screen_gameplay_init(state);
        break;
    }
}
void screen_deinit(struct game_state *state) {
    assert(state);

    switch (state->screen) {
    case SCREEN_EMPTY:
        break;
    case SCREEN_GAMEPLAY:
        screen_gameplay_deinit(state);
        break;
    }
}

void screen_input(struct game_state *state) {
    assert(state);

    switch (state->screen) {
    case SCREEN_EMPTY:
        break;
    case SCREEN_GAMEPLAY:
        screen_gameplay_input(state);
        break;
    }
}

void screen_update(struct game_state *state) {
    assert(state);

    switch (state->screen) {
    case SCREEN_EMPTY:
        break;
    case SCREEN_GAMEPLAY:
        screen_gameplay_update(state);
        break;
    }
}
void screen_draw(struct game_state *const state) {
    assert(state);

    switch (state->screen) {
    case SCREEN_EMPTY:
        break;
    case SCREEN_GAMEPLAY:
        screen_gameplay_draw(state);
        break;
    }
}
