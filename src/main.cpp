/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Team Xoloft                                               */
/*    Created:      9/12/19                                                   */
/*    Description:  Psuedo-Code for Friday 9/13/19                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*This code has templates for future applications*/
//


// Global Variables
#include "vex.h"
#include "RobotConfiguration.h"
#include "Bot.h"

double DriveGearDifference = 1; // The gear ratio is of 2.6 meaning a gear
                                  // reduction (3 - 2) (18 - 12) sprockets
double FinalDistance;
double WheelDiameter = 6; // in cm

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------
  Timeout

    This function allows a function to timeout just in case it fails, so
    that it can move on to the next function.

    Variables:
    Time(sec)

    Notes:

---------------------------------------------------------------------------*/

void Timeout(int Time) {
  LeftFrontMotor.setTimeout(Time, vex::timeUnits::sec);
  RightFrontMotor.setTimeout(Time, vex::timeUnits::sec);
  LeftBackMotor.setTimeout(Time, vex::timeUnits::sec);
  RightBackMotor.setTimeout(Time, vex::timeUnits::sec);
  LeftIntakeMotor.setTimeout(Time, vex::timeUnits::sec);
  RightIntakeMotor.setTimeout(Time, vex::timeUnits::sec);
  LeftArmMotor.setTimeout(Time, vex::timeUnits::sec);
  RightArmMotor.setTimeout(Time, vex::timeUnits::sec);
}

/*--------------------------------------------------------------------------
  Conversion

    This function converts the tiles that are inputed into the distance
    the robot will need to travel.

    Variables:
    Distance(Tile)

    Notes:

---------------------------------------------------------------------------*/

void Conversion(double Tiles) {
  double TileDistance = 62;

  double Distance = Tiles * TileDistance;

  double Circumference = WheelDiameter * M_PI;

  double DegreesToRotate = (360 * Distance) / Circumference;

  FinalDistance = DegreesToRotate / DriveGearDifference;
}

/*---------------------------------------------------------------------------
  Move

    This function tells the robot how far to move and whether that is
    forward or reverse.

    Variables:
    Distance(Tile)
    Velocity(Percentage)
    Time(Second)

    Notes:

---------------------------------------------------------------------------*/

void Move(double Tiles, double Velocity, int Time) {
  Timeout(Time);
  Conversion(Tiles);

  LeftFrontMotor.setVelocity(Velocity, vex::velocityUnits::pct);
  RightFrontMotor.setVelocity(Velocity, vex::velocityUnits::pct);
  LeftBackMotor.setVelocity(Velocity, vex::velocityUnits::pct);
  RightBackMotor.setVelocity(Velocity, vex::velocityUnits::pct);

  LeftFrontMotor.rotateFor(-FinalDistance, vex::rotationUnits::deg, false); // This command must be non blocking.
  RightFrontMotor.rotateFor(-FinalDistance, vex::rotationUnits::deg, false);
  LeftBackMotor.rotateFor(FinalDistance, vex::rotationUnits::deg, false);
  RightBackMotor.rotateFor(FinalDistance, vex::rotationUnits::deg );  
}

void ArmMove(int Velocity, double Revolution) {

  LeftArmMotor.setVelocity(Velocity,vex::velocityUnits::pct);
  RightArmMotor.setVelocity(Velocity,vex::velocityUnits::pct);

  LeftArmMotor.rotateFor(vex::directionType::fwd, Revolution, vex::rotationUnits::rev, false);
  RightArmMotor.rotateFor(vex::directionType::rev, Revolution, vex::rotationUnits::rev);


  LeftArmMotor.stop(brakeType::hold);
  RightArmMotor.stop(brakeType::hold);

}
void TiltMove(int Velocity, double Revolution) {

  LeftTiltMotor.setVelocity(Velocity,vex::velocityUnits::pct);
  RightTiltMotor.setVelocity(Velocity,vex::velocityUnits::pct);

  LeftTiltMotor.rotateFor(vex::directionType::fwd, Revolution, vex::rotationUnits::rev, false);
  RightTiltMotor.rotateFor(vex::directionType::rev, Revolution, vex::rotationUnits::rev);

  LeftTiltMotor.stop(brakeType::hold);
  RightTiltMotor.stop(brakeType::hold);

}
/*---------------------------------------------------------------------------
  Turn
    This function tells the robot to turn either to the right or left,
    based on distance and not gyro

    Variables:
    Distance(Tile)
    Velocity(Percentage)
    Time(Second)

    Notes:
---------------------------------------------------------------------------*/

void TurnLeft(double Tiles, double Velocity, double Time) {
  Timeout(Time);

Conversion(Tiles);               

  LeftFrontMotor.setVelocity(Velocity, vex::velocityUnits::pct);
  RightFrontMotor.setVelocity(Velocity, vex::velocityUnits::pct);
  LeftBackMotor.setVelocity(Velocity, vex::velocityUnits::pct);
  RightBackMotor.setVelocity(Velocity, vex::velocityUnits::pct);
  //LeftIntakeMotor.setVelocity(Velocity, vex::velocityUnits::pct);
  //RightIntakeMotor.setVelocity(Velocity, vex::velocityUnits::pct);

  LeftFrontMotor.rotateFor(-FinalDistance, vex::rotationUnits::deg, false); // This command must be non blocking.
  RightFrontMotor.rotateFor(-FinalDistance, vex::rotationUnits::deg, false);
  LeftBackMotor.rotateFor(FinalDistance, vex::rotationUnits::deg, false);
  RightBackMotor.rotateFor(FinalDistance, vex::rotationUnits::deg,true);
 // LeftIntakeMotor.rotateFor(FinalDistance, vex::rotationUnits::deg,true);
 // RightIntakeMotor.rotateFor(-FinalDistance, vex::rotationUnits::deg);
}

void TurnRight(double Tiles, double Velocity, double Time) {
  Timeout(Time);

  Conversion(Tiles);

  LeftFrontMotor.setVelocity(Velocity, vex::velocityUnits::pct);
  RightFrontMotor.setVelocity(Velocity, vex::velocityUnits::pct);
  LeftBackMotor.setVelocity(Velocity, vex::velocityUnits::pct);
  RightBackMotor.setVelocity(Velocity, vex::velocityUnits::pct);
 // LeftIntakeMotor.setVelocity(Velocity, vex::velocityUnits::pct);
 // RightIntakeMotor.setVelocity(Velocity, vex::velocityUnsits::pct);

  LeftFrontMotor.rotateFor(-FinalDistance, vex::rotationUnits::deg, false); // This command must be non blocking.
  RightFrontMotor.rotateFor(-FinalDistance, vex::rotationUnits::deg, false);
  LeftBackMotor.rotateFor(FinalDistance, vex::rotationUnits::deg, false);
  RightBackMotor.rotateFor(FinalDistance, vex::rotationUnits::deg, true);
  //LeftIntakeMotor.rotateFor(FinalDistance, vex::rotationUnits::deg, true);
  //RightIntakeMotor.rotateFor(-FinalDistance, vex::rotationUnits::deg);
}

/*---------------------------------------------------------------------------
  Ultrasonic RangeFinder/Sonar

    This function lets us determine our robots point from an object
    
    Variables:
    Length(mm)

    Notes:

---------------------------------------------------------------------------*/

void pneumatics(){
  //int count = 0;
  while(1){
    if(Controller1.ButtonB.pressing()){
      leftpiston.set(false);
      }
    else{
      leftpiston.set(true);
    }
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  enum Color{RED, BLUE, TEST};
  Color side = RED;
  Bot test;
  GyroSensor GyroTurn;
  LineSensor lineTracker;

  if(side == BLUE) //need to fix (only works for red side)
  {
    //pull up arms and tilt motor
    ArmMove(85,.2);
    vex::task::sleep(100);
    TiltMove(10,.2);
    LeftTiltMotor.stop(brakeType::hold);
    RightTiltMotor.stop(brakeType::hold);
    ArmMove(25,1.0);
    LeftArmMotor.stop(brakeType::hold);
    RightArmMotor.stop(brakeType::hold);
    TiltMove(10,.3);
    LeftTiltMotor.stop(brakeType::hold);
    RightTiltMotor.stop(brakeType::hold);
    vex::task::sleep(500);
    //move forward to 4 stack tower
    Move(2.5,27,3);
    //turn to face front toward tower
    GyroTurn.GyroTurn(130, 30);
    vex::task::sleep(500);
    //first push into tower and then lower arms and intake top block
    Move(.6,15, 3);
    //LeftIntakeMotor.spin(vex::directionType::rev, 20, vex::velocityUnits::pct);
    //RightIntakeMotor.spin(vex::directionType::fwd, 20, vex::velocityUnits::pct);
    //ArmMove(25,-0.15);
    LeftArmMotor.stop(brakeType::hold);
    RightArmMotor.stop(brakeType::hold);
    //LeftIntakeMotor.stop(brakeType::hold);
    //RightIntakeMotor.stop(brakeType::hold);
    vex::task::sleep(100);

    //firt turn to callibrate
    GyroTurn.GyroTurn(30,25);
    vex::task::sleep(150);
    //second push into tower
    Move(0.7,30,2);
    //second turn to callibrate
    GyroTurn.GyroTurn(-29,25);
    vex::task::sleep(150);
    //third push into tower into score
    Move(1.7,35,2);
    vex::task::sleep(150);
    //back up
    Move(-0.75, 90, 2);
    vex::task::sleep(150);
    /*
    //turn to realine
    GyroTurn.GyroTurn(-90,35);
    Move(-0.7, 50, 3);
    vex::task::sleep(150);
    //move forward toward tower
    Move(1.5, 50, 3);
    vex::task::sleep(150);
    */
  }
         
  if(side == RED)
  {
    //pull up arms and tilt motor
    ArmMove(85,.2);
    vex::task::sleep(100);
    TiltMove(10,.2);
    LeftTiltMotor.stop(brakeType::hold);
    RightTiltMotor.stop(brakeType::hold);
    ArmMove(25,1.0);
    LeftArmMotor.stop(brakeType::hold);
    RightArmMotor.stop(brakeType::hold);
    TiltMove(10,.3);
    LeftTiltMotor.stop(brakeType::hold);
    RightTiltMotor.stop(brakeType::hold);
    vex::task::sleep(500);
    //move forward to 4 stack tower
    Move(2.5,27,3);
    //turn to face front toward tower
    GyroTurn.GyroTurn(-125, 30);
    vex::task::sleep(500);
    //first push into tower and then lower arms and intake top block
    Move(.6,15, 3);
    //LeftIntakeMotor.spin(vex::directionType::rev, 20, vex::velocityUnits::pct);
    //RightIntakeMotor.spin(vex::directionType::fwd, 20, vex::velocityUnits::pct);
    //ArmMove(25,-0.15);
    LeftArmMotor.stop(brakeType::hold);
    RightArmMotor.stop(brakeType::hold);
    //LeftIntakeMotor.stop(brakeType::hold);
    //RightIntakeMotor.stop(brakeType::hold);
    vex::task::sleep(100);

    //firt turn to callibrate
    GyroTurn.GyroTurn(-35,25);
    vex::task::sleep(150);
    //second push into tower
    Move(0.5,30,2);
    //second turn to callibrate
    GyroTurn.GyroTurn(30,25);
    vex::task::sleep(150);
    //third push into tower into score
    Move(1.7,35,2);
    vex::task::sleep(150);
    //back up
    Move(-0.75, 90, 2);
    vex::task::sleep(150);
    /*
    //turn to realine
    GyroTurn.GyroTurn(90,35);
    Move(-0.7, 50, 3);
    vex::task::sleep(150);
    //move forward toward tower
    Move(1.5, 50, 3);
    vex::task::sleep(150);
    */
  }

  /*
  if(side == BLUE)
  {
    ArmMove(80,.2);
    vex::task::sleep(100);
    TiltMove(30,.4);
    LeftTiltMotor.stop(brakeType::hold);
    RightTiltMotor.stop(brakeType::hold);
    vex::task::sleep(100);
    ArmMove(25,1.1);
    LeftArmMotor.stop(brakeType::hold);
    RightArmMotor.stop(brakeType::hold);
    vex::task::sleep(500);
    Move(2,27,3);
    GyroTurn.GyroTurn(106, 35);
    vex::task::sleep(500);
    Move(.5,25, 1);
    GyroTurn.GyroTurn(11,35);
    vex::task::sleep(300);
    Move(.5,25,2);
    GyroTurn.GyroTurn(6,25);
    vex::task::sleep(100);
    Move(1.2,60,2);
    vex::task::sleep(100);
    Move(-1, 80, 2);
    GyroTurn.GyroTurn(131,35);
    Move(-1.5, 35, 2);
    TiltMove(-30,-.2);
    vex::task::sleep(500);
    ArmMove(-25,-1.3);
    LeftArmMotor.stop(brakeType::hold);
    RightArmMotor.stop(brakeType::hold);
    vex::task::sleep(500);
    Move(3, 35, 3);
    GyroTurn.GyroTurn(-145, 35);
    Move(3,65, 4);
    Move(-1,70, 2);
  }
         
  if(side == RED)
  {
    ArmMove(80,.2);
    vex::task::sleep(100);
    TiltMove(30,.5);
    LeftTiltMotor.stop(brakeType::hold);
    RightTiltMotor.stop(brakeType::hold);
    ArmMove(25,1.1);
    LeftArmMotor.stop(brakeType::hold);
    RightArmMotor.stop(brakeType::hold);
    vex::task::sleep(500);
    Move(2,27,3);
    GyroTurn.GyroTurn(-106, 35);
    vex::task::sleep(500);
    Move(.5,25, 1);
    GyroTurn.GyroTurn(-11,35);
    vex::task::sleep(300);
    Move(.5,25,2);
    GyroTurn.GyroTurn(-6,25);
    vex::task::sleep(100);
    Move(1.3,60,2);
    vex::task::sleep(100);
    Move(-1, 80, 2);
    GyroTurn.GyroTurn(-131,35);
    Move(-1.5, 35, 2);
    TiltMove(-30,-.3);
    vex::task::sleep(500);
    ArmMove(-25,-.6);
    LeftArmMotor.stop(brakeType::hold);
    RightArmMotor.stop(brakeType::hold);
    vex::task::sleep(500);
    Move(3, 35, 3);
    GyroTurn.GyroTurn(145, 35);
    Move(3,65, 4);
    Move(-1,70, 2);
  }
  */

  if(side == TEST)
  {
    TiltMove(30,.5);
    ArmMove(25,1.4);
    LeftArmMotor.stop(brakeType::hold);
    RightArmMotor.stop(brakeType::hold);
  }
}
/*---------------------------------------------------------------------------//
  TankDrive

    This function allows for tank drive in User Control Task

    Variables:

    Notes:

---------------------------------------------------------------------------*/

void TankDrive() {
  LeftFrontMotor.spin(vex::directionType::rev, Controller1.Axis3.position(),vex::velocityUnits::pct);
  RightFrontMotor.spin(vex::directionType::rev, Controller1.Axis2.position(),vex::velocityUnits::pct);
  LeftBackMotor.spin(vex::directionType::fwd, Controller1.Axis3.position(),vex::velocityUnits::pct);
  RightBackMotor.spin(vex::directionType::fwd, Controller1.Axis2.position(),vex::velocityUnits::pct);
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    //TankDrive();
    LeftBackMotor.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
    RightBackMotor.spin(vex::directionType::fwd, Controller1.Axis2.position(), vex::velocityUnits::pct);
    LeftFrontMotor.spin(vex::directionType::rev, Controller1.Axis3.position(), vex::velocityUnits::pct);
    RightFrontMotor.spin(vex::directionType::rev, Controller1.Axis2.position(), vex::velocityUnits::pct);
    if(Controller1.ButtonL2.pressing()) { 
        //...Spin the arm motor out.
        LeftIntakeMotor.spin(vex::directionType::rev, -80, vex::velocityUnits::pct);
        RightIntakeMotor.spin(vex::directionType::fwd, -80, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonR2.pressing()) { 
        //...Spin the arm motor in.
        LeftIntakeMotor.spin(vex::directionType::rev, 80, vex::velocityUnits::pct);
        RightIntakeMotor.spin(vex::directionType::fwd, 80, vex::velocityUnits::pct);
    }
      // else If the down button is pressed...
      // else If neither up or down button is pressed...
      else { 
        //...Stop the intake motor.
        LeftIntakeMotor.stop(vex::brakeType::brake);
        RightIntakeMotor.stop(vex::brakeType::brake);
      }
      if(Controller1.ButtonR1.pressing()){
      //arm system down
        LeftArmMotor.spin(vex::directionType::fwd, -35, vex::velocityUnits::pct);
        RightArmMotor.spin(vex::directionType::rev, -35, vex::velocityUnits::pct);
    
      }
      else if(Controller1.ButtonL1.pressing()){
      //arm system up
        LeftArmMotor.spin(vex::directionType::fwd, 35, vex::velocityUnits::pct);
        RightArmMotor.spin(vex::directionType::rev, 35, vex::velocityUnits::pct);
    
      }
    else{
      RightTiltMotor.stop(vex::brakeType::brake);
      LeftTiltMotor.stop(vex::brakeType::brake);
      RightArmMotor.stop(vex::brakeType::brake);
      LeftArmMotor.stop(vex::brakeType::brake);
    }
    // arm motor;
      if(Controller1.ButtonA.pressing()){
      //arms go up
        LeftTiltMotor.spin(vex::directionType::rev, 30, vex::velocityUnits::pct);
        RightTiltMotor.spin(vex::directionType::fwd, 30, vex::velocityUnits::pct);
      }
      if(Controller1.ButtonB.pressing()){
        //arms go down
        LeftTiltMotor.spin(vex::directionType::rev, -30, vex::velocityUnits::pct);
        RightTiltMotor.spin(vex::directionType::fwd, -30, vex::velocityUnits::pct);
      }
    vex::task::sleep(20); // Sleep the task for a short amount of time to
                          // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (1) {
    vex::task::sleep(100); // Sleep the task for a short amount of time to
                           // prevent wasted resources.
  }
}