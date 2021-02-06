#include <Autonomous.hpp>
#include <Robot.h>

AutoManager::AutoManager (DriveManager *drive, ManipulatorManager *manipulator, ShooterManager *shoot) {
    this->driveManager = drive;
    this->manipulatorManager = manipulator;
    this->shooterManager = shoot;
}

void AutoManager::testAuto() {
    switch(autoStep) {
        case 0:
            this->manipulatorManager->intakeStartup();
            break;
        case 1:
            this->driveManager->autoPrep();
            break;
        case 2:
            this->driveManager->autoBasic();
            break;
    }
    frc::SmartDashboard::PutNumber("auto step", autoStep);
}

void AutoManager::lowDeposit() {
    frc::SmartDashboard::PutNumber("auto step", autoStep);
    switch (autoStep) {
        case 0:
            this->driveManager->autoPrep();
            break;
        case 1:
            this->driveManager->autoDrive(7);
            break;
        case 2:
            this->manipulatorManager->intakeAutoHeight(false);
            break;
        case 3:
            this->manipulatorManager->intakeAutoHeight(true);
            this->manipulatorManager->intakeAutoStart();
            break;
        case 4:
            this->manipulatorManager->intakeAutoHeight(true);
            this->manipulatorManager->intakeAuto(2, true);
            break;
        case 5:
            this->manipulatorManager->intakeAutoHeight(true);
            this->driveManager->autoPrep();
            break;
        case 6:
            this->driveManager->autoDrive(-2);
            this->manipulatorManager->intakeAutoHeight(true);
            break;
        case 7:
            this->manipulatorManager->intakeStartup();
            break;
    }
}

void AutoManager::lowDepositOffset(int rightStart1) {
    frc::SmartDashboard::PutNumber("auto step", autoStep);

    switch (autoStep) {
        case 0:
            //this->manipulatorManager->intakeStartup();
            this->driveManager->zeroDrive();
            autoStep++;
            break;
        case 1:
            this->driveManager->autoPrep();
            break;
        case 2:
            this->driveManager->autoDrive(4);
            break;
        case 3:
            this->driveManager->autoPrep();
            break;
        case 4:
            this->driveManager->autoTurn(-90 * rightStart1); //-64
            this->manipulatorManager->holdIntake();
            break;
        case 5:
            this->driveManager->autoPrep();
            break;
        case 6:
            this->driveManager->autoDrive(4.4);
            break;
        case 7:
            this->driveManager->autoPrep();
            break;
        case 8:
            this->driveManager->autoTurn(90 * rightStart1); //55
            this->manipulatorManager->holdIntake();
            break;
        case 9:
            this->driveManager->autoPrep();
            break;
        case 10:
            this->driveManager->autoDrive(2.5);
            break;
        case 11:
            this->manipulatorManager->intakeAutoHeight(false);
            this->driveManager->zeroDrive();
            break;
        case 12:
            this->manipulatorManager->intakeAutoHeight(true);
            this->manipulatorManager->intakeAutoStart();
            break;
        case 13:
            this->manipulatorManager->intakeAutoHeight(true);
            this->manipulatorManager->intakeAuto(0.9, true);
            this->driveManager->zeroDrive();
            break;
        case 14:
            this->manipulatorManager->intakeAutoHeight(true);
            this->driveManager->autoPrep();
            break;
        case 15:
            this->driveManager->autoDrive(-2);
            this->manipulatorManager->intakeAutoHeight(true);
            break;
        case 16:
            this->manipulatorManager->intakeStartup();
            this->driveManager->zeroDrive();
            break;
        case 17:
            this->driveManager->zeroDrive();
            break;
    }
}

void AutoManager::lowDepositLong() {
    frc::SmartDashboard::PutNumber("auto step", autoStep);
    switch (autoStep) {
        case 0:
            this->driveManager->autoPrep();
            break;
        case 1:
            this->driveManager->autoDrive(8.5);
            break;
        case 2:
            this->manipulatorManager->intakeAutoHeight(false);
            break;
        case 3:
            this->manipulatorManager->intakeAutoHeight(true);
            this->manipulatorManager->intakeAutoStart();
            break;
        case 4:
            this->manipulatorManager->intakeAutoHeight(true);
            this->manipulatorManager->intakeAuto(2, true);
            break;
        case 5:
            this->manipulatorManager->intakeAutoHeight(true);
            this->driveManager->autoPrep();
            break;
        case 6:
            this->driveManager->autoDrive(-2);
            this->manipulatorManager->intakeAutoHeight(true);
            break;
        case 7:
            this->manipulatorManager->intakeStartup();
            break;
    }
}

void AutoManager::shootMiddle(int foward1, bool turnaround) {
    frc::SmartDashboard::PutNumber("auto step", autoStep);
    if (!turnaround && autoStep > 6 && autoStep < 10) {
        autoStep = 11;
    }

    switch(autoStep) {
    case 0:
        this->manipulatorManager->intakeStartup();
        this->driveManager->zeroDrive();
        break;
    case 1: 
        this->manipulatorManager->intakeAutoStart();
        this->driveManager->zeroDrive();
        break;
    case 2:
        this->shooterManager->shootAuto(true);
        this->driveManager->zeroDrive();
        this->manipulatorManager->autoTimer(4);
        break;
    case 3:
        this->shooterManager->stopShoot();
        break;
    case 4:
        this->driveManager->autoPrep();
        break;
    case 5:
        this->driveManager->autoDrive(3 * foward1);
        break;
    case 6:
        this->driveManager->autoPrep();
        break;
    case 7:
        this->driveManager->autoTurn(-130);
        break;
    case 8:
        this->driveManager->autoPrep();
        break;
    case 9:
        this->driveManager->autoDrive(7);
        this->manipulatorManager->intakeAuto(-1, false);
        break;
    case 10:
        this->manipulatorManager->stopIntake();
        break;
    case 11:
        this->driveManager->zeroDrive();
        break;
    }

}