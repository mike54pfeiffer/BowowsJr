#include "RobotConfiguration.h"
#include "Classes_Header/LightSensor.h"

LightSensor::LightSensor()
{
  lightValue = LightReader.value(analogUnits::mV);
  lightValueWithBlock = 550;
}

void LightSensor::Callibrate()
{
  vex::task::sleep(250);
  lightValue = LightReader.value(analogUnits::mV);
}

void LightSensor::LightTest()
{
  //run an infinite loop to have all the time to test the output of your gyro
  while(true)
  {
    //print the gyro value of degrees rotated to the brain
    Brain.Screen.clearScreen();
    double val = LightReader.value(analogUnits::mV);
    Brain.Screen.printAt(100, 100, "LightValue %f mV", val);
    vex::task::sleep(500);
  }
}

bool LightSensor::blockIsIn(int pause)
{
  vex::task::sleep(pause);
  if(LightReader.value(analogUnits::mV) > lightValueWithBlock)
  {
    return true;
  }
  return false;
}