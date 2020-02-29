#include "RobotConfiguration.h"

/*----- External Devices -----*/
  brain Brain = brain();
  controller Controller1 = controller();

/*----- Drive System -----*/
  motor RightBackMotor1 = motor(vex::PORT20, vex::gearSetting::ratio6_1,true);
  motor RightBackMotor2 = motor(vex::PORT18, vex::gearSetting::ratio6_1,false);
  motor LeftBackMotor1 = motor(vex::PORT6, vex::gearSetting::ratio6_1,false);
  motor LeftBackMotor2 = motor(vex::PORT8, vex::gearSetting::ratio6_1,true);
  motor RightFrontMotor1 = motor(vex::PORT14, vex::gearSetting::ratio6_1,false);
  motor RightFrontMotor2 = motor(vex::PORT15, vex::gearSetting::ratio6_1,true);
  motor LeftFrontMotor1 = motor(vex::PORT4, vex::gearSetting::ratio6_1,false);
  motor LeftFrontMotor2 = motor(vex::PORT3, vex::gearSetting::ratio6_1,true);
  motor_group LeftFrontMotor = motor_group(LeftFrontMotor1, LeftFrontMotor2);
  motor_group RightFrontMotor = motor_group(RightFrontMotor1, RightFrontMotor2);
  motor_group LeftBackMotor = motor_group(LeftBackMotor1, LeftBackMotor2);
  motor_group RightBackMotor = motor_group(RightBackMotor1, RightBackMotor2);
  motor_group LeftDrive = motor_group(LeftFrontMotor1, LeftFrontMotor2, LeftBackMotor1, LeftBackMotor2);
  motor_group RightDrive = motor_group(RightFrontMotor1, RightFrontMotor2, RightBackMotor1, RightBackMotor2);

/*----- Arm System -----*/
  motor RightArmMotor = motor(vex::PORT10, vex::gearSetting::ratio36_1, false);
  motor LeftArmMotor = motor(vex::PORT10, vex::gearSetting::ratio36_1, false);
  motor_group ArmSystem = motor_group(LeftArmMotor, RightArmMotor);

/*----- Intake System -----*/
  motor RightIntakeMotor = motor(vex::PORT10, vex::gearSetting::ratio36_1,false);
  motor LeftIntakeMotor = motor(vex::PORT10, vex::gearSetting::ratio36_1,false);
  motor_group IntakeSystem = motor_group(LeftIntakeMotor, RightIntakeMotor);

/*----- Ramp Tilt System -----*/
  motor RightTiltMotor = motor(vex::PORT10, vex::gearSetting::ratio36_1, true);
  motor LeftTiltMotor = motor(vex::PORT10, vex::gearSetting::ratio36_1, true);
  motor_group RampTiltSystem = motor_group(LeftIntakeMotor, RightIntakeMotor);

/*----- 3-Wire Port Sensors -----*/
  gyro Gyro = gyro(Brain.ThreeWirePort.B);
  line RightLineTracker = line(Brain.ThreeWirePort.C);
  line LeftLineTracker = line(Brain.ThreeWirePort.D);
  light LightReader = light(Brain.ThreeWirePort.H);

/*----- Pneumatics -----*/
  digital_out Piston = digital_out(Brain.ThreeWirePort.E);

/*----- Competition -----*/
competition Competition = competition();

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)