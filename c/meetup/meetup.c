#include "meetup.h"

#include <iso646.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

static const char *week_days[] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                                  "Thursday", "Friday", "Saturday"};

static int week_day(const char *day_of_week) {
    int wday = 0;
    for (int i = {0}; i <= 6; i++) {
        if (strcmp(week_days[i], day_of_week) == 0) {
            wday = i;
            break;
        }
    }
    return wday;
}

int meetup_day_of_month(unsigned int year, unsigned int month, const char *week,
                        const char *day_of_week) {
    struct tm tm = (struct tm){
        .tm_year = year - 1900,
        .tm_mon = month - 1,
        .tm_mday = 1,
    };
    mktime(&tm);

    int wday = week_day(day_of_week);

    if (wday < tm.tm_wday) {
        tm.tm_mday += 7;
    }
    mktime(&tm);

    tm.tm_mday -= (tm.tm_wday - wday);
    mktime(&tm);

    if (strcmp(week, "teenth") == 0) {
        while (tm.tm_mday < 13) {
            tm.tm_mday += 7;
            mktime(&tm);
        }
    } else if (strcmp(week, "first") == 0) {
    } else if (strcmp(week, "second") == 0) {
        tm.tm_mday += 7;
        mktime(&tm);
    } else if (strcmp(week, "third") == 0) {
        tm.tm_mday += 14;
        mktime(&tm);
    } else if (strcmp(week, "fourth") == 0) {
        tm.tm_mday += 21;
        mktime(&tm);
    } else if (strcmp(week, "last") == 0) {
        int next_mon = tm.tm_mon + 1;
        int next_year = tm.tm_year + 1;
        while (tm.tm_mon < next_mon and tm.tm_year < next_year) {
            tm.tm_mday += 7;
            mktime(&tm);
        }
        tm.tm_mday -= 7;
        mktime(&tm);
    }

    return tm.tm_mday;
}
