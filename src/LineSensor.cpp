#include "RobotConfiguration.h"
#include "LineSensor.h"

void LineSensor::fallBack()
{
  //function to override movement and backout before crossing line
  LeftFrontMotor.setVelocity(70, vex::velocityUnits::pct);
  RightFrontMotor.setVelocity(70, vex::velocityUnits::pct);
  LeftBackMotor.setVelocity(70, vex::velocityUnits::pct);
  RightBackMotor.setVelocity(70, vex::velocityUnits::pct);
  int stopper = time(0) + 1;
  for(int timeWait = time(0); timeWait <= stopper; timeWait = time(0))
  {
    LeftBackMotor.spin(directionType::rev); 
    LeftFrontMotor.spin(directionType::rev); 
    RightBackMotor.spin(directionType::rev); 
    RightFrontMotor.spin(directionType::rev);
  }
  LeftBackMotor.stop();
  LeftFrontMotor.stop();
  RightBackMotor.stop();
  RightFrontMotor.stop();
}

LineSensor::LineSensor()
{
  //Values to use for detection
  whiteValue = NULL;
  darkValue = NULL;
  blueValue = NULL;
  redValue = NULL;
  tolerance = 100;
}

void LineSensor::CallibrateLineSensor()
{
  //values to set to get an initial read of values
  leftAnalogCallibrated = LeftLineTracker.value(analogUnits::mV);
  rightAnalogCallibrated = RightLineTracker.value(analogUnits::mV);
  averageDetectionCallibrated = (leftAnalog + rightAnalog) / 2;
}

void LineSensor::SetLineValues()
{
  //change the current values in the lineTracker class
  leftAnalog = LeftLineTracker.value(analogUnits::mV);
  rightAnalog = RightLineTracker.value(analogUnits::mV);
  averageDetection = (leftAnalog + rightAnalog) / 2;
}

void LineSensor::moveWithCaution(int speed)
{
  //A move function which utillizes the line sensors
  LeftFrontMotor.setVelocity(speed, vex::velocityUnits::pct);
  RightFrontMotor.setVelocity(speed, vex::velocityUnits::pct);
  LeftBackMotor.setVelocity(speed, vex::velocityUnits::pct);
  RightBackMotor.setVelocity(speed, vex::velocityUnits::pct);
  LeftBackMotor.spin(directionType::fwd); 
  LeftFrontMotor.spin(directionType::fwd); 
  RightBackMotor.spin(directionType::fwd); 
  RightFrontMotor.spin(directionType::fwd);
  int stopper = time(0) + 10;
  for(int timeWait = time(0); timeWait <= stopper; timeWait = time(0))
  {
    this -> SetLineValues();
    //if((averageDetection > (white + (tolerance/2))) && (leftAnalog < (white + tolerance) || rightAnalog < (white + tolerance)))
    //{
    //  return this -> fallBack();
    //}
  }
  LeftBackMotor.stop();
  LeftFrontMotor.stop();
  RightBackMotor.stop();
  RightFrontMotor.stop();
}

void LineSensor::LineTest()
{
  while(true)
  {
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(1, 20, "Left Analog percent: %d mV", LeftLineTracker.value(analogUnits::mV));
    Brain.Screen.newLine();
    Brain.Screen.printAt(1, 40, "Right Analog percent: %d mV", RightLineTracker.value(analogUnits::mV));
    Brain.Screen.newLine();
    Brain.Screen.printAt(1, 60, "Average Detection: %d", (LeftLineTracker.value(analogUnits::mV) + RightLineTracker.value(analogUnits::mV))/2);
    vex::task::sleep(250);
  }
}