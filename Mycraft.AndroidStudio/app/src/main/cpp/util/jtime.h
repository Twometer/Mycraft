//
// Created by twome on 22/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_JTIME_H
#define MYCRAFT_ANDROIDSTUDIO_JTIME_H

#include <linux/time.h>
#include <stdint.h>
#include <time.h>

class time_util {
public:
    static int64_t get_time_nanos();

};

#endif //MYCRAFT_ANDROIDSTUDIO_JTIME_H
