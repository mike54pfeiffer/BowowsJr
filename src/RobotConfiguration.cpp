#include "RobotConfiguration.h"

/*----- External Devices -----*/
  brain Brain = brain();
  controller Controller1 = controller();

/*----- Drive System -----*/
  motor LeftFrontMotorF = motor(vex::PORT1, vex::gearSetting::ratio18_1,false);
  motor RightFrontMotorF = motor(vex::PORT9, vex::gearSetting::ratio18_1,true);
  motor LeftFrontMotorB = motor(vex::PORT3, vex::gearSetting::ratio18_1,false);
  motor RightFrontMotorB = motor(vex::PORT4, vex::gearSetting::ratio18_1,true);
  motor LeftBackMotorF = motor(vex::PORT5, vex::gearSetting::ratio18_1,false);
  motor RightBackMotorF = motor(vex::PORT6, vex::gearSetting::ratio18_1,true);
  motor LeftBackMotorB = motor(vex::PORT7, vex::gearSetting::ratio18_1,false);
  motor RightBackMotorB = motor(vex::PORT8, vex::gearSetting::ratio18_1,true);
  motor_group LeftFrontMotor = motor_group(LeftFrontMotorF, LeftFrontMotorB);
  motor_group RightFrontMotor = motor_group(RightFrontMotorF, RightFrontMotorB);
  motor_group LeftBackMotor = motor_group(LeftBackMotorF, LeftBackMotorB);
  motor_group RightBackMotor = motor_group(RightBackMotorF, RightBackMotorB);
  motor_group LeftDrive = motor_group(LeftFrontMotorF, LeftFrontMotorB, LeftBackMotorF, LeftBackMotorB);
  motor_group RightDrive = motor_group(RightFrontMotorF, RightFrontMotorB, RightBackMotorF, RightBackMotorB);
  motor_group DriveSystem = motor_group(LeftFrontMotorF, LeftFrontMotorB, LeftBackMotorF, LeftBackMotorB, RightFrontMotorF, RightFrontMotorB, RightBackMotorF, RightBackMotorB);

/*----- Arm System -----*/
  motor LeftArmMotorT = motor(vex::PORT12, vex::gearSetting::ratio36_1, true);
  motor RightArmMotorT = motor(vex::PORT13, vex::gearSetting::ratio36_1, false);
  motor LeftArmMotorB = motor(vex::PORT14, vex::gearSetting::ratio36_1, false);
  motor RightArmMotorB = motor(vex::PORT15, vex::gearSetting::ratio36_1, true);
  motor_group ArmSystem = motor_group(RightArmMotorT, RightArmMotorB, LeftArmMotorT, LeftArmMotorB);

/*----- Intake System -----*/
  motor LeftIntakeMotor = motor(vex::PORT11, vex::gearSetting::ratio36_1,false);
  motor RightIntakeMotor = motor(vex::PORT20, vex::gearSetting::ratio36_1,false);
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