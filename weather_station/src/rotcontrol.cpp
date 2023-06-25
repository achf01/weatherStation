#include <Arduino.h>
#include "step.h"
#include "rotcontrol.h"
#include <EEPROM.h>

#define EEPROM_SIZE sizeof(int)*2


typedef struct{
    up up_state;
    void (*state_func)(info_reduced info, Stepper* stp, up* state);
}msfup;


typedef struct{
    down down_state;
    void (*state_func)(info_reduced info, Stepper* stp, down* state);
}msfdown;

void fn_CLEAR(info_reduced info,Stepper *stp2, up* state ){
    // Serial.println("UP: Elaborating state CLEAR");
    if(info.storm){
        revolution_(stp2,false);
        *state=STORM;
        Serial.println("to STORM");
    }else if(info.cloud){
        revolution_(stp2,true);
        *state=CLOUD;
        Serial.println("to CLOUD");
    }
}

void fn_CLOUD(info_reduced info,Stepper *stp2, up* state){
    // Serial.println("UP: Elaborating state CLOUD");
    if(info.storm){
        revolution_(stp2,true);
        *state=STORM;
        Serial.println("to STORM");
    }else if(info.clear){
        revolution_(stp2,false);
        *state=CLEAR;
        Serial.println("to CLEAR");
    }
}

void fn_STORM(info_reduced info,Stepper *stp2, up* state){
    // Serial.println("UP: Elaborating state STORM");
    if(info.clear){
        revolution_(stp2,true);
        *state=CLEAR;
        Serial.println("to CLEAR");
    }else if(info.cloud){
        revolution_(stp2,false);
        *state=CLOUD;
        Serial.println("to CLOUD");
    }
}



void fn_SUN(info_reduced info,Stepper *stp1, down* state){
    // Serial.println("DOWM: Elaborating state SUN");
    if (info.snow){
        revolution_(stp1,true);
        *state=SNOW;
        Serial.println("to SNOW");
    }
    else if (info.rain){
        revolution_(stp1,false);
        *state=RAIN;
        Serial.println("to RAIN");
    } 
}

void fn_RAIN(info_reduced info,Stepper *stp1, down* state){
    // Serial.println("DOWM: Elaborating state RAIN");
    if (info.snow){
        revolution_(stp1,false);
        *state=SNOW;
        Serial.println("to SNOW");
    } 
    else if (info.sun){
        revolution_(stp1,true);
        *state=SUN;
        Serial.println("to SUN");
    }
}

void fn_SNOW(info_reduced info,Stepper *stp1, down* state){
    // Serial.println("DOWM: Elaborating state SNOW");
    if (info.rain){
        revolution_(stp1,true);
        *state=SNOW;
        Serial.println("to SNOW");
    } 
    else if (info.sun){
        revolution_(stp1,false);
        *state=SUN;
        Serial.println("to SUN");
    }
}

msfup fsm_up[]={
    {CLEAR, fn_CLEAR},
    {CLOUD, fn_CLOUD},
    {STORM, fn_STORM}                  
};

msfdown fsm_down[]={
    {SUN,fn_SUN},
    {RAIN,fn_RAIN},
    {SNOW,fn_SNOW}
};

void rot_control(up* up_state, down* down_state, info_reduced info, Stepper *stp1, Stepper *stp2){
    Serial.println("control_elaboration");
    (*fsm_up[*up_state].state_func)(info, stp1, up_state);
    (*fsm_down[(*down_state)].state_func)(info, stp2, down_state);
    EEPROM.write(0, *up_state);
    EEPROM.commit();
    EEPROM.write(4, *down_state);
    EEPROM.commit();
}

info_reduced init_info(up* up_state, down* down_state){
    EEPROM.begin(EEPROM_SIZE);
    int state_up = EEPROM.read(0); // one per wheel
    int state_down = EEPROM.read(4); // one per wheel
    info_reduced info;
    switch(state_up){
        case 0:{
            info.clear=true;
            info.storm=false;
            info.cloud=false;
            *up_state=CLEAR;
        };break;
        case 1:{
            info.clear=false;
            info.storm=false;
            info.cloud=true;
            *up_state=CLOUD;
        };break;
        case 2:{
            info.clear=false;
            info.storm=true;
            info.cloud=false;
            *up_state=STORM;
        };break;
        default:{
            info.clear=true;
            info.storm=false;
            info.cloud=false;
            *up_state=CLEAR;
        }
    }

    switch(state_down){
        case 0:{
            info.sun=true;
            info.rain=false;
            info.snow=false;
            *down_state=SUN;
        };break;
        case 1:{
            info.sun=false;
            info.rain=true;
            info.snow=false;
            *down_state=RAIN;
        };break;
        case 2:{
            info.sun=false;
            info.rain=false;
            info.snow=true;
            *down_state=SNOW;
        };break;
        default:{
            info.sun=true;
            info.rain=false;
            info.snow=false;
            *down_state=SUN;
        }
    }


    return info;
}