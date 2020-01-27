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
  whiteValue = 175;
  darkValue = 2235;
  blueValue = 205;
  redValue = 185;
  tolerance = 10;
}

bool LineSensor::toleranceCheck(char sensor, int readValue)
{
  sensor = toupper(sensor);
  switch(sensor)
  {
    case 'L':
    {
      if(LeftLineTracker.value(analogUnits::mV) >= readValue - tolerance && LeftLineTracker.value(analogUnits::mV) <= readValue + tolerance)
      {
        return true;
      }
      break;
    }
    case 'R':
    {
      if(RightLineTracker.value(analogUnits::mV) >= readValue - tolerance && RightLineTracker.value(analogUnits::mV) <= readValue + tolerance)
      {
        return true;
      }
      break;
    }
    case 'B':
    {
      if(LeftLineTracker.value(analogUnits::mV) >= readValue - tolerance && LeftLineTracker.value(analogUnits::mV) <= readValue + tolerance && RightLineTracker.value(analogUnits::mV) >= readValue - tolerance && RightLineTracker.value(analogUnits::mV) <= readValue + tolerance)
      {
        return true;
      }
      break;
    }
    default:
    {
      return false;
    }
  }
  return false;
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

void LineSensor::LineStraight(float Velocity)
{
  bool leftDetect = false;
  bool rightDetect = false;
  LeftFrontMotor.spin(directionType::fwd, Velocity, vex::velocityUnits::pct);
  LeftBackMotor.spin(directionType::fwd, Velocity, vex::velocityUnits::pct);
  RightFrontMotor.spin(directionType::fwd, Velocity, vex::velocityUnits::pct);
  RightBackMotor.spin(directionType::fwd, Velocity, vex::velocityUnits::pct);
  while(1)
  {
    if(toleranceCheck('R', whiteValue) && !leftDetect)
    {
      rightDetect = true;
    }
    if(toleranceCheck('L', whiteValue) && !rightDetect)
    {
      leftDetect = true;
    }
    if(toleranceCheck('B', whiteValue))
    {
      //both line sensors are on line
      leftDetect = false;
      rightDetect = false;
      LeftFrontMotor.stop(vex::brakeType::hold);
      RightFrontMotor.stop(vex::brakeType::hold);
      LeftBackMotor.stop(vex::brakeType::hold);
      RightBackMotor.stop(vex::brakeType::hold);
      //turn to face tower
      break;
    }
    else if(toleranceCheck('L', whiteValue) && rightDetect)
    {
      //right line sensor passed line first
      LeftFrontMotor.stop(vex::brakeType::hold);
      RightFrontMotor.stop(vex::brakeType::hold);
      LeftBackMotor.stop(vex::brakeType::hold);
      RightBackMotor.stop(vex::brakeType::hold);
      RightFrontMotor.spin(directionType::fwd, 40, vex::velocityUnits::pct);
      RightBackMotor.spin(directionType::fwd, 40, vex::velocityUnits::pct);
      while(1)
      {
        if(toleranceCheck('R', whiteValue))
        {
          LeftFrontMotor.stop(vex::brakeType::hold);
          RightFrontMotor.stop(vex::brakeType::hold);
          LeftBackMotor.stop(vex::brakeType::hold);
          RightBackMotor.stop(vex::brakeType::hold);
          break;
        }
      }
      break;
    }
    else if(toleranceCheck('R', whiteValue) && leftDetect)
    {
      //left line sensor passed line first
      LeftFrontMotor.stop(vex::brakeType::hold);
      RightFrontMotor.stop(vex::brakeType::hold);
      LeftBackMotor.stop(vex::brakeType::hold);
      RightBackMotor.stop(vex::brakeType::hold);
      LeftFrontMotor.spin(directionType::rev, 40, vex::velocityUnits::pct);
      LeftBackMotor.spin(directionType::rev, 40, vex::velocityUnits::pct);
      while(1)
      {
        if(toleranceCheck('L', whiteValue))
        {
          LeftFrontMotor.stop(vex::brakeType::hold);
          RightFrontMotor.stop(vex::brakeType::hold);
          LeftBackMotor.stop(vex::brakeType::hold);
          RightBackMotor.stop(vex::brakeType::hold);
          break;
        }
      }
      break;
    }
  }
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