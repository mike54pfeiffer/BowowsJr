#ifndef DATALOGGING_H
#define DATALOGGING_H

class DataLogging
{
  private:
    double preRotationValue[8];
    double nextRotationValue[8];
    double prevRightArmRotation;
    double prevLeftArmRotation;
    double prevRightIntakeRotation;
    double prevLeftIntakeRotation;
    double prevRightBackRotation;
    double prevLeftBackRotation;
    double prevRightFrontRotation;
    double prevLeftFrontRotation;

  public:
    DataLogging();
    void nextPosition(int = 80, int = 80, int = 40);
    void skipStep();
    friend std::istream &operator>>(std::istream&, DataLogging&); 
};

#endif