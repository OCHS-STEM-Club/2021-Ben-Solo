#pragma once //Runs code below once

#include <frc/WPILib.h>
#include <networktables/NetworkTable.h> //Allows us to get get data from Network Table
#include <networktables/NetworkTableInstance.h>
#include <frc/AddressableLED.h>

#define AREA_DISTANCE_RATIO 4.1823379 //2.11249
#define MAX_STEER 0.4 // the maximum value sent to steer the robot
#define STEER_K 0.175
#define DRIVE_K 1.35
#define MAX_DRIVE 0.5

#define LED_LENGTH 6

class VisionManager { //Creates vision manager object
private: //Only the vision subclass can effect
frc::Joystick *stick;

bool imageToggle = true; //bool = true or false
bool imageSwitch = false;

double rawDistance; //double = any number
double distanceFlat;

double turnOutput;
double moveOutput;
double moveWant = 2.34; //0.88 trench

frc::AddressableLED *led;



public: //Everything below is made accessable
    VisionManager();
    void display();
    double distance();
    double trackTurn();
    double trackMove();
};