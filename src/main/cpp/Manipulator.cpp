#include <Manipulator.hpp>
#include <Robot.h>

ManipulatorManager::ManipulatorManager () {
  m_colorMatcher.AddColorMatch(kBlueTarget);
  m_colorMatcher.AddColorMatch(kGreenTarget);
  m_colorMatcher.AddColorMatch(kRedTarget);
  m_colorMatcher.AddColorMatch(kYellowTarget);

  stick = new frc::Joystick{0};
  xbox = new frc::XboxController{1};

  //spinMotor = new WPI_TalonSRX(8);
  //spinMotor->GetSensorCollection().SetQuadraturePosition(0, 10);

  intakeRotateMotor = new rev::CANSparkMax(10, rev::CANSparkMax::MotorType::kBrushless);
  intakeRotateMotor->GetEncoder().SetPosition(0);

  intakeSpinMotor = new WPI_TalonSRX(11);

  currentColor = " ";
  colorCount = 0;
  encStartRot = 0;

  linActuator = new frc::Servo(2);
  linActuator->SetBounds(2.0, 1.8, 1.0, 1.2, 1.0);

  intakePidController = new rev::CANPIDController(*intakeRotateMotor);
  intakePidController->SetP(0);
  intakePidController->SetI(0);
  intakePidController->SetD(0);
  //intakePidController->SetIZone(0);
  //intakePidController->SetFF(0);
  intakePidController->SetOutputRange(1,-1);

  timerM = new frc::Timer();
	//timer->Start();
}

double absDoubleM (double x) { //method that takes a varible and gets the absolute value of it
  if (x < 0) {
    return -x;
  }
  else {
    return x;
  }
}

int SignM(double input) {
    if (input > 0) {
        return 1;
    }
    else if (input < 0) {
        return -1;
    }
    else if (input == 0) {
        return 0;
    }
}

double deadbandM(double joystickValue, double deadbandValue) {
    if(absDoubleM(joystickValue) < 0.1){
        return 0;
    }
    else{
        return (1 / (1 - deadbandValue)) * (joystickValue + (-SignM(joystickValue) * deadbandValue));
    } 
}

void ManipulatorManager::manualColorSpin() {
    xStickValue = stick->GetRawAxis(5);
    //xStickValue = deadband(xStickValue,0.5);

    //spinMotor->Set(xStickValue);
    //aq  frc::SmartDashboard::PutNumber("spin motor roations", spinMotor->GetSensorCollection().GetQuadraturePosition() / 4096.0);


    frc::Color detectedColor = m_colorSensor.GetColor();


  std::string colorString;
  double confidence = 0.0;
  frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

  if (matchedColor == kBlueTarget) {
    colorString = "Blue";
  } else if (matchedColor == kRedTarget) {
    colorString = "Red";
  } else if (matchedColor == kGreenTarget) {
    colorString = "Green";
  } else if (matchedColor == kYellowTarget) {
    colorString = "Yellow";
  } else {
    colorString = "Unknown";
  }


  frc::SmartDashboard::PutNumber("Red", detectedColor.red);
  frc::SmartDashboard::PutNumber("Green", detectedColor.green);
  frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
  frc::SmartDashboard::PutNumber("Confidence", confidence);
  frc::SmartDashboard::PutString("Detected Color", colorString);
}

/*void ManipulatorManager::colorFinder() {
  gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
  frc::SmartDashboard::PutString("colorToFind", gameData);

  frc::Color detectedColor = m_colorSensor.GetColor();


  std::string colorString;
  double confidence = 0.0;
  frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

  if (matchedColor == kBlueTarget) {
    colorString = "R";
  } else if (matchedColor == kRedTarget) {
    colorString = "B";
  } else if (matchedColor == kGreenTarget) {
    colorString = "Y";
  } else if (matchedColor == kYellowTarget) {
    colorString = "G";
  } else {
    colorString = "Unknown";
  } 

  frc::SmartDashboard::PutString("Detected Color", colorString);

  if (colorString != gameData) {
    spinMotor->Set(0.225);
  }
  else {
    spinMotor->Set(0);
  }
  
}

void ManipulatorManager::countSpins() {

  frc::Color detectedColor = m_colorSensor.GetColor();

  std::string colorString;
  double confidence = 0.0;
  frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

  if (matchedColor == kBlueTarget) {
    colorString = "B";
  } else if (matchedColor == kRedTarget) {
    colorString = "R";
  } else if (matchedColor == kGreenTarget) {
    colorString = "G";
  } else if (matchedColor == kYellowTarget) {
    colorString = "Y";
  } else {
    colorString = "Unknown";
  }

  if (currentColor != colorString) {
    currentColor = colorString;
    if (currentColor == "R") {
      colorCount++;
    }
  }

  if (xbox->GetRawButton(10)) {
    colorCount = 0;
  }

  if (colorCount < 7) {
    spinMotor->Set(0.6);
  }
  else {
    spinMotor->Set(0);
  }

  frc::SmartDashboard::PutString("Detected Color", colorString);
}

void ManipulatorManager::stopWheel() {
  spinMotor->Set(0);
}*/

/*void ManipulatorManager::countSpinsEnc(){
  currentEncRot = spinMotor->GetSensorCollection().GetQuadraturePosition() / 4096.0;
  frc::SmartDashboard::PutNumber("spin motor roations", currentEncRot);

  if (stick->GetRawButton(9)){ //sets start and end values
    encStartRot = currentEncRot;
    encEndRot = encStartRot + (3.5 * (1/COLORWHEELRATIO));
  }

  if (currentEncRot < encEndRot){
    spinMotor->Set(-0.2);
  }
  else {
    spinMotor->Set(0);
  }
}*/

void ManipulatorManager::intake() {
  //intakeSpinMotor->Set(deadbandM(xbox->GetRawAxis(1), 0.2));
  if (xbox->GetRawButton(1)) {
    intakeSpinMotor->Set(-0.8);
  }
  else if (xbox->GetRawButton(2)) {
    intakeSpinMotor->Set(0.8);
  }
  else {
    intakeSpinMotor->Set(0);
  }

  if (xbox->GetPOV() == 0 && intakeButtonToggle) {
    //rotateControlMode = 1;
    //intakePidController->SetReference(0, rev::ControlType::kPosition);
  }
  else if (xbox->GetPOV() == 180 && intakeButtonToggle) {
    //intakePidController->SetReference(0, rev::ControlType::kPosition);
    //intakeRotateMotor->StopMotor();
    rotateControlMode = 2;
  }
  else if (xbox->GetPOV() == 270 && intakeButtonToggle) {
    rotateControlMode = 3;
  }
    else if (xbox->GetPOV() == 90 && intakeButtonToggle) {
    rotateControlMode = 4;
  }
  else {
    intakeButtonToggle = true;
  }
  
  rotatePosition = intakeRotateMotor->GetEncoder().GetPosition();
  if (rotateControlMode == 1) {
    //intakeRotateMotor->Set(-0.01);
    if (rotatePosition > LOW_GOAL_HEIGHT) {
      intakeRotateMotor->Set(-0.022);
    }
    else if (rotatePosition < (LOW_GOAL_HEIGHT - 0.4)){
      intakeRotateMotor->Set(0.03);
    }
  }
  if (rotateControlMode == 2) {
    if (rotatePosition < 42 && rotatePosition > 20) { //replace 0 with desired location
      intakeRotateMotor->Set(-0.00005);
    }
    else if (rotatePosition < 16) {
      intakeRotateMotor->Set(0.04);
    }
    else if (rotatePosition < 19) {
      intakeRotateMotor->Set(-0.000);
    }
    else {
      intakeRotateMotor->Set(0);
    }
  }
  if (rotateControlMode == 3) {
    /*if (rotatePosition > 45 && xbox->GetRawAxis(5) > 0) {
      intakeRotateMotor->Set(0);
    }
    else {
      intakeRotateMotor->Set(xbox->GetRawAxis(5) * 0.25);
    }*/
    if (rotatePosition > 14) {
      intakeRotateMotor->Set(-0.19);
    }
    else {
      intakeRotateMotor->Set(-0.16);
    }
    

    if (rotatePosition < LOW_GOAL_HEIGHT) {
      rotateControlMode = 1;
    }
  }
  if (rotateControlMode == 4) {
    intakeRotateMotor->Set(xbox->GetRawAxis(5) * 0.4);
  }

  frc::SmartDashboard::PutNumber("intake rotate encoder", intakeRotateMotor->GetEncoder().GetPosition());
  frc::SmartDashboard::PutNumber("intake rotate power", intakeRotateMotor->Get());
  frc::SmartDashboard::PutNumber("intake rotate current", intakeRotateMotor->GetOutputCurrent());
  frc::SmartDashboard::PutNumber("intake rotate temp", intakeRotateMotor->GetMotorTemperature());
  frc::SmartDashboard::PutNumber("rotate control mode", rotateControlMode);
}

void ManipulatorManager::linearActuator() {
  if (xbox->GetRawButton(5)) {
    //linActuator->SetSpeed(1);
    linActuator->SetPosition(0);
  }
  else if (xbox->GetRawButton(6)) {
    //linActuator->SetSpeed(-1);
    linActuator->SetPosition(0.65);
  }
  //else {
    //linActuator->SetSpeed(0);
    //linActuator->SetDisabled();
  //}
}

void ManipulatorManager::intakeTest() {
  intakeSpinMotor->Set(0.5 * deadbandM(xbox->GetRawAxis(1), 0.2));
  frc::SmartDashboard::PutNumber("intake percent", intakeSpinMotor->Get());

  intakeRotateMotor->Set(deadbandM(xbox->GetRawAxis(5), 0.2));
  frc::SmartDashboard::PutNumber("intake rotate encoder", intakeRotateMotor->GetEncoder().GetPosition());
  frc::SmartDashboard::PutNumber("intake rotate power", intakeRotateMotor->Get());
  frc::SmartDashboard::PutNumber("intake rotate current", intakeRotateMotor->GetOutputCurrent());
  frc::SmartDashboard::PutNumber("intake rotate temp", intakeRotateMotor->GetMotorTemperature());
}

void ManipulatorManager::intakeStartup() {

    rotatePosition = intakeRotateMotor->GetEncoder().GetPosition();
    if (rotatePosition < 42 && rotatePosition > 22) { //replace 0 with desired location
      intakeRotateMotor->Set(-0.00005);
    }
    else if (rotatePosition > -1 && rotatePosition < 15) {
      intakeRotateMotor->Set(0.08);
    }
    else if (rotatePosition < 20) {
      intakeRotateMotor->Set(-0.000);
    }
    else {
      intakeRotateMotor->Set(0);
    }

    if (rotatePosition > 42) {
      autoStep++;
    }

      frc::SmartDashboard::PutNumber("intake rotate encoder", intakeRotateMotor->GetEncoder().GetPosition());
  frc::SmartDashboard::PutNumber("intake rotate power", intakeRotateMotor->Get());
  frc::SmartDashboard::PutNumber("intake rotate current", intakeRotateMotor->GetOutputCurrent());
  frc::SmartDashboard::PutNumber("intake rotate temp", intakeRotateMotor->GetMotorTemperature());
}

void ManipulatorManager::intakeAutoStart() {
  timerM->Reset();
  timerM->Start();
  autoStep++;
}

void ManipulatorManager::intakeAuto(double duration, bool outTrue) {
  if (outTrue && (duration > timerM->Get() || duration == -1)) {
    intakeSpinMotor->Set(0.8);
  }
  else if (!outTrue && (duration > timerM->Get() || duration == -1)) {
    intakeSpinMotor->Set(-0.8);
  }
  else {
    intakeSpinMotor->Set(0);
    autoStep++;
  }
}

void ManipulatorManager::intakeAutoHeight(bool sustainHeight) {
  rotatePosition = intakeRotateMotor->GetEncoder().GetPosition();
  if (!sustainHeight) {
    if (rotatePosition > LOW_GOAL_HEIGHT) {
      intakeRotateMotor->Set(-0.022);
    }
    else if (rotatePosition < (LOW_GOAL_HEIGHT - 0.3)){
      intakeRotateMotor->Set(0.08);
    }
  }

  if ((rotatePosition > LOW_GOAL_HEIGHT) && !sustainHeight) {
    autoStep++;
  }

  if (sustainHeight) {
    if (rotatePosition > LOW_GOAL_HEIGHT) {
      intakeRotateMotor->Set(-0.022);
    }
    else if (rotatePosition < (LOW_GOAL_HEIGHT - 0.4)){
      intakeRotateMotor->Set(0.03);
    }
  }
}

void ManipulatorManager::holdIntake() {
  intakeRotateMotor->Set(-0.00005);
}

void ManipulatorManager::autoTimer(double sec) {
  if (timerM->Get() > sec) {
    autoStep++;
  }
}

void ManipulatorManager::stopIntake() {
  intakeSpinMotor->Set(0);
  autoStep++;
}