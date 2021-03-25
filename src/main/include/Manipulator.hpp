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
    /*static constexpr frc::Color BLUE_TARGET = frc::Color(0.143, 0.427, 0.429); //defult colors given by first
    static constexpr frc::Color GREEN_TARGET = frc::Color(0.197, 0.561, 0.240);
    static constexpr frc::Color RED_TARGET = frc::Color(0.561, 0.232, 0.114);
    static constexpr frc::Color YELLOW_TARGET = frc::Color(0.361, 0.524, 0.113); */

    static constexpr frc::Color GREEN_TARGET = frc::Color(0.186, 0.531, 0.282);
    static constexpr frc::Color YELLOW_TARGET = frc::Color(0.330, 0.540, 0.130);
    static constexpr frc::Color BLUE_TARGET = frc::Color(0.216, 0.434, 0.349); 
    static constexpr frc::Color RED_TARGET = frc::Color(0.453, 0.381, 0.175);
    static constexpr frc::Color PURPLE_TARGET = frc::Color(0.333, 0.359, 0.307);
    static constexpr frc::Color DARKGREY_TARGET = frc::Color(0, 0, 0);
    static constexpr frc::Color LIGHTGREY_TARGET = frc::Color(0, 0, 0);
    

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