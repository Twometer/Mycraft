//
// Created by twome on 17/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_ASYNCSECTIONQUEUE_H
#define MYCRAFT_ANDROIDSTUDIO_ASYNCSECTIONQUEUE_H

#include <queue>
#include "../world/Section.h"

class AsyncSectionQueue {
private:
    static std::queue<Section *> sectionQueue;

    static bool running;

    static void *work(void*);

public:
    static void schedule(Section *section);

    static void initialize();

    static void shutdown();

};


#endif //MYCRAFT_ANDROIDSTUDIO_ASYNCSECTIONQUEUE_H
