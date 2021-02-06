#pragma once //runs only once

#include <frc/WPILib.h> 
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h> 

class ShooterManager { 
    private:
    WPI_TalonSRX *shootMotor;

    WPI_TalonSRX *feederMotor;
    WPI_TalonSRX *hoodMotor;

    frc::XboxController *xbox;

    frc::DigitalInput *hoodEncoder;
    //frc::Counter *hoodCount;
    frc::AnalogPotentiometer *hoodPotent;
    
    double velocityOut;
    double velocityAct;
    //bool currentEncoderState;
    //int hoodEncoderCount = 0;
    int hoodPosition;

    double velocityWant;

    public:
    ShooterManager();
    void shoot(double velocityIn, double enabled);
    void hoodRotate(double hoodPosition);
    void shootTest(double in);
    void shootAuto(bool doShoot);
    void stopShoot();

};
