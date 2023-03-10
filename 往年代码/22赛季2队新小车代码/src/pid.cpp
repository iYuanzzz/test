#include "pid.h"

float pid_calculate(_pid*pid,float Set,float Actual)
{
  pid->err=Set-Actual;
  pid->out+=pid->p*(pid->err-pid->err_last)
           +pid->i*pid->err
           +pid->d*(pid->err-2*pid->err_last+pid->err_last2);
  pid->err_last2=pid->err_last;
  pid->err_last=pid->err;
  if(pid->out>200) pid->out=200;
  else if(pid->out<-200) pid->out=-200;
  // if(pid->out < 40 && pid->out > 0)pid->out = 40;
  // if(pid->out > -40 && pid->out < 0)pid->out = -40;
  return pid->out;
}
float pid_calculate2(_pid*pid,float Set,float Actual)
{
  pid->err=Set-Actual;
  pid->out=pid->p*pid->err
           +pid->i*pid->integal
           +pid->d*(pid->err-pid->err_last);
  pid->integal+=pid->err;
  pid->err_last=pid->err;
  if(pid->integal>90) pid->integal=90;
  else if(pid->integal<-90) pid->integal=-90;
  if(pid->out>200) pid->out=200;
  else if(pid->out<-200) pid->out=-200;
  if(pid->out < 30 && pid->out > 0)pid->out = 30;
  if(pid->out > -30 && pid->out < 0)pid->out = -30;
  return pid->out;
}
float pid_calculate3(_pid*pid,float Set,float Actual)
{
  pid->err=Set-Actual;
  pid->out=pid->p*pid->err
           +pid->i*pid->integal
           +pid->d*(pid->err-pid->err_last);
  pid->integal+=pid->err;
  if(pid->integal>7000) pid->integal=7000;
 
  pid->err_last=pid->err;
  // if(pid->integal>90) pid->integal=90;
  // else if(pid->integal<-90) pid->integal=-90;
  if(pid->out < 30 && pid->out > 0)pid->out = 30;
  if(pid->out > -30 && pid->out < 0)pid->out = -30;
  //if(Actual<0.8*Set) pid->out=Set;
  return pid->out;
}

float pid_turn(_pid*pid,float Set,float Actual)
{
  pid->err=Set-Actual;
  if(G.err>180) G.err-=360;
  else if(G.err<-180) G.err+=360;
  pid->out+=pid->p*(pid->err-pid->err_last)
           +pid->i*pid->err
           +pid->d*(pid->err-2*pid->err_last+pid->err_last2);
  pid->err_last2=pid->err_last;
  pid->err_last=pid->err;
  if(pid->out>200) pid->out=200;
  else if(pid->out<-200) pid->out=-200;
  // if(pid->out < 40 && pid->out > 0)pid->out = 40;
  // if(pid->out > -40 && pid->out < 0)pid->out = -40;
  return pid->out;
}
void pid_init()
{
  //速度环
  // LS.p=0.005;//0.02
  // LS.i=1;//0.6
  // LS.d=0.0015;//0.1//0.001
  // RS.p=0.0005;//0.02
  // RS.i=1;//0.6
  // RS.d=0.005;//0.001
  LS.p=0.008;//0.6//0.4
  LS.i=1.33;//1.33
  LS.d=0.002;//0.065
  RS.p=LS.p;
  RS.i=LS.i;
  RS.d=LS.d;

  // L.p=0.1;
  // L.i=0.1;
  // L.d=0.01;
  // R.p=0.1;
  // R.i=0.1;
  // R.d=0.01;
  L.p=0.001;
  L.i=0.01;
  L.d=0.001;
  R.p=0.001;
  R.i=0.01;
  R.d=0.001;


  G.p=0.5;//0.5
  G.i=0.015;//0.015
  G.d=0.2;//0.2

  UpL.p=0.3;//0.3
  UpL.i=0.07;//0.07
  UpL.d=0.33;//0.5
}
void turn_init()
{
  G.p=0.5;//0.5
  G.i=0.015;//0.015
  G.d=0.2;//0.2
  G.out=0;
  G.err=0;
  G.err_last=0;
  G.err_last2=0;
}
