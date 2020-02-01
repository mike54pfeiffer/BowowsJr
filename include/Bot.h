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

struct Bot
{
  public:
  GyroSensor gyroSensor;
  LineSensor lineSensor;

  void setArms();
  void riseLow();
  void riseHigh();
  void outtake();
  void parabolicTurn(char, int);
};

#endif