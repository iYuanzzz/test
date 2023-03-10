using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor L2;
extern motor L3;
extern motor R1;
extern motor R2;
extern motor R3;
extern motor L_Pick;
extern motor R_Pick;
extern motor SpinUp;
extern motor Ready;
extern motor SpinUpR;
extern inertial GYRO;
extern digital_out Q;
extern motor L1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );