#pragma once

#include <Drive.hpp>
#include <Manipulator.hpp>
#include <Shooter.hpp>

class AutoManager { 
    private:
    DriveManager *driveManager;
    ManipulatorManager *manipulatorManager;
    ShooterManager *shooterManager;

    public:
    AutoManager(DriveManager *drive, ManipulatorManager *manipulator, ShooterManager *shoot);
    void testAuto();
    void lowDeposit();
    void lowDepositOffset(int rightStart1);
    void lowDepositLong();
    void shootMiddle(int foward1, bool turnaround);
};