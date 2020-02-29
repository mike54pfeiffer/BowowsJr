#ifndef ROBOTCONFIGURATION_H
#define ROBOTCONFIGURATION_H
#include "vex.h"
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       RobotConfiguration.h                                      */
/*    Author:       Jhovanny Michua                                           */
/*    Created:      9/12/19                                                   */
/*    Description:  Header file declaring all components of the bot as        */
/*                  external to avoid multiple definition errors              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----- External Devices -----*/
  extern brain Brain;
  extern controller Controller1;

/*----- Drive System -----*/
  extern motor RightBackMotor1;
  extern motor RightBackMotor2;
  extern motor LeftBackMotor1;
  extern motor LeftBackMotor2;
  extern motor RightFrontMotor1;
  extern motor RightFrontMotor2;
  extern motor LeftFrontMotor1;
  extern motor LeftFrontMotor2;
  extern motor_group LeftFrontMotor;
  extern motor_group RightFrontMotor;
  extern motor_group LeftBackMotor;
  extern motor_group RightBackMotor;
  extern motor_group LeftDrive;
  extern motor_group RightDrive;

/*----- Arm System -----*/
  extern motor RightArmMotor;
  extern motor LeftArmMotor;
  extern motor_group ArmSystem;

/*----- Intake System -----*/
  extern motor RightIntakeMotor;
  extern motor LeftIntakeMotor;
  extern motor_group IntakeSystem;

/*----- Ramp Tilt System -----*/
  extern motor RightTiltMotor;
  extern motor LeftTiltMotor;
  extern motor_group RampTiltSystem;

/*----- 3-Wire Sensors -----*/
  extern gyro Gyro;
  extern line RightLineTracker;
  extern line LeftLineTracker;
  extern light LightReader;

/*----- Pneumatics -----*/
  extern digital_out Piston;

/*----- Competition -----*/
  extern competition Competition;

#endif