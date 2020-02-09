#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       GyroSensor.h                                              */
/*    Author:       Michael Pfeiffer                                          */
/*    Created:      11/25/19                                                  */
/*    Description:  Header file declaring the Gyro Class to declare member    */
/*                  functions and data members to use with the Gyro           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

class LightSensor
{
  private:
    int lightValueWithBlock;
    int lightValue;
  public:
    LightSensor();
    void Callibrate();
    void LightTest();
    bool blockIsIn(int = 750);
};

#endif