#include "RobotConfiguration.h"
#include "Classes_Header\Bot.h"


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
void Bot::setArms(double rev, int timeout)
{
  ArmSystem.rotateTo(rev, vex::rotationUnits::rev);
}

void Bot::raiseLow(int timeout)
{
  //setArms(0.7);

}

void Bot::raiseMid(int timeout)
{
  //setArms(0.9);
}

void Bot::raiseHigh(int timeout)
{
  setArms(1.1);
}

void Bot::outtake(int timeout)
{
  
}

void Bot::moveTo(double rev, int speed, int timeout)
{
  
}

void Bot::move(double rev, int speed, int timeout)
{

}