#include "RobotConfiguration.h"
#include "Classes_Header/GyroSensor.h"

void GyroSensor::GyroTest()
{
  //call calibration function in gyro object
  Gyro.startCalibration();

  //run an infinite loop to have all the time to test the output of your gyro
  while(true)
  {
    //print the gyro value of degrees rotated to the brain
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(100, 100, "Gyro %f", Gyro.value(rotationUnits::deg));
    vex::task::sleep(500);
  }
}

/*---------------------------------------------------------------------------
  GyroTurn
    This function tells the robot to turn either to the right or left,
    based on gyro
    Variables:
    DegreeAmount(Degree)
    Velocity(Percentage)
    Notes:
---------------------------------------------------------------------------*/

void GyroSensor::GyroTurn(double DegreeAmount, int Velocity) {
  //call calibration function in gyro object
  Gyro.startCalibration();
  
  //wait for calibration to finish, usually 1 second
  vex::task::sleep(1000);

  //Set speeds of both Drive motors
  DriveSystem.setVelocity(Velocity, vex::velocityUnits::pct);

  //if degree amount to turn is negative, turn right
  if(DegreeAmount < 0)
  {
    //while loop to run until turn is complete
    while (Gyro.value(rotationUnits::deg) >= DegreeAmount)
    {
      //print rotation value to brain and spin
      LeftDrive.spin(directionType::fwd);  
      RightDrive.spin(directionType::rev);
    }
  }
  //if degree amount to turn is positive, turn left
  else if(DegreeAmount > 0)
  {
    //while loop to run until turn is complete
    while (Gyro.value(rotationUnits::deg) <= DegreeAmount)
    {
      //print rotation value to brain and spin
      LeftDrive.spin(directionType::rev); 
      RightDrive.spin(directionType::fwd); 
    }
  }
  //Stop motors after reached degree turn
  LeftBackMotor.stop();
  LeftFrontMotor.stop();
  RightBackMotor.stop();
  RightFrontMotor.stop();
}