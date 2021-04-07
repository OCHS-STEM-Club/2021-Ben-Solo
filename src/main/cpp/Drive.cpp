#include <Drive.hpp>
#include <Robot.h>

DriveManager::DriveManager () {

    driveMotorLeft = new rev::CANSparkMax(2, rev::CANSparkMax::MotorType::kBrushless);
    driveMotorRight = new rev::CANSparkMax(3, rev::CANSparkMax::MotorType::kBrushless);

    slaveMotorLeft1 = new rev::CANSparkMax(4, rev::CANSparkMax::MotorType::kBrushless);
    slaveMotorLeft2 = new rev::CANSparkMax(5, rev::CANSparkMax::MotorType::kBrushless);
    slaveMotorRight1 = new rev::CANSparkMax(6, rev::CANSparkMax::MotorType::kBrushless);
    slaveMotorRight2 = new rev::CANSparkMax(7, rev::CANSparkMax::MotorType::kBrushless);

    slaveMotorLeft1->Follow(*driveMotorLeft, false); //follows drive motor left
    slaveMotorLeft2->Follow(*driveMotorLeft, false);
    slaveMotorRight1->Follow(*driveMotorRight, false);
    slaveMotorRight2->Follow(*driveMotorRight, false);

    driveMotorLeft->SetSmartCurrentLimit(60); //sets max current limit
    driveMotorRight->SetSmartCurrentLimit(60); //defalt is 80
    slaveMotorLeft1->SetSmartCurrentLimit(60);
    slaveMotorLeft2->SetSmartCurrentLimit(60);
    slaveMotorRight1->SetSmartCurrentLimit(60);
    slaveMotorRight2->SetSmartCurrentLimit(60);

    /*leftDriveEnc = new rev::CANEncoder(*driveMotorLeft); //creates encoder object
    rightDriveEnc = new rev::CANEncoder(*driveMotorRight);
    leftDriveEnc->SetPosition(0); //sets encoder object to 0
    rightDriveEnc->SetPosition(0);*/
    driveMotorLeft->GetEncoder().SetPosition(0);
    driveMotorRight->GetEncoder().SetPosition(0);

    robotDrive = new frc::DifferentialDrive(*driveMotorLeft, *driveMotorRight); //object holds motor cont info and does alc for that
    //stick = new frc::Joystick{0};
    xbox = new frc::XboxController{1};
    xboxDrive = new frc::XboxController{0}; //make sure to change other statements and if statements and configure creep

    autoTime = new frc::Timer();

  try {
		gyro = new AHRS(frc::SPI::Port::kMXP);
	}
	catch(std::exception ex) {
		std::string err_string = "Error initalizing navX-MXP: ";
		err_string += ex.what();
		frc::DriverStation::ReportError(err_string.c_str());
	}
	gyro->Reset();
}

int Sign(double input) { //method that returns numbers for its relation to 0
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

double deadband(double joystickValue, double deadbandValue) { //colins special proportioanl deadband thingy just copy
    if(fabs(joystickValue) < 0.2){
        return 0;
    }
    else{
        return (1 / (1 - deadbandValue)) * (joystickValue + (-Sign(joystickValue) * deadbandValue));
    } 
}

void DriveManager::drive() {
    //xStickValue = -deadband(stick->GetRawAxis(1), 0.2); //getting raw axis values
    //yStickValue = deadband(stick->GetRawAxis(2), 0.2);
    xStickValue = -xboxDrive->GetRawAxis(1);
    yStickValue = xboxDrive->GetRawAxis(4) *0.63; //.67

    /*if(stick->GetRawButton(1)){
      xStickValue *= 0.70;
      yStickValue *= 0.55;
    }*/
    if (xboxDrive->GetRawAxis(3) > 0.9) {
      xStickValue *= 0.90; //Go full speed please
      //yStickValue *= 0.67;
    }

    if (xboxDrive->GetRawAxis(2) < 0.9) {
      xStickValue *= 0.85;
      //yStickValue *= 0.67;
    }

    /*if (xboxDrive->GetRawAxis(2) > 0.9) {
      xStickValue *= 0.99;
      yStickValue *= 0.99;
    }*/

    /*if (!stick->GetRawAxis(3)) {
      xStickValue *= 0.75;
      yStickValue *= 0.6;
    }*/

    if(xbox->GetRawButton(5)){
      colorwheelExtended = false;
    }
    else if (xbox->GetRawButton(6)){
      colorwheelExtended = true;
    }

    if(colorwheelExtended){
      //xStickValue *= 0.5;
      //yStickValue *= 0.5;
    }

    /*if (stick->GetRawButton(2)) {
      xStickValue *= 0.50;
      yStickValue *= 0.45;
    }*/
    /*if (xboxDrive->GetRawButton(1)) {
      yStickValue = 0;
    }*/

    robotDrive->ArcadeDrive(xStickValue, yStickValue);

    frc::SmartDashboard::PutNumber("left encoder", driveMotorLeft->GetEncoder().GetPosition()); //getting motor controller data and putting it on smart dashboard
    frc::SmartDashboard::PutNumber("right encoder", driveMotorLeft->GetEncoder().GetPosition());
    //frc::SmartDashboard::PutNumber("left velocity", driveMotorLeft->GetEncoder().GetVelocity());
    //frc::SmartDashboard::PutNumber("right velocity", driveMotorLeft->GetEncoder().GetVelocity());

    frc::SmartDashboard::PutNumber("left current", driveMotorLeft->GetOutputCurrent());
    frc::SmartDashboard::PutNumber("right current", driveMotorRight->GetOutputCurrent());
    frc::SmartDashboard::PutNumber("left Temp", driveMotorLeft->GetMotorTemperature());
    frc::SmartDashboard::PutNumber("right Temp", driveMotorRight->GetMotorTemperature());

  /*if (stick->GetRawButton(5)) {
    gyro->Reset();
  }*/

  if (xboxDrive->GetRawButton(8)){
    gyro->Reset();
  }
  frc::SmartDashboard::PutNumber("gyro angle", gyro->GetAngle());
}

void DriveManager::subclassTurn(double turnValue, double moveValue) { //allows different subclass to access drive system to turn robot (Ex vision tracking turns robot)
    robotDrive->ArcadeDrive(moveValue, turnValue);
  //  robotDrive->ArcadeDrive(-xboxDrive->GetRawAxis(1) *0.6, turnValue);
}

double distanceToRev(double in){
  in *= 12;
  in /= 18.84;
  in *= 7.18;
  return in;
}

double clampDrive(double in,double minval,double maxval) {
  if (in > maxval) {
    return maxval;
  }
  else if (in < minval) {
    return minval;
  }
  else {
    return in;
  }
}

void DriveManager::autoPrep() {
  gyro->Reset();
  gyro->ZeroYaw();

  leftEncLast = driveMotorLeft->GetEncoder().GetPosition();
  rightEncLast = driveMotorRight->GetEncoder().GetPosition();
  gyroLast = gyro->GetAngle();

  autoStep++;

  autoTime->Reset();
  autoTime->Start();
}

void DriveManager::autoDrive(double distance){
  leftCurrentPos = driveMotorLeft->GetEncoder().GetPosition() - leftEncLast;
  rightCurrentPos = driveMotorRight->GetEncoder().GetPosition() - rightEncLast;

  revNeed = distanceToRev(distance);

  avgPosition = (leftCurrentPos - rightCurrentPos) / 2.0;
  if (distance>0) {
    offset = revNeed - avgPosition;
  }
  else if (distance<0) {
    offset = -(revNeed - avgPosition);
  }

  power = offset / (revNeed / 18.0);
  power = clampDrive(power,-0.5,0.5);

  turnCorrection = (gyro->GetAngle() - gyroLast) * TURN_K;
  robotDrive->ArcadeDrive(power, 0);

  if (offset < 0.2){
    robotDrive->ArcadeDrive(0,0);
    autoStep++;
  }
  

  /*frc::SmartDashboard::PutNumber("auto power", power);
  frc::SmartDashboard::PutNumber("offset", offset);
  frc::SmartDashboard::PutNumber("rev want", revNeed);
  frc::SmartDashboard::PutNumber("avg position", avgPosition);
  frc::SmartDashboard::PutNumber("left pos", leftCurrentPos);
  frc::SmartDashboard::PutNumber("right pos", rightCurrentPos);*/
}

void DriveManager::autoTurn(double angle) {
  turnCorrection = (angle - gyro->GetAngle()) * TURN_K;
  turnCorrection = clampDrive(turnCorrection, -0.4, 0.4);

  robotDrive->ArcadeDrive(0, turnCorrection);

  turnOffset = angle - gyro->GetAngle();

  if (turnOffset < 0) {
    turnOffset = -turnOffset;
  }

  if (turnOffset < 5) {
    robotDrive->ArcadeDrive(0,0);
    autoStep++;
  }

  frc::SmartDashboard::PutNumber("turn offset", turnOffset);
  frc::SmartDashboard::PutNumber("gyro angle", gyro->GetAngle());
}

void DriveManager::autoBasic() {
  if (autoTime->Get() < 0.5) {
    robotDrive->ArcadeDrive(0.5,0);
  }
  else {
    robotDrive->ArcadeDrive(0,0);
    autoStep++;
  }

  leftCurrentPos = driveMotorLeft->GetEncoder().GetPosition() - leftEncLast;
  rightCurrentPos = driveMotorRight->GetEncoder().GetPosition() - rightEncLast;
  //frc::SmartDashboard::PutNumber("left pos", leftCurrentPos);
  //frc::SmartDashboard::PutNumber("right pos", rightCurrentPos);
}

void DriveManager::zeroDrive() {
  robotDrive->ArcadeDrive(0,0);
}
