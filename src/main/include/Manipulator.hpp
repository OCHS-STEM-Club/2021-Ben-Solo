#pragma once

#include <frc/WPILib.h>
#include <ctre/Phoenix.h> 
#include <rev/CANSparkMax.h>
#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"

#define COLORWHEELRATIO 0.25 //4/16
#define LOW_GOAL_HEIGHT 7.2

class ManipulatorManager {
private:
    rev::ColorSensorV3 m_colorSensor{frc::I2C::Port::kOnboard};
    rev::ColorMatch m_colorMatcher;
    /*static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429); //defult colors given by first
    static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
    static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
    static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113); */

    static constexpr frc::Color kGreenTarget = frc::Color(0.234, 0.519, 0.207);
    static constexpr frc::Color kYellowTarget = frc::Color(0.409, 0.427, 0.095);
    static constexpr frc::Color kBlueTarget = frc::Color(0.221, 0.435, 0.344); 
    static constexpr frc::Color kRedTarget = frc::Color(0.596, 0.308, 0.096);
    static constexpr frc::Color kPurpleTarget = frc::Color(0, 0, 0);
    static constexpr frc::Color kDarkGreyTileTarget = frc::Color(0, 0, 0);
    static constexpr frc::Color kLightGreyTileTarget = frc::Color(0, 0, 0);
    

    frc::Joystick *stick;
    frc::XboxController *xbox;

    //WPI_TalonSRX *spinMotor;

    rev::CANSparkMax *intakeRotateMotor;
    WPI_TalonSRX *intakeSpinMotor;

    frc::Servo *linActuator;

    rev::CANPIDController *intakePidController;

    frc::Timer *timerM;

    double xStickValue;
    std::string gameData;
    std::string currentColor;
    int colorCount;

    double encStartRot;
    double encEndRot;
    double currentEncRot;

    bool intakeButtonToggle = true;
    int rotateControlMode = 0;
    double rotatePosition;

 public:
    ManipulatorManager();
    void manualColorSpin();
    void colorFinder();
    void countSpins();
    void stopWheel();
    //void countSpinsEnc();
    void intake();
    void linearActuator();
    void intakeTest();
    void intakeStartup();
    void intakeAuto(double duration, bool outTrue);
    void intakeAutoStart();
    void intakeAutoHeight(bool sustainHeight);
    void holdIntake();
    void autoTimer(double sec);
    void stopIntake();
};