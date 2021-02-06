#include <vision.hpp>

VisionManager::VisionManager () { //Finish initionalizing
  stick = new frc::Joystick{0};
  led = new frc::AddressableLED{8};
  led->SetLength(LED_LENGTH);
  led->Start();

}

int r;
int g;
int b;
std::array<frc::AddressableLED::LEDData, LED_LENGTH> ledBuffer;
void setLED(std::string color) {
  if (color == "r") {
    r = 255;
    g = 0;
    b = 0;
  }
  else if (color == "g") {
    r = 0;
    g = 255;
    b = 0;
  }
  else if (color == "b") {
    r = 0;
    g = 0;
    b = 255;
  }
  else if (color == "y") {
    r = 255;
    g = 255;
    b = 0;
  }
  else if (color == "bl") {
    r = 0;
    g = 0;
    b = 0;
  }
  else if (color == "w") {
    r = 255;
    g = 255;
    b = 255;
  }

  for (int i = 0; i < LED_LENGTH; i++) {
    ledBuffer[i].SetRGB(r,g,b);
  }
}

void VisionManager::display() {
  std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

  table->PutNumber("pipeline", 3);
  frc::SmartDashboard::PutBoolean("has target", table->GetNumber("tv", 0.0));

  double targetOffsetAngle_Horizontal = table->GetNumber("tx",0.0);
  double targetOffsetAngle_Vertical = table->GetNumber("ty",0.0);
  double targetArea = table->GetNumber("ta",0.0);
  double targetSkew = table->GetNumber("ts",0.0);

  frc::SmartDashboard::PutNumber("tx", targetOffsetAngle_Horizontal);
  frc::SmartDashboard::PutNumber("ty", targetOffsetAngle_Vertical);
  frc::SmartDashboard::PutNumber("ta", targetArea);
  frc::SmartDashboard::PutNumber("ts", targetSkew);

  if (stick->GetRawButton(4) && imageToggle) {
    imageSwitch = !imageSwitch;
    imageToggle = false;
  }
  else if (!stick->GetRawButton(4)) {
    imageToggle = true;
  }

  if (imageSwitch) {
    table->PutNumber("camMode", 0);
    table->PutNumber("ledMode", 3);
  }
  else {
    table->PutNumber("camMode", 1);
    table->PutNumber("ledMode", 1);
  }

  if (abs(targetOffsetAngle_Horizontal) < 5 && abs(targetOffsetAngle_Vertical) < 5 && table->GetNumber("tv", 0.0)) {
    frc::SmartDashboard::PutBoolean("is alligned", true);
    setLED("g");
  }
  else if (table->GetNumber("tv", 0.0)) {
    frc::SmartDashboard::PutBoolean("is alligned", false);
    setLED("b");
  }
  else {
    frc::SmartDashboard::PutBoolean("is alligned", false);
    setLED("r");
  }

  led->SetData(ledBuffer);
}

double VisionManager::distance() {
  std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
  double targetArea = table->GetNumber("ta",0.0);

  //rawDistance = targetArea * AREADISTANCERATIO;
  //rawDistance = (targetArea * -1.31) +12.8;
  //frc::SmartDashboard::PutNumber("raw distance", rawDistance);
  //distanceFlat = sqrt(pow(rawDistance, 2) - pow(8.1875,2));
  //frc::SmartDashboard::PutNumber("target distance", distanceFlat);

  rawDistance = (targetArea * -4752.0) + 121947; //* -4752.0) + 124947
  frc::SmartDashboard::PutNumber("velocity calc", rawDistance);

  return rawDistance;
}

double clamp(double in,double minval,double maxval) {
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

double VisionManager::trackTurn() {
  std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
  double targetOffsetAngle_Horizontal = table->GetNumber("tx",0.0);
  double tv = table->GetNumber("tv",0.0);

  if (tv == 1) {
    turnOutput = targetOffsetAngle_Horizontal * STEER_K; //or divid by max value (27 degrees)
    turnOutput = clamp(turnOutput,-MAX_STEER,MAX_STEER);
    return turnOutput;
  }
  else {
    return 0;
  }
}

double VisionManager::trackMove() {
  std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
  double targetArea = table->GetNumber("ta",0.0);
  double tv = table->GetNumber("tv",0.0);

  moveWant = frc::SmartDashboard::GetNumber("ta want", 2.34);

  if (tv == 1) {
    moveOutput = (targetArea - moveWant) * DRIVE_K;
    moveOutput = clamp(moveOutput, -MAX_DRIVE,MAX_DRIVE);
    return -moveOutput;
  }
  else {
    return 0;
  }
}
