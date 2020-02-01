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

extern brain Brain;
extern controller Controller1;
extern motor RightIntakeMotor;
extern motor LeftIntakeMotor;
extern motor RightBackMotor;
extern motor LeftBackMotor;
extern motor RightFrontMotor;
extern motor LeftFrontMotor;
extern motor RightTiltMotor;
extern motor LeftTiltMotor;
extern motor RightArmMotor;
extern motor LeftArmMotor;
extern gyro Gyro;
extern line RightLineTracker;
extern line LeftLineTracker;
extern digital_out leftpiston;
extern light LightReader;

#endif