#include "step.h"
#include <Arduino.h>
#include <Stepper.h>



Stepper init1(int in1, int in3, int in2, int in4,int stepPerRev){
    Stepper myStepper(stepPerRev, in1, in3, in2, in4);
    myStepper.setSpeed(5);
    return myStepper;
}

Stepper init2(int in1, int in3, int in2, int in4,int stepPerRev){
    Stepper myStepper(stepPerRev, in1, in3, in2, in4);
    myStepper.setSpeed(5);
    return myStepper;
}

void revolution_(Stepper* stepper, bool clock,int stepPerRev){
    if(clock){
        stepper->step(-stepPerRev);
        // Serial.println("clock");
    }else{
        stepper->step(stepPerRev);
        // Serial.println("counter");
    }
    
}
