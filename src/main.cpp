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
#include "VisionSensor.h"

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

void Move(double Tiles, double Velocity, int Time, double Intake) {
  Timeout(Time);
  Conversion(Tiles);

    if(Intake == 1){

    LeftIntakeMotor.spin(vex::directionType::fwd, 90, vex::velocityUnits::pct);
    RightIntakeMotor.spin(vex::directionType::rev, 90, vex::velocityUnits::pct);
  }
   else{
    LeftIntakeMotor.stop(brakeType::hold);
    RightIntakeMotor.stop(brakeType::hold);
  }

  LeftFrontMotor.setVelocity(Velocity, vex::velocityUnits::pct);
  RightFrontMotor.setVelocity(Velocity, vex::velocityUnits::pct);
  LeftBackMotor.setVelocity(Velocity, vex::velocityUnits::pct);
  RightBackMotor.setVelocity(Velocity, vex::velocityUnits::pct);

  LeftFrontMotor.rotateFor(-FinalDistance, vex::rotationUnits::deg, false); // This command must be non blocking.
  RightFrontMotor.rotateFor(-FinalDistance, vex::rotationUnits::deg, false);
  LeftBackMotor.rotateFor(FinalDistance, vex::rotationUnits::deg, false);
  RightBackMotor.rotateFor(FinalDistance, vex::rotationUnits::deg );  


}

void ArmMove(int Velocity, double Revolution, int time) {
  Timeout(time);
  LeftArmMotor.setVelocity(Velocity,vex::velocityUnits::pct);
  RightArmMotor.setVelocity(Velocity,vex::velocityUnits::pct);

  LeftArmMotor.rotateFor(vex::directionType::fwd, Revolution, vex::rotationUnits::rev, false);
  RightArmMotor.rotateFor(vex::directionType::rev, Revolution, vex::rotationUnits::rev);

  LeftArmMotor.stop(brakeType::hold);
  RightArmMotor.stop(brakeType::hold);

}
void TiltMove(int Velocity, double Revolution, int time) {
  Timeout(time);
  LeftTiltMotor.setVelocity(Velocity,vex::velocityUnits::pct);
  RightTiltMotor.setVelocity(Velocity,vex::velocityUnits::pct);

  LeftTiltMotor.rotateFor(vex::directionType::fwd, Revolution, vex::rotationUnits::rev, false);
  RightTiltMotor.rotateFor(vex::directionType::rev, Revolution, vex::rotationUnits::rev);

  LeftTiltMotor.stop(brakeType::hold);
  RightTiltMotor.stop(brakeType::hold);
 
}

void Intake(double Velocity, double Revolution, int time){
  Timeout(time);

    LeftIntakeMotor.setVelocity(Velocity, vex::velocityUnits::pct);
    RightIntakeMotor.setVelocity(Velocity, vex::velocityUnits::pct);

    LeftIntakeMotor.rotateFor(vex::directionType::rev, Revolution, vex::rotationUnits::rev, false);
    RightIntakeMotor.rotateFor(vex::directionType::fwd, Revolution, vex::rotationUnits::rev);


    LeftIntakeMotor.stop(brakeType::hold);
    RightIntakeMotor.stop(brakeType::hold);

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
  enum Color{RED, BLUE, SKILLS, TEST};
  Color side = TEST;

  Bot test;
  GyroSensor GyroTurn;
  LineSensor lineTracker;

  LeftArmMotor.resetRotation();
  RightArmMotor.resetRotation();

  if(side == BLUE)
  {
    //wait for teammate to run set up
    vex::task::sleep(3000);
    //move forward to 4 stack tower
    Move(-1.1, 20, 5, 0);
    LeftFrontMotor.stop(vex::brakeType::hold);
    RightFrontMotor.stop(vex::brakeType::hold);
    LeftBackMotor.stop(vex::brakeType::hold);
    RightBackMotor.stop(vex::brakeType::hold);
    //turn to face back toward tower
    GyroTurn.GyroTurn(94, 25);
    vex::task::sleep(100);
    //release intake system and push left side tower
    ArmMove(100,-.3, 2);
    vex::task::sleep(100);
    ArmMove(-85,.4, 2);
    vex::task::sleep(500);
    //move back to line up cube to intake
    Move(-.1,30, 1, 0);
    vex::task::sleep(250);
    //move forward to intake cube 
    Move(.4,35,1, 1);
    //move around tower to get a straight push into the 
    GyroTurn.GyroTurn(-30,30);
    Move(-.4,25,2, 0);
    GyroTurn.GyroTurn(68,25);
    vex::task::sleep(150);

    //push into tower
    Move(-0.3, 80, 2, 0);
    vex::task::sleep(500);
    Move(-4, 75, 2, 0);
    //move out of score zone
    Move(1,50, 2, 0);
    //face middle tower
    GyroTurn.GyroTurn(-95, 30);
    //go to tower
    Move(1, 30, 3, 0);
    //move arms up
    ArmMove(40, -1.3, 3);
    //score high
    Intake(-80, 2 ,1);
    //////////////////////////////
    /*
    //turn to face tower
    GyroTurn.GyroTurn(64,35);
    vex::task::sleep(100);
    ArmMove(40, -1.2);
    //move toward tower
    Move(.1, 35, 2, 0);
    //outtake cube to score high
    Intake(-80, 2 ,1);
    //move back
    Move(-1, 50, 2, 0);
    //move arms down
    ArmMove(-20,1.2);
    
    
    GyroTurn.GyroTurn(-50,25);
    Move(0.5, 50, 2, 1);
    Move(-0.5, 50, 2, 0);
    GyroTurn.GyroTurn(-100,30);
    ArmMove(40, -1.3);
    Intake(-80, 2 ,1);
    */

  }
         
  if(side == RED)
  {
    //wait for teammate to run set up
    vex::task::sleep(3000);
    //move forward to 4 stack tower
    Move(-1.1, 20, 5, 0);
    LeftFrontMotor.stop(vex::brakeType::hold);
    RightFrontMotor.stop(vex::brakeType::hold);
    LeftBackMotor.stop(vex::brakeType::hold);
    RightBackMotor.stop(vex::brakeType::hold);
    //turn to face back toward tower
    GyroTurn.GyroTurn(-94, 25);
    vex::task::sleep(100);
    //release intake system and push left side tower
    ArmMove(100,-.3, 2);
    vex::task::sleep(100);
    ArmMove(-85,.4, 2);
    vex::task::sleep(500);
    //move back to line up cube to intake
    Move(-.1,25, 1, 0);
    vex::task::sleep(250);
    //move forward to intake cube 
    Move(.4,40,1, 1);
    //move around tower to get a straight push into the 
    GyroTurn.GyroTurn(24,30);
    Move(-.4,25,2, 0);
    GyroTurn.GyroTurn(-73,25);
    vex::task::sleep(150);

    //push into tower
    Move(-0.3, 80, 2, 0);
    vex::task::sleep(500);
    Move(-4, 75, 2, 0);
    //move out of score zone
    Move(1,50, 2, 0);

    //face middle tower
    GyroTurn.GyroTurn(95, 30);
    //go to tower
    Move(1, 30, 3, 0);
    //move arms up
    ArmMove(40, -1.3, 3);
    //score high
    Intake(-80, 2 ,1);
///////////////////////////////////////////
    /*
    //turn to face tower
    GyroTurn.GyroTurn(-64,35);
    vex::task::sleep(100);
    //move arms up
    ArmMove(40, -1.2);
    //move toward tower
    Move(.1, 35, 2, 0);
    //release cube
    Intake(-80, 2 ,1);
    //move back
    Move(-1, 50, 2, 0);
    //move arms down
    ArmMove(-20,1.2);
    */
/*
    GyroTurn.GyroTurn(50,25);
    Move(0.5, 50, 2, 1);
    Move(-0.5, 50, 2, 0);
    GyroTurn.GyroTurn(100,30);
    ArmMove(40, -1.3);
    Intake(-80, 2 ,1);
    */
  }

  if(side == SKILLS)
  {
    //push intake away
    Move(0.2, 25, 5, 0);
    Move(-0.2, 35, 5, 0);
    vex::task::sleep(500);
    //release arm system
    ArmMove(100,-.3, 3);
    vex::task::sleep(100);
    ArmMove(-85,.4, 3);
    vex::task::sleep(250);
    //move to tower and intake
    Move(0.5, 20, 5, 1);
    Move(0.6, 35, 5, 0);
    vex::task::sleep(250);//a little to the left on blue side, fix it!
    //move arms up
    ArmMove(40, -1.2, 3);
    //score high
    Intake(-80, 2 ,1);
    //lower arms
    ArmMove(-40, -1.2, 3);
    LeftArmMotor.stop(vex::brakeType::coast);
    RightArmMotor.stop(vex::brakeType::coast);
    //turn to face block chunk
    GyroTurn.GyroTurn(-20, 25);
    //push chunk into corner to score
    Move(-2, 75, 5, 0);
    Move(0.5, 25, 5, 0);
    Move(-1, 75, 5, 0);
  }

  if(side == TEST)
  {
    VisionSensor.setWifiMode(vex::vision::wifiMode::off);
    while(1)
    {
      VisionSensor.takeSnapshot(1);
      if (VisionSensor.largestObject.exists && VisionSensor.largestObject.width > 5)
      {
        Brain.Screen.setPenColor(vex::color::white);
        Brain.Screen.setFillColor(vex::color::green);
        Brain.Screen.drawRectangle(0,0, 480, 240);
        Brain.Screen.setCursor(2,6);
        Brain.Screen.setFont(vex::fontType::mono40);
        Brain.Screen.print("Forward");
        LeftFrontMotor.spin(vex::directionType::fwd, 25, vex::velocityUnits::pct);
        LeftBackMotor.spin(vex::directionType::rev, 25, vex::velocityUnits::pct);
        RightFrontMotor.spin(vex::directionType::fwd, 25, vex::velocityUnits::pct);
        RightBackMotor.spin(vex::directionType::rev, 25, vex::velocityUnits::pct);
      }
      else
      {
        VisionSensor.takeSnapshot(2);
        if (VisionSensor.largestObject.exists && VisionSensor.largestObject.width > 5)
        {
          Brain.Screen.setPenColor(vex::color::black);
          Brain.Screen.setFillColor(vex::color::yellow);
          Brain.Screen.drawRectangle(0,0, 480, 240);
          Brain.Screen.setCursor(2,6);
          Brain.Screen.setFont(vex::fontType::mono40);
          Brain.Screen.print("Right");
          LeftFrontMotor.spin(vex::directionType::fwd, 25, vex::velocityUnits::pct);
          LeftBackMotor.spin(vex::directionType::rev, 25, vex::velocityUnits::pct);
        }
        else 
        {
          VisionSensor.takeSnapshot(3);
          if (VisionSensor.largestObject.exists && VisionSensor.largestObject.width>5)
          {
            Brain.Screen.setPenColor(vex::color::white);
            Brain.Screen.setFillColor(vex::color::red);
            Brain.Screen.drawRectangle(0,0, 480, 240);
            Brain.Screen.setCursor(2,6);
            Brain.Screen.setFont(vex::fontType::mono40);
            Brain.Screen.print("Left");
            RightFrontMotor.spin(vex::directionType::fwd, 25, vex::velocityUnits::pct);
            RightBackMotor.spin(vex::directionType::rev, 25, vex::velocityUnits::pct);
          }
          else 
          {
            LeftFrontMotor.stop();
            LeftBackMotor.stop();
            RightFrontMotor.stop();
            RightBackMotor.stop();
            Brain.Screen.clearScreen();
          }
        }
      } 
      task::sleep(100);
    }
  } //End TEST
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
  LeftArmMotor.resetRotation();
  RightArmMotor.resetRotation();
  bool lowTowerTask = false;
  bool midTowerTask = false;
  bool highTowerTask = false;
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
        LeftArmMotor.spin(vex::directionType::fwd, 35, vex::velocityUnits::pct);
        RightArmMotor.spin(vex::directionType::rev, 35, vex::velocityUnits::pct);
    
      }
      else if(Controller1.ButtonL1.pressing()){
      //arm system up
        LeftArmMotor.spin(vex::directionType::fwd, -35, vex::velocityUnits::pct);
        RightArmMotor.spin(vex::directionType::rev, -35, vex::velocityUnits::pct);
    
      }
    else{
      RightArmMotor.stop(vex::brakeType::hold);
      LeftArmMotor.stop(vex::brakeType::hold);
    }
    // arm motor;
      if(Controller1.ButtonA.pressing() || lowTowerTask)
      {
        lowTowerTask = true;
        midTowerTask = false;
        highTowerTask = false;
        //arms go up to score on the lower towers
        if(LeftArmMotor.rotation(vex::rotationUnits::rev) > -1.1 && RightArmMotor.rotation(vex::rotationUnits::rev)  > -1.1)
        {
          LeftArmMotor.spin(vex::directionType::fwd, -40, vex::velocityUnits::pct);
          RightArmMotor.spin(vex::directionType::rev, -40, vex::velocityUnits::pct);
        }
        else if(LeftArmMotor.rotation(vex::rotationUnits::rev) > -1.1 && RightArmMotor.rotation(vex::rotationUnits::rev)  > -1.1)
        {
          LeftArmMotor.spin(vex::directionType::fwd, 40, vex::velocityUnits::pct);
          RightArmMotor.spin(vex::directionType::rev, 40, vex::velocityUnits::pct);
        }
        else
        {
          lowTowerTask = false;
          LeftArmMotor.stop(vex::brakeType::hold);
          RightArmMotor.stop(vex::brakeType::hold);
        }
      }
      if(Controller1.ButtonB.pressing() || midTowerTask)
      {
        lowTowerTask = false;
        midTowerTask = true;
        highTowerTask = false;
        //arms go up to score on the lower towers
        if(LeftArmMotor.rotation(vex::rotationUnits::rev) > -1.3 && RightArmMotor.rotation(vex::rotationUnits::rev)  > -1.3)
        {
          LeftArmMotor.spin(vex::directionType::fwd, -40, vex::velocityUnits::pct);
          RightArmMotor.spin(vex::directionType::rev, -40, vex::velocityUnits::pct);
        }
        else if(LeftArmMotor.rotation(vex::rotationUnits::rev) > -1.3 && RightArmMotor.rotation(vex::rotationUnits::rev)  > -1.3)
        {
          LeftArmMotor.spin(vex::directionType::fwd, 40, vex::velocityUnits::pct);
          RightArmMotor.spin(vex::directionType::rev, 40, vex::velocityUnits::pct);
        }
        else
        {
          midTowerTask = false;
          LeftArmMotor.stop(vex::brakeType::hold);
          RightArmMotor.stop(vex::brakeType::hold);
        }
      }
      if(Controller1.ButtonX.pressing()){
        lowTowerTask = false;
        midTowerTask = false;
        highTowerTask = false;
        RightArmMotor.stop(vex::brakeType::hold);
        LeftArmMotor.stop(vex::brakeType::hold);
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