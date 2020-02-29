#ifndef  VEX_H
#define VEX_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

//C++ Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <climits>

//Vex Coding Studio Libraries
#include "v5.h"
#include "v5_vcs.h"

//Vex Namespace
  using namespace vex;

//Global Variables
  const int redMotor_RPM = 100;
  const int greenMotor_RPM = 200;
  const int blueMotor_RPM = 600;

#endif