#include "vex.h"
#include "basics.h"
#include "manualcontrol.h"
#include "move.h"
int shoot_lock=1;
bool pick_lock=1;
bool roll_lock=1;
bool dire_lock=1;
bool q_lock=1;

bool shoot_enable=1;
bool pick_enable=1;
bool roll_enable=1;
bool q_enable=1;
//bool dire_enable=1;
int count=1;
int k=1;
extern double z;
int _direction()
{
  if(Controller1.ButtonRight.pressing() && dire_lock==1)
  {
      k = -k;
      if(k==1)
      {
        Controller1.Screen.setCursor(2,1);
        Controller1.Screen.print("收集");
      }
      else{
        Controller1.Screen.setCursor(2,1);
        Controller1.Screen.print("开炮");
      }
      dire_lock = 0;
  }

  else if(Controller1.ButtonRight.pressing()==0)
  {
    dire_lock = 1;
  }  
  return k;
}
void chassis(int Direction)
{
  double x = Controller1.Axis1.position(pct);
  double y = Controller1.Axis3.position(pct);
  if(fabs(x)<5) x=0;
  if(fabs(y)<5) y=0;
  if(Controller1.ButtonY.pressing())
  {
    y=0;
    x=-20;
  }
  else  if(Controller1.ButtonA.pressing())
  {
    y=0;
    x=20;
  }
  LSpeed(Direction*1.8*y+0.75*x);  
  RSpeed(Direction*1.8*y-0.75*x);  

}
void shoot()
{ 

 if(Controller1.ButtonR1.pressing() && shoot_lock==1)
  {
    if(shoot_enable)
    {
       SpinUp.spin(forward,350,rpm);
       //SpinUpR.spin(forward,300,rpm);
       shoot_lock = 2;
       shoot_enable = 0;
       Controller1.Screen.setCursor(1,1);
       Controller1.Screen.print("350");
    }
  }

  else if(Controller1.ButtonR1.pressing() && shoot_lock==2)
  {
    if(shoot_enable)
    {
       SpinUp.spin(forward,400,rpm);
       //SpinUpR.spin(forward,350,rpm);
       shoot_lock = 3;
       shoot_enable = 0;
       Controller1.Screen.setCursor(1,1);
       Controller1.Screen.print("400");
    }
  }
   else if(Controller1.ButtonR1.pressing() && shoot_lock==3)
  {
    if(shoot_enable)
    {
       SpinUp.spin(forward,500,rpm);
       //SpinUpR.spin(forward,400,rpm);
      shoot_lock = 4;
      shoot_enable = 0;
      Controller1.Screen.setCursor(1,1);
      Controller1.Screen.print("500");
    }
  }
  else if(Controller1.ButtonR1.pressing() && shoot_lock==4)
  {
    if(shoot_enable)
    {
       SpinUp.spin(forward,600,rpm);
       //SpinUpR.spin(forward,400,rpm);
      shoot_lock = 5;
      shoot_enable = 0;
      Controller1.Screen.setCursor(1,1);
      Controller1.Screen.print("600");
    }
  }
  
  else if( (Controller1.ButtonR1.pressing() && shoot_lock==5)  ||  Controller1.ButtonX.pressing() )
  {
    if(shoot_enable)
    {
      SpinUp.stop(coast);
      //SpinUpR.stop(coast);
      Ready.stop(coast);
      shoot_lock = 1;
      shoot_enable = 0;
      Controller1.Screen.setCursor(1,1);
      Controller1.Screen.print("0");
    } 
  }
  else if(Controller1.ButtonR1.pressing()==0&&Controller1.ButtonB.pressing()==0)
  {
    shoot_enable = 1;
  }
  if(Controller1.ButtonB.pressing())
  {
    SpinUp.spin(forward,-100,rpm);
    //SpinUpR.spin(forward,-100,rpm);
  }
  // else if()
  // {
  //   SpinUp.stop(coast);
  //   SpinUpR.stop(coast);
  // }

}
void Parameter()
{


  
  if(shoot_lock==1)
  {
    //Controller1.Screen.clearScreen(); 
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("0");
  }
  else  if(shoot_lock==2)
  {
    //Controller1.Screen.clearScreen(); 
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("spin 350");
  }
  else  if(shoot_lock==3)
  {
    //Controller1.Screen.clearScreen(); 
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("spin 400");
  }
  else  if(shoot_lock==4)
  {
    //Controller1.Screen.clearScreen(); 
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("spin 450");
  }

 
}
void pick()
{
    if(Controller1.ButtonR2.pressing() && pick_lock)
  {
    if(pick_enable)
    {
      PSpeed(200);
       Ready.spin(forward,-180,rpm);
      pick_lock = 0;
      pick_enable = 0;
    }
  }
  else if(Controller1.ButtonR2.pressing() && !pick_lock)
  {
    if(pick_enable)
    {
      L_Pick.stop(coast);
      Ready.stop(coast);
      //R_Pick.stop(coast);
      pick_lock = 1;
      pick_enable = 0;
    } 
  }
  else if(Controller1.ButtonR2.pressing()==0&&Controller1.ButtonL2.pressing()==0)
  {
    pick_enable = 1;
  }
  if(Controller1.ButtonL2.pressing())
  {
    PSpeed(-200);//反转
  }
  else if(pick_lock == 1&&pick_enable == 1)
  {
      L_Pick.stop(coast);
      //R_Pick.stop(coast);
  }
}

void rollroll()
{

  if(Controller1.ButtonL1.pressing() && roll_lock)
  {
    if(roll_enable)
    {
      Ready.spin(forward,180,rpm);
      //PSpeed(0);
      roll_lock = 0;
      roll_enable = 0;
    }
  }
  else if(Controller1.ButtonL1.pressing() && !roll_lock)
  {
    if(roll_enable)
    {
      Ready.stop(coast);
      roll_lock = 1;
      roll_enable = 0;
    } 
  }
  else if(Controller1.ButtonL1.pressing()==0)
  {
    roll_enable = 1;
  }
}
void Spin180()
{
  if(Controller1.ButtonUp.pressing())
  {
    double stand_z=GYRO.heading(degrees);

    if(stand_z>180)
    {
      z=GYRO.heading(degrees);
      while((z-stand_z+180)>2)
      {
        pid_calculate(&G,stand_z-180,z);
        LSpeed(-G.out);
        RSpeed(G.out);
        if(Controller1.ButtonDown.pressing()) break;
      }
      all_hold();
    }

  }
}  

void Hidden_Skills()
{
  if(Controller1.ButtonLeft.pressing()) 
  {
    go(500,120,1);
  }
}
void QQ()
{

    if(Controller1.ButtonLeft.pressing()&& q_lock)
  {
    if(q_enable)
    {
      Q.set(true);
      q_lock = 0;
      q_enable = 0;
    }
  }
  else if(Controller1.ButtonLeft.pressing() && !q_lock)
  {
    if(q_enable)
    {
      Q.set(false);
      q_lock = 1;
      q_enable = 0;
    } 
  }
  else if(Controller1.ButtonLeft.pressing()==0)
  {
    q_enable = 1;
  }
}



