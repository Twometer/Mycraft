//
// Created by twome on 22/06/2018.
//

#include "jtime.h"

int64_t time_util::get_time_nanos() {
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec * 1000000000LL + now.tv_nsec;
}