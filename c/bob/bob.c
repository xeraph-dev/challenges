#include "bob.h"

#include <ctype.h>
#include <iso646.h>
#include <stdbool.h>

char *hey_bob(char *greeting) {
    bool yell = {false};
    bool stop_yell = {false};
    bool silence = {true};

    char last = {0};

    while (*greeting != '\0') {
        if (not isspace(*greeting) and silence) {
            silence = false;
        }

        if (isupper(*greeting) and not yell and not stop_yell) {
            yell = true;
        }
        if (islower(*greeting) and yell and not stop_yell) {
            yell = false;
            stop_yell = true;
        }
        if (not isspace(*(greeting))) {
            last = *greeting;
        }
        greeting++;
    }

    bool question = not silence and last == '?';

    if (question and not yell)
        return "Sure.";
    else if (not question and yell)
        return "Whoa, chill out!";
    else if (question and yell)
        return "Calm down, I know what I'm doing!";
    else if (silence)
        return "Fine. Be that way!";
    else
        return "Whatever.";
}
