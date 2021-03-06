#ifndef LINESENSOR_H
#define LINESENSOR_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       LineSensor.h                                              */
/*    Author:       Michael Pfeiffer                                          */
/*    Created:      11/25/19                                                  */
/*    Description:  Header file declaring the Line Tracker Class to declare   */
/*                  member functions and data members to use with the Line    */
/*                  Tracker                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
  LineTracker

    This class lets the robot detect lines through the light reflected
    from the ground
    
    Variables:

    Notes:

---------------------------------------------------------------------------*/
class LineSensor
{
  private:
    //Data Members
    int leftAnalog;
    int rightAnalog;
    int averageDetection;
    int leftAnalogCallibrated;
    int rightAnalogCallibrated;
    int averageDetectionCallibrated;
    //color values
    int whiteValue;
    int darkValue;
    int blueValue;
    int redValue;
    int tolerance;
    //Private Member Functions
    void fallBack();
    bool toleranceCheck(char, int);
  public:
    //Public Member Functions
    LineSensor();
    void CallibrateLineSensor();
    void SetLineValues();
    void moveWithCaution(int);
    void LineStraight(float);
    void LineTest();
};

#endif