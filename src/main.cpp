// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----
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
#include "RobotConfiguration.h"
#include "Classes_Header/Bot.h"
#include "Classes_Header/VisionSensor.h"

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

  if(Intake == 1)
  {
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

  RightIntakeMotor.stop(vex::brakeType(hold));
  LeftIntakeMotor.stop(vex::brakeType(hold));

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

bool ArmIsAt(double rotationValue, int Time)
{
  Timeout(Time);
  if(LeftArmMotor.rotation(vex::rotationUnits::rev) == rotationValue && RightArmMotor.rotation(vex::rotationUnits::rev)  == rotationValue)
  {
    return true;
  }
  return false;
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
  enum Color{BLUE, RED, SKILLS, TEST, BLUE_VS_USC, RED_VS_USC};
  Color side = RED;

  Bot test;
  GyroSensor Gyroscope;
  LineSensor lineTracker;
  LeftArmMotor.setMaxTorque(100, percentUnits::pct);
  RightArmMotor.setMaxTorque(100, percentUnits::pct);

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
    Gyroscope.GyroTurn(94, 25);
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
    //move around tower and line up to push
    Gyroscope.GyroTurn(-30,30);
    Move(-.5,25,2, 0);
    Gyroscope.GyroTurn(68,25);
    vex::task::sleep(150);
    //push tower
    Move(-2, 30, 2, 0);
    Move(-1.9, 75, 2, 0);
    //move out of score zone
    Move(1,50, 2, 0);

    //realign bot against wall
    Gyroscope.GyroTurn(-20, 30);
    Move(-1, 30, 5, 0);
    vex::task::sleep(100);

    //face middle tower
    Move(0.3, 30, 3, 0);
    Gyroscope.GyroTurn(-10, 30);

    //go to tower
    Move(0.7, 30, 3, 0);
    //move arms up and realign with tower
    ArmMove(40, -0.65, 3);
    Move(0.15, 30, 3, 0);

    //score high
    Intake(-80, 2 ,1);
    //////////////////////////////
    /*
    //turn to face tower
    Gyroscope.GyroTurn(64,35);
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
    
    
    Gyroscope.GyroTurn(-50,25);
    Move(0.5, 50, 2, 1);
    Move(-0.5, 50, 2, 0);
    Gyroscope.GyroTurn(-100,30);
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
    Gyroscope.GyroTurn(-94, 25);
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
    Gyroscope.GyroTurn(24,30);
    Move(-.5,25,2, 0);
    Gyroscope.GyroTurn(-73,25);
    vex::task::sleep(150);

    //push into corner
    Move(-2, 30, 2 , 0);
    Move(-1.9, 75, 2, 0);
    //move out of score zone
    Move(1,50, 2, 0);

    //realign bot against wall
    Gyroscope.GyroTurn(20, 30);
    Move(-1, 30, 5, 0);
    vex::task::sleep(100);

    //face middle tower
    Move(0.3, 30, 3, 0);
    Gyroscope.GyroTurn(10, 30);

    //go to tower
    Move(0.7, 30, 3, 0);
    //move arms up and aline with tower
    ArmMove(40, -0.65, 3);
    Move(0.15, 30, 3, 0);

    //score high
    Intake(-80, 2 ,1);
///////////////////////////////////////////
    /*
    //turn to face tower
    Gyroscope.GyroTurn(-64,35);
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
    Gyroscope.GyroTurn(50,25);
    Move(0.5, 50, 2, 1);
    Move(-0.5, 50, 2, 0);
    Gyroscope.GyroTurn(100,30);
    ArmMove(40, -1.3);
    Intake(-80, 2 ,1);
    */
  }

  if(side == SKILLS)
  {
    //set arm motor encoders
    LeftArmMotor.resetRotation();
    RightArmMotor.resetRotation();
    //setup to takeout arms
    ArmMove(100, -0.2, 2);
    vex::task::sleep(100);
    LeftArmMotor.stop(vex::brakeType(coast));
    RightArmMotor.stop(vex::brakeType(coast));
    vex::task::sleep(250);
    Move(-.1,40,2,1);
    vex::task::sleep(100);
    ArmMove(90, 0.1, 2);
    vex::task::sleep(250);
    Move(.05,40,2,1);
    ArmMove(90,0.1, 2);
    vex::task::sleep(100);
    //intake cube
    Intake(80, -3 ,1);
    Move(0.1, 40, 2, 1);
    vex::task::sleep(500);
    //realign with wall
    Move(-0.15, 25, 2, 0);
    //move arms up to tower
    ArmMove(40, -0.7, 3);
    LeftArmMotor.stop(vex::brakeType(hold));
    RightArmMotor.stop(vex::brakeType(hold));
    vex::task::sleep(250);
    //move forward to realign arms with tower
    Move(0.15, 30, 2, 0);
    //score high
    vex::task::sleep(100);
    Intake(-80, 3 ,1);
    //back up to wall
    Move(-0.2, 30, 2, 0);
    vex::task::sleep(100);
    //turn to gather preload
    Gyroscope.GyroTurn(60, 30);
    //slowly lower arms
    ArmMove(50, 0.5, 2);
    LeftArmMotor.stop(vex::brakeType(coast));
    RightArmMotor.stop(vex::brakeType(coast));
    vex::task::sleep(500);
    //intake cube
    Move(0.9, 40, 2, 1);
    //turn to tower
    Gyroscope.GyroTurn(-60, 30);
    //realign with back wall
    Move(-0.45, 50, 3, 0);
    vex::task::sleep(250);
    //move to second tower
    Move(1.2, 50, 3, 1);
    vex::task::sleep(250);
    Move(-0.1, 50, 2, 0);
    vex::task::sleep(250);
    //lift arms up
    ArmMove(80, -0.55, 2);
    vex::task::sleep(250);
    //move and realign arms arms with tower
    Move(0.15, 30, 2, 0);
    //score high
    Intake(-80, 3 ,1);
    //lower arms
    ArmMove(80, 0.5, 2);
    LeftArmMotor.stop(vex::brakeType(coast));
    RightArmMotor.stop(vex::brakeType(coast));
    vex::task::sleep(250);
    //intake cube
    Move(-0.1, 50, 2, 1);
    vex::task::sleep(250);
    Move(0.1, 15, 2, 1);
    vex::task::sleep(100);
    Intake(80, -2 , 1);
    //move back to line up cube push
    Move(-0.4, 50, 2, 0);
    //turn to face cube
    Gyroscope.GyroTurn(-20, 30);
    //push cube into score zone
    Move(-0.7, 80, 2, 0);
    vex::task::sleep(250);
    //move out of score zone
    Move(0.5, 40, 2, 0);
    //turn and realign with wall
    Gyroscope.GyroTurn(40, 30);
    Move(-0.6, 40, 2, 0);
    vex::task::sleep(100);
    //move forward and turn to face cross tower
    Move(0.3, 40, 2, 0);
    Gyroscope.GyroTurn(-25, 30);
    //move across field to tower
    Move(7, 40, 2, 0);
    vex::task::sleep(100);
    //move arms up to tower
    ArmMove(80, -0.65, 2);
    //align arms to tower
    Move(0.15, 30, 2, 0);
    vex::task::sleep(100);
    //score high
    Intake(-80, 3 ,1);
    //back out and lower arms
    Move(-0.5, 30, 3, 0);
    vex::task::sleep(100);
    ArmMove(50, 0.5, 2);
    LeftArmMotor.stop(vex::brakeType(coast));
    RightArmMotor.stop(vex::brakeType(coast));
    vex::task::sleep(100);
    //turn to score zone
    Gyroscope.GyroTurn(-80, 30);
    Move(-2, 30, 2 , 0);
    Move(-2, 75, 2, 0);
    vex::task::sleep(100);
    Move(1, 70, 3, 0);
    //end SKILLS
  }

  if(side == TEST)
  {
    if(Brain.SDcard.isInserted())
    {
      std::ifstream inFile;
      DataLogging logger;

      inFile.open("Data_Logging.txt", std::ifstream::in);

      while(inFile >> logger)
      {
        logger.nextPosition(80, 80, 20);
      }

      inFile.close();
    }

    else
    {
      LightSensor lighter;
      Move(1, 30, 3, 1);
      while(!(lighter.blockIsIn()))
      {
        Move(0.25, 40, 2, 1);
        vex::task::sleep(250);
      }
      Move(-1, 50, 2, 0);
    }

    /*
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
    */
  } //End TEST
  if(side == BLUE_VS_USC)
  {
    //set arm motor encoders
    LeftArmMotor.resetRotation();
    RightArmMotor.resetRotation();
    //setup to takeout arms
    ArmMove(100, -0.2, 2);
    vex::task::sleep(100);
    LeftArmMotor.stop(vex::brakeType(coast));
    RightArmMotor.stop(vex::brakeType(coast));
    vex::task::sleep(250);
    Move(-.1,40,2,1);
    vex::task::sleep(100);
    ArmMove(90, 0.1, 2);
    vex::task::sleep(250);
    Move(.05,40,2,1);
    ArmMove(90,0.1, 2);
    vex::task::sleep(100);
    //intake cube
    Intake(80, -3 ,1);
    Move(0.1, 40, 2, 1);
    vex::task::sleep(500);
    //realign with wall
    Move(-0.15, 25, 2, 0);
    //move arms up to tower
    ArmMove(40, -0.7, 3);
    LeftArmMotor.stop(vex::brakeType(hold));
    RightArmMotor.stop(vex::brakeType(hold));
    vex::task::sleep(250);
    //move forward
    Move(0.15, 30, 2, 0);
    //score high
    vex::task::sleep(100);
    Intake(-80, 3 ,1);
    //back up to wall
    Move(-0.2, 30, 2, 0);
    //turn to gather preload
    vex::task::sleep(100);
    Gyroscope.GyroTurn(60, 30);
    //slowly lower arms
    ArmMove(50, 0.5, 2);
    LeftArmMotor.stop(vex::brakeType(coast));
    RightArmMotor.stop(vex::brakeType(coast));
    vex::task::sleep(500);
    //intake cube
    Move(0.9, 40, 2, 1);
    //turn to tower
    Gyroscope.GyroTurn(-60, 30);
    //realign with back wall
    Move(-0.45, 50, 3, 0);
    vex::task::sleep(250);
    //move to second tower
    Move(1.2, 50, 3, 1);
    vex::task::sleep(250);
    Move(-0.1, 50, 2, 0);
    vex::task::sleep(250);
    //lift arms up
    ArmMove(80, -0.55, 2);
    vex::task::sleep(250);
    //score high
    Intake(-80, 3 ,1);
    //lower arms
    ArmMove(80, 0.5, 2);
    LeftArmMotor.stop(vex::brakeType(coast));
    RightArmMotor.stop(vex::brakeType(coast));
    vex::task::sleep(250);
    //intake cube
    Move(-0.1, 50, 2, 1);
    vex::task::sleep(250);
    Move(0.1, 15, 2, 1);
    vex::task::sleep(100);
    Intake(80, -2 , 1);
    //move back to line up cube push
    Move(-0.4, 50, 2, 0);
    //turn to face cube
    Gyroscope.GyroTurn(-25, 30);
    //push cube into score zone
    Move(-0.7, 80, 2, 0);
    vex::task::sleep(250);
  }
  if(side == RED_VS_USC)
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
    Gyroscope.GyroTurn(-94, 25);
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
    Gyroscope.GyroTurn(24,30);
    Move(-.4,25,2, 0);
    Gyroscope.GyroTurn(-73,25);
    vex::task::sleep(150);

    //push into corner
    Move(-2, 30, 2 , 0);
    Move(-2, 75, 2, 0);
    //move out of score zone
    Move(1,50, 2, 0);

    //face middle tower
    Gyroscope.GyroTurn(95, 30);
    //go to tower
    Move(0.7, 30, 3, 0);
    //move arms up
    ArmMove(40, -0.65, 3);
    //score high
    Intake(-80, 2 ,1);
///////////////////////////////////////////
    /*
    //turn to face tower
    Gyroscope.GyroTurn(-64,35);
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
  LeftArmMotor.resetRotation();
  RightArmMotor.resetRotation();

  std::ofstream outFile;

  int count = 0;
  bool editor = true;
  bool Data_Logging = false;
  bool lowTowerTask = false;
  bool midTowerTask = false;
  bool highTowerTask = false;

  if (editor)
  {
    Brain.Screen.clearScreen();
    Controller1.Screen.clearScreen();
    Brain.Screen.printAt(10, 30, "Editor Mode On");
    Controller1.Screen.print("Editor Mode On");
    Controller1.Screen.newLine();
  }
  else
  {
    Brain.Screen.clearScreen();
    Controller1.Screen.clearScreen();
    Brain.Screen.printAt(10, 30, "Editor Mode Off");
    Controller1.Screen.print("Editor Mode Off");
    Controller1.Screen.newLine();
  }
  if (Brain.SDcard.isInserted())
  {
    Brain.Screen.printAt(10, 50, "SD Card Found");
    Controller1.Screen.print("SD Card Found");
    Controller1.Screen.newLine();
  }
  else
  {
    Brain.Screen.printAt(10, 50, "SD Card Not Found");
    Controller1.Screen.print("SD Card Not Found");
    Controller1.Screen.newLine();
  }

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
        LeftArmMotor.spin(vex::directionType::fwd, 90, vex::velocityUnits::pct);
        RightArmMotor.spin(vex::directionType::rev, 90, vex::velocityUnits::pct);
    
      }
      else if(Controller1.ButtonL1.pressing()){
      //arm system up
        LeftArmMotor.spin(vex::directionType::fwd, -90, vex::velocityUnits::pct);
        RightArmMotor.spin(vex::directionType::rev, -90, vex::velocityUnits::pct);
    
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
          //position arms up
          LeftArmMotor.spin(vex::directionType::fwd, -40, vex::velocityUnits::pct);
          RightArmMotor.spin(vex::directionType::rev, -40, vex::velocityUnits::pct);
        }
        else if(LeftArmMotor.rotation(vex::rotationUnits::rev) < -1.1 && RightArmMotor.rotation(vex::rotationUnits::rev)  < -1.1)
        {
          //position arms down
          LeftArmMotor.spin(vex::directionType::fwd, 40, vex::velocityUnits::pct);
          RightArmMotor.spin(vex::directionType::rev, 40, vex::velocityUnits::pct);
        }
        else
        {
          //condiition satisfied
          lowTowerTask = false;
          if(editor)
          {
            LeftArmMotor.stop(vex::brakeType::brake);
            RightArmMotor.stop(vex::brakeType::brake);  
          }
          else
          {
            LeftArmMotor.stop(vex::brakeType::hold);
            RightArmMotor.stop(vex::brakeType::hold);
          }
        }
      }
      if(Controller1.ButtonB.pressing() || midTowerTask)
      {
        lowTowerTask = false;
        midTowerTask = true;
        highTowerTask = false;
        //arms go up to score on the lower towers
        if(LeftArmMotor.rotation(vex::rotationUnits::rev) > -1.2 && RightArmMotor.rotation(vex::rotationUnits::rev)  > -1.2)
        {
          //position arms up
          LeftArmMotor.spin(vex::directionType::fwd, -40, vex::velocityUnits::pct);
          RightArmMotor.spin(vex::directionType::rev, -40, vex::velocityUnits::pct);
        }
        else if(LeftArmMotor.rotation(vex::rotationUnits::rev) < -1.3 && RightArmMotor.rotation(vex::rotationUnits::rev)  < -1.3)
        {
          //position arms down
          LeftArmMotor.spin(vex::directionType::fwd, 40, vex::velocityUnits::pct);
          RightArmMotor.spin(vex::directionType::rev, 40, vex::velocityUnits::pct);
        }
        else
        {
          //condition satisfied
          midTowerTask = false;
          LeftArmMotor.stop(vex::brakeType::hold);
          RightArmMotor.stop(vex::brakeType::hold);
        }
      }
      if(Controller1.ButtonX.pressing())
      {
        lowTowerTask = false;
        midTowerTask = false;
        highTowerTask = false;
        RightArmMotor.stop(vex::brakeType::hold);
        LeftArmMotor.stop(vex::brakeType::hold);
      }
      if(Controller1.ButtonUp.pressing() && Brain.SDcard.isInserted() && editor)
      {
        vex::task::sleep(500);
        if(Data_Logging)
        {
          if(outFile.is_open())
          {
            //increase loop counter variable
            count++;
            //record current encoder rotation values of each motor
            outFile << RightArmMotor.rotation(vex::rotationUnits::rev) << ',' //rightArmMotor rotation value
                    << LeftArmMotor.rotation(vex::rotationUnits::rev) << ',' //leftArmMotor rotaion value
                    << RightIntakeMotor.rotation(vex::rotationUnits::rev) << ',' //rightIntakeMotor rotaion value
                    << LeftIntakeMotor.rotation(vex::rotationUnits::rev) << ',' //leftIntakeMotor rotation value
                    << RightBackMotor.rotation(vex::rotationUnits::rev) << ',' //rightBackMotor rotation value
                    << LeftBackMotor.rotation(vex::rotationUnits::rev) << ',' //leftBackMotor rotation value
                    << RightFrontMotor.rotation(vex::rotationUnits::rev) << ',' //rightFrontMotor rotation value
                    << LeftFrontMotor.rotation(vex::rotationUnits::rev) << '\n'; //leftFrontMotor rotation value
            //print message for UI
            Brain.Screen.clearScreen();
            Brain.Screen.printAt(10, 30, "Values recorded %d times", count);
            Controller1.Screen.clearScreen();
            Controller1.Screen.print("Values recorded %d times", count);
            Controller1.Screen.newLine();
          }
          else
          {
            outFile.open("Data_Logging.txt", std::ofstream::out);
            outFile << 0 << ',' //rightArmMotor rotation value
                    << 0 << ',' //leftArmMotor rotaion value
                    << 0 << ',' //rightIntakeMotor rotaion value
                    << 0 << ',' //leftIntakeMotor rotation value
                    << 0 << ',' //rightBackMotor rotation value
                    << 0 << ',' //leftBackMotor rotation value
                    << 0 << ',' //rightFrontMotor rotation value
                    << 0 << ',' //leftFrontMotor rotation value
                    << '\n';
            if(outFile.is_open())
            {
              Brain.Screen.clearScreen();
              Brain.Screen.printAt(10, 30, "file opened");
              Controller1.Screen.clearScreen();
              Controller1.Screen.print("file opened");
              Controller1.Screen.newLine();
            }
          }
        }
        else
        {
          Data_Logging = true;
          //reset rotation of motor in order as their values will appear on the .txt file
          RightArmMotor.resetRotation();
          LeftArmMotor.resetRotation();
          RightIntakeMotor.resetRotation();
          LeftIntakeMotor.resetRotation();
          RightBackMotor.resetRotation();
          LeftBackMotor.resetRotation();
          RightFrontMotor.resetRotation();
          LeftFrontMotor.resetRotation();
        }
      }
      else if(Controller1.ButtonDown.pressing() && Brain.SDcard.isInserted() && outFile.is_open())
      {
        outFile.close();
        Brain.Screen.clearScreen();
        Brain.Screen.printAt(10, 30, "File Closed");
        Controller1.Screen.clearScreen();
        Controller1.Screen.print("File Closed");
        Controller1.Screen.newLine();
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