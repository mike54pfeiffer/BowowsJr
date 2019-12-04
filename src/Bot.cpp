#include "RobotConfiguration.h"
#include "Bot.h"


/*---------------------------------------------------------------------------
  OutTake
>>>>>>> 33f543dbf695519be9a782527cecf03579fc3c3d

    A group of functions that allow bot to outtake blocks and backout
    
    Variables:
    TiltMotor(90 Degrees)
    Pneumatics(Pre-Set Time)

    Notes:
    Could a second gyro be added to create make the Tilt Motor easier

---------------------------------------------------------------------------*/
void Bot::outtake()
{
  double count = time(0);
  while(count != 5)
  {
    if(count != 4 && count != 5)
    {
      RightTiltMotor.spin(vex::directionType::fwd, 25, vex::velocityUnits::pct);
      LeftTiltMotor.spin(vex::directionType::fwd, 25, vex::velocityUnits::pct);
    }
    else if(count != 0 && count != 1 && count != 2 && count != 3)
    {
      Brain.Screen.printAt(1, 20, "count: %f", count);
      RightTiltMotor.stop();
      LeftTiltMotor.stop();
      leftpiston.set(false);
      LeftFrontMotor.setVelocity(50, vex::velocityUnits::pct);
      RightFrontMotor.setVelocity(50, vex::velocityUnits::pct);
      LeftBackMotor.setVelocity(50, vex::velocityUnits::pct);
      RightBackMotor.setVelocity(50, vex::velocityUnits::pct);
      LeftBackMotor.spin(directionType::rev); 
      LeftFrontMotor.spin(directionType::rev); 
      RightBackMotor.spin(directionType::rev); 
      RightFrontMotor.spin(directionType::rev);
    }
    count = time(0);
  }

    leftpiston.set(true);
    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();
}

/*---------------------------------------------------------------------------
  Parabolic Turn

    This function allows for the bot to take a parabolic path
    
    Variables:
    ******STILL NEED TO ADD*******

    Notes:

---------------------------------------------------------------------------*/

void Bot::parabolicTurn(char turnDirection, int degree)
{
  turnDirection = toupper(turnDirection);
  int counter = 0;

  LeftFrontMotor.setVelocity(50, vex::velocityUnits::pct);
  RightFrontMotor.setVelocity(50, vex::velocityUnits::pct);
  LeftBackMotor.setVelocity(50, vex::velocityUnits::pct);
  RightBackMotor.setVelocity(50, vex::velocityUnits::pct);

  Gyro.startCalibration();
  
  // wait for calibration to finish, usually 1 second
  //Set speeds of both Drive motors
    vex::task::sleep(1000);

  while(1)
  {
    if(Gyro.value(rotationUnits::deg) <= degree)
    {
      break;
    }
    counter++;  
    if(counter % 2 == 0)
    {
      LeftBackMotor.spin(directionType::fwd); 
      LeftFrontMotor.spin(directionType::fwd); 
      RightBackMotor.spin(directionType::fwd); 
      RightFrontMotor.spin(directionType::fwd);
    }
    else if(turnDirection == 'L')
    {
      LeftBackMotor.spin(directionType::rev); 
      LeftFrontMotor.spin(directionType::rev); 
      RightBackMotor.spin(directionType::fwd); 
      RightFrontMotor.spin(directionType::fwd);
    }
    else if(turnDirection == 'R')
    {
      LeftBackMotor.spin(directionType::fwd); 
      LeftFrontMotor.spin(directionType::fwd); 
      RightBackMotor.spin(directionType::rev); 
      RightFrontMotor.spin(directionType::rev);
    }
  }
}
