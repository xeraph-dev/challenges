#include "secret_handshake.h"

#include <stdbool.h>
#include <stdlib.h>

enum command {
    WINK = 1 << 0,
    BLINK = 1 << 1,
    CLOSE = 1 << 2,
    JUMP = 1 << 3,
    REVERSE = 1 << 4,
};

static bool command_check(enum command command, size_t number) {
    return ((number | ~command) ^ ~command) == command;
}

static char *command_string(enum command command) {
    switch (command) {
    case WINK:
        return "wink";
    case BLINK:
        return "double blink";
    case CLOSE:
        return "close your eyes";
    case JUMP:
        return "jump";
    case REVERSE:
    default:
        return "";
    }
}

static const enum command COMMANDS[4] = {WINK, BLINK, CLOSE, JUMP};
static const enum command *COMMANDS_END = COMMANDS + 4;
static const enum command COMMANDS_REVERSE[4] = {JUMP, CLOSE, BLINK, WINK};
static const enum command *COMMANDS_REVERSE_END = COMMANDS_REVERSE + 4;

const char **commands(size_t number) {
    char **cmds = calloc(4, sizeof(char *));
    size_t cmds_len = {0};

    const enum command *commands_start =
        command_check(REVERSE, number) ? COMMANDS_REVERSE : COMMANDS;
    const enum command *commands_end =
        command_check(REVERSE, number) ? COMMANDS_REVERSE_END : COMMANDS_END;

    for (const enum command *command = {commands_start}; command < commands_end;
         command++) {
        if (command_check(*command, number)) {
            cmds[cmds_len++] = command_string(*command);
        }
    }

    return (const char **)cmds;
}
