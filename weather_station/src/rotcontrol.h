#ifndef __ROTCONTROL_H__
#define __ROTCONTROL_H__

#include <step.h>

typedef enum{SUN, RAIN, SNOW}down;
typedef enum{CLEAR, CLOUD, STORM}up;

typedef struct{
    bool rain;
    bool snow;
    bool sun;
    bool clear;
    bool storm;
    bool cloud;
}info_reduced;


info_reduced init_info(up* up_state, down* down_state);

void rot_control(up* up_state, down* down_state, info_reduced info, Stepper *stp1, Stepper *stp2);

void set_weather(char* set_weather);


#endif