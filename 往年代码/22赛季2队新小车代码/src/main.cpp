/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// L2                   motor         12              
// L3                   motor         13              
// R1                   motor         18              
// R2                   motor         19              
// R3                   motor         20              
// L_Pick               motor         1               
// R_Pick               motor         10              
// SpinUp               motor         4               
// Ready                motor         8               
// SpinUpR              motor         5               
// GYRO                 inertial      6               
// Q                    digital_out   B               
// L1                   motor         14              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "manualcontrol.h"
#include "basics.h"
#include "move.h"
#include "auto.h"
using namespace vex;
competition Competition;
#define debug 1      
//1为调试，0为比赛
extern double z;
void pre_auton(void) {GYRO.calibrate();
  vexcodeInit();
  Q.set(true);
}



void autonomous(void) {

Auto_2();
}

void usercontrol(void) {

  Controller1.Screen.setCursor(2,1);
  Controller1.Screen.print("收集");
  while (1) {
#ifdef debug
  if(Controller1.ButtonUp.pressing() )
  { 
    //Auto_3();
 
        
  Auto_2();
  }

    chassis(_direction());//底盘
    shoot();//摩擦轮
    pick();//收集盘
    rollroll();//推盘
    QQ();//气缸



#else

    chassis(_direction());//底盘
    shoot();//摩擦轮
    pick();//收集盘
    rollroll();//推盘
    //Hidden_Skills();
    //Parameter();//参数显示
#endif
  wait(20, msec); 
  }
}


int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  
  // Run the pre-autonomous function.
  pre_auton();
  GYRO.calibrate();
  
  pid_init();
  // Prevent main from exiting with an infinite loop.
  while (true) {
  // if(Controller1.ButtonDown.pressing() )
  // { 
  //   GYRO.calibrate();
  // }
  // Controller1.Screen.setCursor(1,1);
  // Controller1.Screen.print(GYRO.heading(degrees));
    wait(100, msec);
  }
}
