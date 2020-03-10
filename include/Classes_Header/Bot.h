#ifndef BOT_H
#define BOT_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       Bot.h                                                     */
/*    Author:       Team Xoloft                                               */
/*    Created:      11/25/19                                                  */
/*    Description:  Header file declaring the Bot Class to implement          */
/*                  composition with the LineSensor and GyroSensor objects    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "LineSensor.h"
#include "GyroSensor.h"
#include "LightSensor.h"
#include "DataLogging.h"

struct Bot
{
  public:
  GyroSensor gyroSensor;
  LineSensor lineSensor;
  LightSensor lightSensor;
  DataLogging datalogger;

  void setArms(double, int = 5);
  void raiseLow(int = 5);
  void raiseMid(int = 5);
  void raiseHigh(int = 5);
  void outtake(int = 5);
  void moveTo(double, int, int = 5);
  void move(double, int, int = 5);
};

#endif