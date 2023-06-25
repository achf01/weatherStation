#ifndef __STEP_H__
#define __STEP_H__

#include <Stepper.h>
#include <Arduino.h>
#include "rotcontrol.h"

#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

#define IN5 25
#define IN6 26
#define IN7 27
#define IN8 14

const int stepsPerRevolution = 3410; //for 120 deg


Stepper init1(int in1=IN1, int in3=IN3, int in2=IN2, int in4=IN4,int stepPerRev=stepsPerRevolution);
Stepper init2(int in1=IN5, int in3=IN7, int in2=IN6, int in4=IN8,int stepPerRev=stepsPerRevolution);
void revolution_(Stepper* stepper, bool clock,int stepPerRev=stepsPerRevolution);

#endif
