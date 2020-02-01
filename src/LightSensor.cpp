#include "RobotConfiguration.h"
#include "LightSensor.h"

void LightSensor::LightTest()
{
  //run an infinite loop to have all the time to test the output of your gyro
  while(true)
  {
    //print the gyro value of degrees rotated to the brain
    Brain.Screen.clearScreen();
    double val = LightReader.value(percentUnits::pct);
    Brain.Screen.printAt(100, 100, "LightValue %f %%", val);
    vex::task::sleep(500);
  }
}