#include "vex.h"
#include "basics.h"
#include "pid.h"
#include "manualcontrol.h"
extern _pid L;
extern _pid R;
void LSpeed(double speed)
{
  L1.spin(forward,speed,rpm);
  L2.spin(forward,speed,rpm);
  L3.spin(forward,speed,rpm);
}
void RSpeed(double speed)
{
  R1.spin(forward,speed,rpm);
  R2.spin(forward,speed,rpm);
  R3.spin(forward,speed,rpm);
}
void PSpeed(double speed)
{
  L_Pick.spin(forward,speed,rpm);
  //R_Pick.spin(forward,speed,rpm);
}
void all_reset()
{
  L1.resetRotation();
  L2.resetRotation();
  L3.resetRotation();
  R1.resetRotation();
  R2.resetRotation();
  R3.resetRotation();
}
void all_hold()
{
  L1.stop(hold);
  L2.stop(hold);
  L3.stop(hold);
  R1.stop(hold);
  R2.stop(hold);
  R3.stop(hold);
}
void all_brake()
{
  L1.stop(brake);
  L2.stop(brake);
  L3.stop(brake);
  R1.stop(brake);
  R2.stop(brake);
  R3.stop(brake);
}

void all_coast()
{
  L1.stop(coast);
  L2.stop(coast);
  L3.stop(coast);
  R1.stop(coast);
  R2.stop(coast);
  R3.stop(coast);
}
// void pid_init()
// {
//   L.p=0.1;
//   L.i=0.1;
//   L.d=0.1;
//   ///////////////////
//   R.p=0.1;
//   R.i=0.1;
//   R.d=0.1;
// }

