//
// Created by twome on 22/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_TICKENGINE_H
#define MYCRAFT_ANDROIDSTUDIO_TICKENGINE_H

#define NS_PER_SECOND 1000000000
#define MAX_NS_PER_UPDATE 1000000000
#define TICKS_PER_SECOND 20.0f

class TickEngine {
private:
    float passedTime;
    int64_t lastTime;

public:
    int ticks;
    float partialTicks;

    TickEngine();

    void update();
};


#endif //MYCRAFT_ANDROIDSTUDIO_TICKENGINE_H
