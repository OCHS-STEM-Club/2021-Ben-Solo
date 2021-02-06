#pragma once //runs only once

#include <frc/WPILib.h> 
#include <ctre/Phoenix.h>

class ClimbManager { 
    private:
    WPI_TalonFX *climbMotor;
    WPI_TalonSRX *extendMotor;
    frc::XboxController *xbox;
    //frc::XboxController *driveXbox;
    frc::Joystick *stick;

    int pov;
    double winchPower;

    public:
    ClimbManager();
    void climb();
    void climbTest();
};