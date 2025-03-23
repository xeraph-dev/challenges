// Copyright 2024 xeraph. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include "game.h"

void change_screen(struct game_state *state, enum game_screen screen);

void screen_init(struct game_state *state);
void screen_gameplay_init(struct game_state *state);

void screen_deinit(struct game_state *state);
void screen_gameplay_deinit(struct game_state *state);

void screen_input(struct game_state *state);
void screen_gameplay_input(struct game_state *state);

void screen_update(struct game_state *state);
void screen_gameplay_update(struct game_state *state);

void screen_draw(struct game_state *const state);
void screen_gameplay_draw(struct game_state *const state);
