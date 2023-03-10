#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor L2 = motor(PORT12, ratio18_1, false);
motor L3 = motor(PORT13, ratio18_1, true);
motor R1 = motor(PORT18, ratio18_1, false);
motor R2 = motor(PORT19, ratio18_1, true);
motor R3 = motor(PORT20, ratio18_1, false);
motor L_Pick = motor(PORT1, ratio18_1, true);
motor R_Pick = motor(PORT10, ratio18_1, true);
motor SpinUp = motor(PORT4, ratio6_1, false);
motor Ready = motor(PORT8, ratio18_1, true);
motor SpinUpR = motor(PORT5, ratio6_1, true);
inertial GYRO = inertial(PORT6);
digital_out Q = digital_out(Brain.ThreeWirePort.B);
motor L1 = motor(PORT14, ratio18_1, true);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}