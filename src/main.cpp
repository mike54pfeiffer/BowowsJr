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

void ArmMove() {

  LeftArmMotor.setVelocity(50,vex::velocityUnits::pct);
  RightArmMotor.setVelocity(50,vex::velocityUnits::pct);

  LeftArmMotor.rotateFor(vex::directionType::fwd, 1.4, vex::rotationUnits::rev, false);
  RightArmMotor.rotateFor(vex::directionType::rev, 1.4, vex::rotationUnits::rev);

  LeftArmMotor.stop(brakeType::hold);
  RightArmMotor.stop(brakeType::hold);

}
void TiltMove() {
  Timeout(1);

  LeftTiltMotor.setVelocity(50,vex::velocityUnits::pct);
  RightTiltMotor.setVelocity(50,vex::velocityUnits::pct);

  LeftTiltMotor.rotateFor(vex::directionType::fwd, .5, vex::rotationUnits::rev, false);
  RightTiltMotor.rotateFor(vex::directionType::rev, .5, vex::rotationUnits::rev);


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
/*---------------------------------------------------------------------------
  Intake

    This function starts the intake to be able to take in a cube or drop it
    
    Variables:
    Varient(1, 2, 3, or 4) 
     1- pickup  
     2- drop 
     3- intake while going forward (experimental)
     4- drop while going reverse  (experimental)

    Notes:

---------------------------------------------------------------------------*/

void Intake2 (int rot) {
  LeftIntakeMotor.setVelocity (60 *rot, vex::velocityUnits::pct);
    RightIntakeMotor.setVelocity(-60 *rot, vex::velocityUnits::pct);

    LeftIntakeMotor.spinFor(.25, vex::timeUnits::sec);
    RightIntakeMotor.spinFor(.25, vex::timeUnits::sec);
}


void Intake(int Varient) {
  double Velocity = 50;
  switch (Varient) {
  case 1:         // This case will only turn the intake motor forward
    Timeout(1);

    LeftIntakeMotor.setVelocity (60, vex::velocityUnits::pct);
    RightIntakeMotor.setVelocity(-60, vex::velocityUnits::pct);

    LeftIntakeMotor.spinFor(1, vex::timeUnits::sec);
    RightIntakeMotor.spinFor(1, vex::timeUnits::sec);
    break;

  case 2:         // This case will only turn the intake motor reverse
    Timeout(1);

    LeftIntakeMotor.setVelocity (-60, vex::velocityUnits::pct);
    RightIntakeMotor.setVelocity(60, vex::velocityUnits::pct);

    LeftIntakeMotor.spinFor(.25, vex::timeUnits::sec);
    RightIntakeMotor.spinFor(.25, vex::timeUnits::sec);
    break;

  case 3:         // This case will only turn the intake motor forward while moving forward (experimental)
    Timeout(1);

    LeftFrontMotor.setVelocity(Velocity, vex::velocityUnits::pct);
    RightFrontMotor.setVelocity(Velocity, vex::velocityUnits::pct);
    LeftBackMotor.setVelocity(Velocity, vex::velocityUnits::pct);
    RightBackMotor.setVelocity(Velocity, vex::velocityUnits::pct);
    LeftIntakeMotor.setVelocity (60, vex::velocityUnits::pct);
    RightIntakeMotor.setVelocity(-60, vex::velocityUnits::pct);

    LeftFrontMotor.spinFor(.25, vex::timeUnits::sec); 
    RightFrontMotor.spinFor(.25, vex::timeUnits::sec);
    LeftBackMotor.spinFor(.25, vex::timeUnits::sec);
    RightBackMotor.spinFor(.25, vex::timeUnits::sec);
    LeftIntakeMotor.spinFor(.30, vex::timeUnits::sec);
    RightIntakeMotor.spinFor(.30, vex::timeUnits::sec);

    break;

  case 4:         // This case will only turn the intake motor reverse while moving reverse (experimental)
    Timeout(1);

    LeftFrontMotor.setVelocity(-Velocity, vex::velocityUnits::pct);
    RightFrontMotor.setVelocity(-Velocity, vex::velocityUnits::pct);
    LeftBackMotor.setVelocity(-Velocity, vex::velocityUnits::pct);
    RightBackMotor.setVelocity(-Velocity, vex::velocityUnits::pct);
    LeftIntakeMotor.setVelocity (-60, vex::velocityUnits::pct);
    RightIntakeMotor.setVelocity(60, vex::velocityUnits::pct);

    LeftFrontMotor.spinFor(.25, vex::timeUnits::sec); 
    RightFrontMotor.spinFor(.25, vex::timeUnits::sec);
    LeftBackMotor.spinFor(.25, vex::timeUnits::sec);
    RightBackMotor.spinFor(.25, vex::timeUnits::sec);
    LeftIntakeMotor.spinFor(.30, vex::timeUnits::sec);
    RightIntakeMotor.spinFor(.30, vex::timeUnits::sec);

    break;
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
  enum Color{RED, BLUE, TEST, BS};
  Color side = BLUE;
  Bot test;
  GyroSensor GyroTurn;
  LineSensor lineTracker;

  if(side == BLUE)
  {
    TiltMove();
    LeftTiltMotor.stop(brakeType::hold);
    RightTiltMotor.stop(brakeType::hold);
    vex::task::sleep(100);
    ArmMove();
    LeftArmMotor.stop(brakeType::hold);
    RightArmMotor.stop(brakeType::hold);
    Move(2,30,3);
    GyroTurn.GyroTurn(135, 35);
    Move(3, 90, 5);
    Move(-1, 80, 2);
    GyroTurn.GyroTurn(125,35);
    Move(-2, 35, 3);
    Move(3, 35, 3);
    GyroTurn.GyroTurn(-145, 35);
    Move(3, 50, 4);
    Move(-1,70, 2);
  }
         
  if(side == RED)
  {
    TiltMove();
    ArmMove();
    LeftArmMotor.stop(brakeType::hold);
   RightArmMotor.stop(brakeType::hold);
    Move(2,28,3 );
    GyroTurn.GyroTurn(-126, 35);
    Move(3, 50, 5);
    Move(-1.1, 70, 2);
    GyroTurn.GyroTurn(-113,35);
    Move(-2, 35, 3);
    Move(3, 35, 3);
    GyroTurn.GyroTurn(155, 35);
    Move(3,50,4);
    Move(-2,50, 2);
  }

  if(side == TEST)
  {
    TiltMove();
    ArmMove();
    LeftArmMotor.stop(brakeType::hold);
    RightArmMotor.stop(brakeType::hold);
  }
  if(side == BS)
  {
    Move(1.5,25,3);
    Move(-2, 35, 3);
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
        LeftArmMotor.spin(vex::directionType::fwd, -50, vex::velocityUnits::pct);
        RightArmMotor.spin(vex::directionType::rev, -50, vex::velocityUnits::pct);
    
      }
      else if(Controller1.ButtonL1.pressing()){
      //arm system up
        LeftArmMotor.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
        RightArmMotor.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
    
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