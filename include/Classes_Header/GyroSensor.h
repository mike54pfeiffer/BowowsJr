#ifndef GYROSENSOR_H
#define GYROSENSOR_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       GyroSensor.h                                              */
/*    Author:       Michael Pfeiffer                                          */
/*    Created:      11/25/19                                                  */
/*    Description:  Header file declaring the Gyro Class to declare member    */
/*                  functions and data members to use with the Gyro           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

class GyroSensor
{
  private:
    int gyroValue;
  public:
    void GyroTest();
    void GyroTurn(double, int);
};

#endif