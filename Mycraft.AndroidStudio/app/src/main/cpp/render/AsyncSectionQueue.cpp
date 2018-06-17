//
// Created by twome on 17/06/2018.
//

#include "AsyncSectionQueue.h"
#include <pthread.h>

std::queue<Section *> AsyncSectionQueue::sectionQueue;

bool AsyncSectionQueue::running;

void AsyncSectionQueue::schedule(Section *section) {
    sectionQueue.push(section);
}

void AsyncSectionQueue::initialize() {
    running = true;
    sectionQueue = std::queue<Section *>();
    for (int i = 0; i < 4; i++) {
        pthread_t thread;
        pthread_create(&thread, NULL, AsyncSectionQueue::work, NULL);
    }
}

void *AsyncSectionQueue::work(void *) {
    while (running) {
        if (sectionQueue.size() > 0) {
            Section *section = sectionQueue.front();
            sectionQueue.pop();
            section->sectionRenderer->buildData();
        } else {
            nanosleep((const struct timespec[]) {{0, 20000000L}}, NULL);
        }
    }
    return NULL;
}

void AsyncSectionQueue::shutdown() {
    running = false;
}
