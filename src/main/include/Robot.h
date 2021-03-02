/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string> //Includes a prepopulated include (DO NOT DELETE)

#include <frc/TimedRobot.h> //Includes a prepopulated include that runs the code (DO NOT DELETE)
#include <frc/smartdashboard/SendableChooser.h> //Includes the sendable chooser include

#include <frc/WPILib.h> //Includes the WPI library for FRC

#include "frc/smartdashboard/Smartdashboard.h" //Includes the smartdashboard

#include <Manipulator.hpp>
#include <Drive.hpp>
#include <vision.hpp>
#include <Shooter.hpp>
#include <Autonomous.hpp>
#include <Climber.hpp>

extern bool intakeRotateStart;
extern bool intakeRotateStartCompleted;
extern int autoStep;
extern std::string colorString;

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  Robot();

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  ManipulatorManager *manipulatorManager;
  DriveManager *driveManager;
  VisionManager *visionManager;
  ShooterManager *shooterManager;
  ClimbManager *climbManager;
  AutoManager *autoManager;
};
