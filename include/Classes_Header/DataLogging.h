#ifndef DATALOGGING_H
#define DATALOGGING_H

class DataLogging
{
  private:
    double preRotationValue[7];
    double nextRotationValue[7];
    double prevArmRotation;
    double prevIntakeRotation;
    double prevRightBackRotation;
    double prevLeftBackRotation;
    double prevRightFrontRotation;
    double prevLeftFrontRotation;
    double prevGyroDegree;

  public:
    DataLogging();
    void nextPosition(int = 50, int = 80, int = 30);
    void skipStep();
    friend std::istream &operator>>(std::istream&, DataLogging&); 
};

#endif