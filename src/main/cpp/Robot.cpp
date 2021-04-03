/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream> //Includes a prepopulated iostream include

#include <frc/smartdashboard/SmartDashboard.h>

bool intakeRotateStart = true;
int autoStep = 0;
extern std::string colorString = "";

Robot::Robot() {
  manipulatorManager = new ManipulatorManager();
  driveManager = new DriveManager();
  visionManager = new VisionManager();
  shooterManager = new ShooterManager();
  climbManager = new ClimbManager();
  autoManager = new AutoManager(driveManager, manipulatorManager, shooterManager);
}  

//frc::Joystick *stick; //Initialzing the joystick

frc::XboxController *xboxDrive;
frc::XboxController *xbox;
frc::Timer *timer;

double visionMove;
double visionTurn;
double visionRPM;

int autoSelect = 0;
void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  //stick = new frc::Joystick{0}; //Assigning the joystick to USB port 0 on the driver station
  xbox = new frc::XboxController{1};
  xboxDrive = new frc::XboxController{0};
  timer = new frc::Timer();

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  //frc::SmartDashboard::PutNumber("auto select", 0);
  //frc::SmartDashboard::PutNumber("auto delay", 0);
  frc::SmartDashboard::PutNumber("ta want", 0);
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }

  //driveManager->autoPrep();
  timer->Reset();
  timer->Start();
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
  
  autoSelect = frc::SmartDashboard::GetNumber("auto select", 0);
  if (timer->Get() > frc::SmartDashboard::GetNumber("auto delay", 0)) {
    if (autoSelect == 1) {
      autoManager->lowDeposit();
    }
    else if (autoSelect == 2) {
      autoManager->testAuto();
    }
    else if (autoSelect == 3) {
      autoManager->lowDepositOffset(1);
    }
    else if (autoSelect == 4) {
      autoManager->lowDepositOffset(-1); 
    }
    else if (autoSelect == 5) {
      autoManager->lowDepositLong();
    }
    else if (autoSelect == 6) {
      autoManager->shootMiddle(1, false);
    }
    else if (autoSelect == 7) {
      autoManager->shootMiddle(-1, true);
    }
    else if (autoSelect == 8) {
      autoManager->shootMiddle(-1, false);
    }
 
  }
  
}

void Robot::TeleopInit() {
  timer->Stop();
} //Initalize Teleop

void Robot::TeleopPeriodic() {
  //manipulatorManager->linearActuator();

  if (xbox->GetRawButton(7)) {
    //manipulatorManager->colorFinder();
  }
  else if (xbox->GetRawButton(8)) {
    //manipulatorManager->countSpins();
  }
  //else if (stick->GetRawButton(8)){
  //  manipulatorManager->countSpinsEnc();
  //}
 // else {
    manipulatorManager->manualColorSpin();
    //manipulatorManager->stopWheel();
  //}

  visionManager->display(); //runs vision manager once teleop starts
  //visionManager->distance(); //runs vision manager once teleop starts
  
  //if (!stick->GetRawButton(12) && !stick->GetRawButton(11)) {
    if (!xboxDrive->GetRawButton(5)){
		driveManager->drive();//0, 0, false);
    //shooterManager->shoot(0, false);
	}
  /*else if (stick->GetRawButton(11)) {
    visionTurn = visionManager->trackTurn();
    visionMove = visionManager->trackMove();

    driveManager->subclassTurn(visionTurn, visionMove);
  }*/
	else {
		visionTurn = visionManager->trackTurn();
    visionMove = visionManager->trackMove();
    //visionRPM = ?;

    driveManager->subclassTurn(visionTurn, visionMove);
    //driveManager->subclassTurn(visionTurn, -(0.5 * stick->GetRawAxis(1)));
    //driveManager->subclassTurn(visionTurn, 0);
    //shooterManager->shoot(visionRPM, true);
	}
  
  visionRPM = visionManager->distance();
  //driveManager->drive();
  //manipulatorManager->intakeTest();
  manipulatorManager->intake();
  shooterManager->shootTest(visionRPM);
  //climbManager->climbTest();
}

void Robot::TestPeriodic() {
  frc::SmartDashboard::PutNumber("hood position want", 86.0);
  frc::SmartDashboard::PutNumber("shoot position", 87500);
}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
