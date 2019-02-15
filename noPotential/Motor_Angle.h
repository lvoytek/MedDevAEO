//Header for motor angle file

#ifndef MOTOR_ANGLE_H
#define MOTOR_ANGLE_H

#include <Arduino.h>

const int dirPin = 7;  //stepper motor //PIN ASSIGNMENTS! 
const int stepPin = 6; 
const int sleepPin = 18;
const float R1 = 11470;
const float Angle1 = 0;
const float Angle2 = 90;//52
const float Resistance1 = 2280;
const float Resistance2 = 3880;
const float Vin = 3.3;
const float PotSlope = (Resistance2 - Resistance1) / (Angle2 - Angle1);
const float PotIntercept = (Resistance2 + Resistance1 - PotSlope*(Angle1 + Angle2)) / float(2);
const int SensorPin = A0; 

//Here are the variables that will be used to parse the lines of the firebase database
//First the strings are set to the lines of interest in the database
//Then later the strings will be manipulated to find the target angles, number of reps, and start flag
String StartString = "true";
String Start = "true";
String ExerciseRepsString = "3";
int ExerciseReps = 3;
String TargetExtendString = "0";
int TargetExtend = 0;
String TargetFlexString = "91";
int TargetFlex = 91;
String ExerciseTodayString = "";


void setup_motor();
void start_motor();
void exercise();
int calibrate();
float read_angle();
void extend();
void flex();
void step_forward();
void step_backward();





#endif