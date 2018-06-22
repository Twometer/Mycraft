//
// Created by twome on 22/06/2018.
//

#include <stdint.h>
#include "TickEngine.h"
#include "util/jtime.h"

TickEngine::TickEngine() {
    this->passedTime = 0;
    this->lastTime = time_util::get_time_nanos();
}

void TickEngine::update() {
    int64_t now = time_util::get_time_nanos();
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
