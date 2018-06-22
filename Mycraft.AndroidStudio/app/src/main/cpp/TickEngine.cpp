//
// Created by twome on 22/06/2018.
//

#include <linux/time.h>
#include <stdint.h>
#include <time.h>
#include "TickEngine.h"

int64_t nanoTime() {
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec * 1000000000LL + now.tv_nsec;
}

TickEngine::TickEngine() {
    this->passedTime = 0;
    this->lastTime = nanoTime();
}

void TickEngine::update() {
    int64_t now = nanoTime();
    int64_t passedNs = now - lastTime;
    lastTime = now;
    if (passedNs < 0) passedNs = 0;
    if (passedNs > MAX_NS_PER_UPDATE) passedNs = MAX_NS_PER_UPDATE;
    passedTime += passedNs * TICKS_PER_SECOND / NS_PER_SECOND;
    ticks = (int) passedTime;
    if (ticks > 100) ticks = 100;
    this->passedTime -= ticks;
    this->partialTicks = passedTime;
}
