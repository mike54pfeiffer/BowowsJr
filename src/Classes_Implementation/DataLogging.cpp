#include "RobotConfiguration.h"
#include "Classes_Header/DataLogging.h"

DataLogging::DataLogging()
{
  //constructor to initiallize list alongside variables
  preRotationValue[0] = nextRotationValue[0] = prevArmRotation = 0;  
  preRotationValue[1] = nextRotationValue[1] = prevIntakeRotation = 0; 
  preRotationValue[2] = nextRotationValue[2] = prevRightBackRotation = 0; 
  preRotationValue[3] = nextRotationValue[3] = prevLeftBackRotation = 0; 
  preRotationValue[4] = nextRotationValue[4] = prevRightFrontRotation = 0; 
  preRotationValue[5] = nextRotationValue[5] = prevLeftFrontRotation = 0;
  preRotationValue[6] = nextRotationValue[6] = prevGyroDegree = 0;
}

void DataLogging::nextPosition(int armSpeed, int intakeSpeed, int driveSpeed)
{
  //declare and initiallize variables
  double rotationValue[7] = {0};
  unsigned int motorWaitTime[8] = {0};
  long double theoTime = 0;
  unsigned int additionalTime = 250;
  unsigned int slowestRotation = 0;
  enum motorGroup{ARM, INTAKE, DRIVE, GYRO, ERROR};
  motorGroup currentMotor;
  //set motor velocity
  ArmSystem.setVelocity(armSpeed, vex::velocityUnits::pct);
  IntakeSystem.setVelocity(intakeSpeed, vex::velocityUnits::pct);
  DriveSystem.setVelocity(driveSpeed, vex::velocityUnits::pct);

  //calculate the difference from previous rotation value to next rotation value
  for(int i = 0; i < 7; i++)
  {
    //calculate the distance to rotate each motor
    rotationValue[i] = nextRotationValue[i] - preRotationValue[i];

    //update previous rotation value to current rotation value
    preRotationValue[i] = nextRotationValue[i];

    //check to see which motor is being checked
    switch(i)
    {
      case 0:
      {
        currentMotor = ARM;
        break;
      }
      case 1:
      {
        currentMotor = INTAKE;
        break;
      }
      case 2:
      case 3:
      case 4:
      case 5:
      {
        currentMotor = DRIVE;
        break;
      }
      case 6:
      {
        currentMotor = GYRO;
        break;
      }
      default:
      {
        currentMotor = ERROR;
      }
    }

    //apply correct formula for the specific motor
    if(currentMotor == ARM)
    {
      theoTime = fabs((rotationValue[i] / (armSpeed * redMotor_RPM) * 6000000));
    }
    else if(currentMotor == INTAKE)
    {
      theoTime = fabs((rotationValue[i] / (intakeSpeed * redMotor_RPM) * 6000000));
    }
    else if(currentMotor == DRIVE)
    {
      theoTime = fabs((rotationValue[i] / (driveSpeed * greenMotor_RPM) * 6000000));
    }
    else
    {
      theoTime = 5000;
    }

    //round answer to nearest ones place
    motorWaitTime[i] = static_cast<int>(theoTime + 0.5);

    //add extra time to account for friction and startup lag
    motorWaitTime[i] += ((motorWaitTime[i] / 1000.0) * 125) + additionalTime; //additional time to account for statup lag
  
    //check which motor rotates the longest
    if(slowestRotation < motorWaitTime[i])
    {
      slowestRotation = motorWaitTime[i];
    }
  }

  //rotate motors all at once to the desired position
  ArmSystem.rotateFor(rotationValue[0], vex::rotationUnits::rev, false);
  IntakeSystem.rotateFor(rotationValue[1], vex::rotationUnits::rev, false);
  RightBackMotor.rotateFor(rotationValue[2], vex::rotationUnits::rev, false);
  LeftBackMotor.rotateFor(rotationValue[3], vex::rotationUnits::rev, false);
  RightFrontMotor.rotateFor(rotationValue[4], vex::rotationUnits::rev, false);
  LeftFrontMotor.rotateFor(rotationValue[5], vex::rotationUnits::rev, false);

  //wait for all motors to finish rotating
  vex::task::sleep(slowestRotation);
}

void DataLogging::skipStep()
{
  //add option to pass parameter and dertermine to replace step with other function
  return;
}

std::istream &operator>>(std::istream &input, DataLogging& log)
{
  //take input from all 8 motors and place them in the correct index in the array
  for(int i = 0; i < 8; i++)
  {
    input >> log.nextRotationValue[i];
    input.ignore(1);
  }
  return input;
}