#include "move.h"
void Auto_1()
{
    //第一次射环
       PSpeed(200);
       go(470,90);
       wait(300,msec);
       Turn(174);
       wait(300,msec);
       SpinUp.spin(forward,385,rpm);
       SpinUpR.spin(forward,385,rpm);
       wait(2500,msec);
       Ready.spin(forward,35,rpm);
       wait(5000,msec);
       SpinUp.spin(forward,0,rpm);
       SpinUpR.spin(forward,0,rpm); 
       Ready.spin(forward,0,rpm);  

//穿过得分区      

       Turn(153);
       wait(300,msec);
       go(580,120);
       wait(300,msec);
       Turn(236);
       wait(300,msec);
       go(1740,120);

       Turn(324);

       SpinUp.spin(forward,-100,rpm);
       SpinUpR.spin(forward,-100,rpm); 
       wait(200,msec);
       go(1230,120);
       wait(200,msec);
       PSpeed(0);
       Turn(54);
       go(-90,-100);

       //第一次导入
       wait(3300,msec);
       SpinUp.spin(forward,390,rpm);
       SpinUpR.spin(forward,390,rpm);
       go(680,70);

       Turn(202);
     

       wait(1000,msec);
       Ready.spin(forward,35,rpm);
       wait(5000,msec);
}
void Auto_2()
{
  //第一次射环
  PSpeed(180);
  go(420,50);  //470
  wait(500,msec);
  Turn(-150);
  wait(300,msec);
  SpinUp.spin(forward,435,rpm);//385
  SpinUpR.spin(forward,435,rpm);
  wait(1800,msec);
  Ready.spin(forward,35,rpm);//35
  wait(4500,msec);
  SpinUp.spin(forward,0,rpm);
  SpinUpR.spin(forward,0,rpm); 
  Ready.spin(forward,0,rpm); 
  wait(300,msec);

  Turn(-48);
  wait(500,msec);
  all_coast();
  wait(300,msec);
  go(610,40);//600
  Turn(-132);

  SpinUp.spin(forward,401,rpm);//385
  SpinUpR.spin(forward,401,rpm);
  wait(2000,msec);
  Ready.spin(forward,70,rpm);
  wait(3500,msec);
  SpinUp.spin(forward,0,rpm);
  SpinUpR.spin(forward,0,rpm); 
  Ready.spin(forward,0,rpm); 
  wait(300,msec);
  PSpeed(0);
  Turn(6);
  wait(300,msec);
  go(-1200,-100);//撞墙
   PSpeed(-80);
  Turn(80);//80
  go(1230,100);//去roller
  PSpeed(0);
  Turn(170);
  PSpeed(15);
  go(150,50);
  wait(1000,msec);
  go(-30,-50);
  Turn(135);
}

void Auto_3()//技能赛
{
  //射出导入环
 /* SpinUp.spin(forward,342,rpm);
  SpinUpR.spin(forward,342,rpm);
  wait(2000,msec);
  Ready.spin(forward,35,rpm);//35
  wait(5000,msec);
  SpinUp.spin(forward,0,rpm);
  SpinUpR.spin(forward,0,rpm); 
  Ready.spin(forward,0,rpm); 
  wait(300,msec);*/
   wait(300,msec);
   Turn(-2);
  go(1390,50);
  wait(300,msec);
   PSpeed(-20);
   wait(1000,msec);
    PSpeed(0);
    go(-270,-50);
    Turn(90);
     go(370,50);
      PSpeed(20);
   wait(1000,msec);
    PSpeed(0);
}