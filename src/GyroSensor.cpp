#include "RobotConfiguration.h"
#include "GyroSensor.h"

void GyroSensor::GyroTest()
{
  Gyro.startCalibration();

  while(true){
  Brain.Screen.newLine();
  Brain.Screen.print(Gyro.value(rotationUnits::deg));
  Brain.Screen.print("Gyro %f");
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
  Gyro.startCalibration();
  
  // wait for calibration to finish, usually 1 second
  //Set speeds of both Drive motors
    vex::task::sleep(1000);
    LeftFrontMotor.setVelocity(Velocity, vex::velocityUnits::pct);
    RightFrontMotor.setVelocity(Velocity, vex::velocityUnits::pct);
    LeftBackMotor.setVelocity(Velocity, vex::velocityUnits::pct);
    RightBackMotor.setVelocity(Velocity, vex::velocityUnits::pct);
    Brain.Screen.clearScreen();
    Brain.Screen.print(Gyro.value(rotationUnits::deg));
    //While loop to do the spin
     if(DegreeAmount > 0)
    {
      while (Gyro.value(rotationUnits::deg) <= DegreeAmount)
      {
        Brain.Screen.printAt( 10, 50, "Gyro %f", Gyro.value( rotationUnits::deg ) );
        LeftBackMotor.spin(directionType::fwd); 
        LeftFrontMotor.spin(directionType::rev); 
        RightBackMotor.spin(directionType::rev); 
        RightFrontMotor.spin(directionType::fwd);
      }
    }
    else if(DegreeAmount < 0)
    {
      while (Gyro.value(rotationUnits::deg) >= DegreeAmount)
      {
        Brain.Screen.printAt( 10, 50, "Gyro %f", Gyro.value( rotationUnits::deg ) );
        LeftBackMotor.spin(directionType::rev); 
        LeftFrontMotor.spin(directionType::fwd); 
        RightBackMotor.spin(directionType::fwd); 
        RightFrontMotor.spin(directionType::rev);
      }
    }
    //Stop motors after reached degree turn
    LeftBackMotor.stop();
    LeftFrontMotor.stop();
    RightBackMotor.stop();
    RightFrontMotor.stop();
}