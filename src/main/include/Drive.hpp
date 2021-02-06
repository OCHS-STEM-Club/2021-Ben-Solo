#pragma once //runs only once

#include <frc/WPILib.h> 
#include <rev/CANSparkMax.h>
#include <AHRS.h>
//#include <Robot.h>

#define TURN_K 0.012 //0.4

class DriveManager { 
    private:
    rev::CANSparkMax *driveMotorLeft; // declares motor controllers
    rev::CANSparkMax *driveMotorRight;

    rev::CANSparkMax *slaveMotorLeft1;
    rev::CANSparkMax *slaveMotorLeft2;
    rev::CANSparkMax *slaveMotorRight1;
    rev::CANSparkMax *slaveMotorRight2;

    //rev::CANEncoder *leftDriveEnc;
    //rev::CANEncoder *rightDriveEnc;

    frc::DifferentialDrive *robotDrive;
    //frc::Joystick *stick;
    frc::XboxController *xbox;
    frc::XboxController *xboxDrive;

    AHRS *gyro;

    frc::Timer *autoTime;

    double xStickValue; //creates stick varibles
    double yStickValue;

    double revNeed;
    double offset;
    double leftCurrentPos;
    double rightCurrentPos;
    double avgPosition;
    double power;
    double leftEncLast;
    double rightEncLast;
    double gyroLast;
    double turnCorrection;
    double turnOffset;

    double currentAngle;

    bool colorwheelExtended = false;

    public:
    DriveManager();
    void drive();
    void subclassTurn(double turnValue, double moveValue);
    void autoDrive(double distance);
    void autoPrep();
    void autoTurn(double angle);
    void autoBasic();
    void zeroDrive();
}; 