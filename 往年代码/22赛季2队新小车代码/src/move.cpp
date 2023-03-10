#include "pid.h"
#include "basics.h"
 _pid L;
 _pid R;
 _pid LS;
 _pid RS;
 _pid T;
 _pid TS;
 _pid G;
 _pid UpL;
double z;
void straight(float Set)
{
  float Rotation[2];
  // float Velocity[2];
  z=GYRO.heading(degrees);
  all_reset();
  do
  {
    Rotation[0]=(L1.position(degrees)+L2.position(degrees)+L3.position(degrees))/3;
    Rotation[1]=(R1.position(degrees)+R2.position(degrees)+R3.position(degrees))/3;
    // Velocity[0]=(L1.velocity(rpm)+L2.velocity(rpm)+L3.velocity(rpm));
    // Velocity[1]=(R1.velocity(rpm)+R2.velocity(rpm)+R3.velocity(rpm));
    pid_calculate(&L,Set,Rotation[0]);
    pid_calculate(&R,Set,Rotation[0]);
    LSpeed(L.out);
    RSpeed(R.out);
  }while(fabs(L.err+R.err)>20);
  all_hold();
}

void Straight(float Set,float Speed)//串级
{

  float Rotation[2];
  float Velocity[2];
  double z_err;
  z=GYRO.heading(degrees);
  all_reset();
  do
  {
    z_err=GYRO.heading(degrees)-z;
    
    Rotation[0]=((L1.position(degrees)+L2.position(degrees)+L3.position(degrees))/3);//获取位置
    Rotation[1]=(R1.position(degrees)+R2.position(degrees)+R3.position(degrees))/3;
    Velocity[0]=(L1.velocity(rpm)+L2.velocity(rpm)+L3.velocity(rpm))/3;//获取速度
    Velocity[1]=(R1.velocity(rpm)+R2.velocity(rpm)+R3.velocity(rpm))/3;

    pid_calculate2(&L,Set,Rotation[0]);//算出期望速度
    pid_calculate2(&R,Set,Rotation[1]);

    pid_calculate2(&LS,L.out,Velocity[0]);//速度闭环
    pid_calculate2(&RS,R.out,Velocity[1]);

    if(fabs(LS.out) > fabs(Speed) && LS.out*Speed>0) LS.out = Speed;
    if(fabs(RS.out) > fabs(Speed) && RS.out*Speed>0) RS.out = Speed;
    // LS.out+=Velocity[1]-Velocity[0];//-z_err*z_err;
    // RS.out+=Velocity[0]-Velocity[1];//+z_err*z_err;   
    LSpeed(LS.out);
    RSpeed(RS.out);
    Controller1.Screen.clearScreen(); 
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print(L.out);
    Controller1.Screen.setCursor(2,1);
    //Controller1.Screen.print(L.err);
    Controller1.Screen.print(Rotation[0]);
    Controller1.Screen.setCursor(3,1);
    Controller1.Screen.print(Velocity[1]);
  

  }while(fabs(L.err+R.err)>100);
    all_hold();
}
void go(double site,double speed,bool mode=0)
{
  float Rotation[2];
  all_reset();
  if(mode==0)
  {
      if(site>0)
    {
        do
        {
          Rotation[0]=((L1.position(degrees)+L2.position(degrees)+L3.position(degrees))/3);//获取位置
          Rotation[1]=(R1.position(degrees)+R2.position(degrees)+R3.position(degrees))/3;
          LSpeed(speed);
          RSpeed(speed);
        }while((Rotation[0]+Rotation[1])/2<site);
    }
    else if(site<0)
    {
      do
        {
          Rotation[0]=((L1.position(degrees)+L2.position(degrees)+L3.position(degrees))/3);//获取位置
          Rotation[1]=(R1.position(degrees)+R2.position(degrees)+R3.position(degrees))/3;
          LSpeed(speed);
          RSpeed(speed);
        }while((Rotation[0]+Rotation[1])/2>site);
    }
  }
  else if(mode==1)//手动隐藏技能
  {
      if(site>0)
      {
          do
          {
            Rotation[0]=((L1.position(degrees)+L2.position(degrees)+L3.position(degrees))/3);//获取位置
            Rotation[1]=(R1.position(degrees)+R2.position(degrees)+R3.position(degrees))/3;
            LSpeed(speed);
            RSpeed(speed);
            if(Controller1.ButtonX.pressing()) break;
          }while((Rotation[0]+Rotation[1])/2<site);
      }
      else if(site<0)
      {
        do
          {
            Rotation[0]=((L1.position(degrees)+L2.position(degrees)+L3.position(degrees))/3);//获取位置
            Rotation[1]=(R1.position(degrees)+R2.position(degrees)+R3.position(degrees))/3;
            LSpeed(speed);
            RSpeed(speed);
            if(Controller1.ButtonX.pressing()) break;
          }while((Rotation[0]+Rotation[1])/2>site);
      }
  }

  all_brake();
}
void k_go(double site,double speed)//一阶线性起步，停止
{
  float Rotation[2];
  double spd;
  bool f=1;
  Brain.Timer.reset();
  all_reset();
  while(fabs((Rotation[0]+Rotation[1])/2)<fabs(site))
  {
    Rotation[0]=(L1.position(degrees)+L2.position(degrees)+L3.position(degrees))/3;//获取位置
    Rotation[1]=(R1.position(degrees)+R2.position(degrees)+R3.position(degrees))/3;
    if(f)
    {
      if(Brain.Timer.time()%5==0) spd+=10;
      if(spd>speed) 
      {
        spd=speed;
        f=0;
      }
    }
    else if (fabs(site-(Rotation[0]+Rotation[1])/2)<200&&f==0)
    { 

      if(Brain.Timer.time()%5==0) spd-=10;
      if(spd>speed) 
      {
        spd=speed;
      }
    }       
    LSpeed(spd);
    RSpeed(spd);
  }
  all_brake();
}
void Turn(double Angle)
{
  turn_init();
  z=GYRO.heading(degrees);
  if(z>180)z-=360;
  float stand_err;
  stand_err = Angle-z;
  // if(stand_err<70) G.p=1;
  do{
      z=GYRO.heading(degrees);
      if(z>180) z-=360;     
      pid_turn(&G,Angle,z);
      LSpeed(G.out);
      RSpeed(-G.out);
      //if(stand_err*G.err<0) break;
      Controller1.Screen.clearScreen(); 
      Controller1.Screen.setCursor(1,1);
      Controller1.Screen.print(G.err);
      Controller1.Screen.setCursor(2,2);
      Controller1.Screen.print(z);
      if(stand_err>0&&G.out<5) G.out=5;
      else if(stand_err<0&&G.out>-5) G.out=-5;
      else if(stand_err>0&&G.out>100) G.out=100;
      else if(stand_err<0&&G.out<-100) G.out=-100;
  }while(fabs(G.err)>2);
  all_hold();
}
void Pick(double Set,double speed=200)//收集盘，所传参数均为正值
{
    while(Set-(L_Pick.position(degrees))>20)
    {
      PSpeed(speed);
    }
    L_Pick.stop(coast);
    R_Pick.stop(coast);
}
void Shoot_Shoot(double Set,double speed=400)//摩擦飞轮，所传参数均为正值,参数一为时间，单位ms
{
    Brain.Timer.reset();
    while(Set-Brain.Timer.time()>20)
    {
      SpinUp.spin(forward,speed,rpm);
      SpinUp.spin(forward,speed,rpm);
    }
    SpinUp.stop(coast);
    SpinUpR.stop(coast);
}
void Push(double Set,double speed=200)//开炮，所传参数均为正值,参数一为时间，单位ms
{
    Brain.Timer.reset();
    while(Set-Brain.Timer.time()>20)
    {
      Ready.spin(forward,speed,rpm);
      Ready.spin(forward,speed,rpm);
    }
    Ready.stop(coast);
}
void Shoot_Push(double Set1,double Set=3000)//飞盘，开炮，所传参数均为正值,参数一为时间，单位ms
{    
    SpinUp.spin(forward,450,rpm);
    SpinUpR.spin(forward,450,rpm);
    wait(Set,msec);
    Brain.Timer.reset();
    while(Set1-(Brain.Timer.time())>20)
    {
      Ready.spin(forward,70,rpm);
    }
    SpinUp.stop(coast);
    SpinUpR.stop(coast);
    Ready.stop(coast);
}

