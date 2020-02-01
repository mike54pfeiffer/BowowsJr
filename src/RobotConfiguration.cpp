#include "RobotConfiguration.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Sonar                sonar         G, H            
// ---- END VEXCODE CONFIGURED DEVICES ----

brain Brain = brain();
controller Controller1 = controller();
motor RightIntakeMotor = motor(vex::PORT20, vex::gearSetting::ratio18_1,false);
motor LeftIntakeMotor = motor(vex::PORT9, vex::gearSetting::ratio18_1,false);
motor RightBackMotor = motor(vex::PORT13, vex::gearSetting::ratio18_1,true);
motor LeftBackMotor = motor(vex::PORT3, vex::gearSetting::ratio18_1,false);
motor RightFrontMotor = motor(vex::PORT14, vex::gearSetting::ratio18_1,true);
motor LeftFrontMotor = motor(vex::PORT7, vex::gearSetting::ratio18_1,false);
motor RightTiltMotor = motor(vex::PORT15, vex::gearSetting::ratio18_1, true);
motor LeftTiltMotor = motor(vex::PORT5, vex::gearSetting::ratio18_1, true);
motor RightArmMotor = motor(vex::PORT17, vex::gearSetting::ratio18_1, true);
motor LeftArmMotor = motor(vex::PORT6, vex::gearSetting::ratio18_1, true);
gyro Gyro = gyro(Brain.ThreeWirePort.B);
line RightLineTracker = line(Brain.ThreeWirePort.C);
line LeftLineTracker = line(Brain.ThreeWirePort.D);
digital_out leftpiston = digital_out(Brain.ThreeWirePort.E);
light LightReader = light(Brain.ThreeWirePort.H);