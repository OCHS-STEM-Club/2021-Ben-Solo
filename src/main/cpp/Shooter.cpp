#include <Shooter.hpp>
#include <Robot.h>

ShooterManager::ShooterManager () {
    shootMotor = new WPI_TalonSRX(12);
    //shootMotor->GetSensorCollection().SetQuadraturePosition(0, 10);
    shootMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
    shootMotor->SetSensorPhase(false);
	shootMotor->SetInverted(false);
	//shootMotor->ConfigAllowableClosedloopError(0, 0, 10);
	shootMotor->Config_kP(0, 0.06, 10); //0.04
	shootMotor->Config_kI(0, 0.0, 10); //0.04
	shootMotor->Config_kD(0, 0.001, 10); //0.001
    shootMotor->SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Coast);
    shootMotor->ConfigPeakOutputForward(0, 10);
    shootMotor->ConfigClosedloopRamp(1, 10);
    

    hoodMotor = new WPI_TalonSRX(14);

    feederMotor = new WPI_TalonSRX(13);
    xbox = new frc::XboxController{1};
    //hoodEncoder = new frc::DigitalInput(0);
    //currentEncoderState = hoodEncoder->Get();
    //hoodCount = new frc::Counter(hoodEncoder);

    hoodPotent = new frc::AnalogPotentiometer(1, 1000, 0); //3600
}

void ShooterManager::shoot(double velocityIn, double enabled) {
    velocityAct = shootMotor->GetSensorCollection().GetQuadratureVelocity();
    frc::SmartDashboard::PutNumber("shooter velocity", velocityAct);

    if (xbox->GetRawButton(4)) {
        velocityWant = velocityIn;
        if (0 != frc::SmartDashboard::GetNumber("shoot position", 0)) {
            velocityWant = frc::SmartDashboard::GetNumber("shoot position", 0);
        }
        shootMotor->Set(ControlMode::Velocity, -velocityWant); //replace 0 with correct
    }
    else if (xbox->GetRawButton(3)) {
        shootMotor->Set(0);
    }

    /*if ((velocityAct - velocityIn) < 20 && xbox->GetRawButton(12) ) { //fix button later and allowable error
        feederMotor->Set(0.2);
    }*/
    if (xbox->GetPOV() == 0) { //fix button later
        feederMotor->Set(-0.8);
    }
    else {
        feederMotor->Set(0); 
    }
}

void ShooterManager::hoodRotate(double hoodPositionWant){
    /*if (currentEncoderState != hoodEncoder->Get()){
        if (hoodMotor->Get() > 0){
            hoodEncoderCount++;
        }
        else {
            hoodEncoderCount--;
        }
        currentEncoderState = hoodEncoder->Get();
    }*/
    
    hoodPosition = hoodPotent->Get();
    hoodMotor->Set((hoodPositionWant -hoodPosition) * 0.05);
}

void ShooterManager::shootTest(double in) {


    //hoodMotor->Set(xbox->GetRawAxis(1));
    if (xbox->GetRawAxis(2) > 0.9) {
        hoodMotor->Set(0.5);
    }
    else if (xbox->GetRawAxis(3) > 0.9) {
        hoodMotor->Set(-0.5);
    }
    else {
        hoodMotor->Set(0);
    }

    frc::SmartDashboard::PutNumber("hood position", hoodPotent->Get());

    velocityWant = frc::SmartDashboard::GetNumber("shoot position", 87500); //97000

    if (xbox->GetRawButton(4)) {
       //shootMotor->Set((velocityWant * 1.0) / -120000.0);
       shootMotor->Set(ControlMode::Velocity, -velocityWant);
    }
    else if (xbox->GetRawButton(8)) {
        shootMotor->Set(ControlMode::Velocity, -in);
    }
    else if (xbox->GetRawButton(3)) {
        shootMotor->Set(1.1 * xbox->GetRawAxis(1));
    }

    //frc::SmartDashboard::PutNumber("shooter temp", shootMotor->GetTemperature());
    frc::SmartDashboard::PutNumber("shooter velocity", shootMotor->GetSensorCollection().GetQuadratureVelocity());
    //frc::SmartDashboard::PutNumber("shoot position", shootMotor->GetSensorCollection().GetQuadraturePosition());
    frc::SmartDashboard::PutNumber("shoot power", shootMotor->Get());
    frc::SmartDashboard::PutNumber("shoot voltage", -shootMotor->GetMotorOutputVoltage());
    frc::SmartDashboard::PutNumber("shooter current", shootMotor->GetOutputCurrent());
    

    /*if (100000 > -shootMotor->GetSensorCollection().GetQuadratureVelocity()) {
        frc::SmartDashboard::PutBoolean("shoot ready", false);
        feederMotor->Set(0);
    }
    else {
        frc::SmartDashboard::PutBoolean("shoot ready", true);

        if (xbox->GetRawButton(4)) { //fix button later
            //feederMotor->Set(0.8);
        }
        if (xbox->GetRawButton(3)) {
            feederMotor->Set(-0.8);
        }
        else {
            feederMotor->Set(0);
        }
    }*/

    if (xbox->GetPOV() == 0) {
        feederMotor->Set(-0.8);
    }
    else {
        feederMotor->Set(0);
    }
}

void ShooterManager::shootAuto(bool doShoot) {
    shootMotor->Set((88000 * 1.0) / -120000.0);

    velocityAct = -shootMotor->GetSensorCollection().GetQuadratureVelocity();
    if (velocityAct > 89000 && doShoot) {
        feederMotor->Set(-0.8);
    }
    else {
        feederMotor->Set(0);
    }

    frc::SmartDashboard::PutNumber("shooter velocity", shootMotor->GetSensorCollection().GetQuadratureVelocity());
}

void ShooterManager::stopShoot() {
    shootMotor->Set(0);
    feederMotor->Set(0);
    autoStep++;
}