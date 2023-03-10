#ifndef _PID_H
#define __PID_H
#include "vex.h"
#include "basics.h"
typedef  struct {
  float p;
  float i;
  float d;
  float err;
  float err_last;
  float err_last2;
  float out;
  float integal;
}_pid;
extern _pid L;
extern _pid R;
extern _pid LS;
extern _pid RS;
extern _pid T;
extern _pid TS;
extern _pid G;
extern _pid UpL;
float pid_calculate(_pid*pid,float Set,float Actual);
float pid_calculate2(_pid*pid,float Set,float Actual);
float pid_turn(_pid*pid,float Set,float Actual);
float pid_calculate3(_pid*pid,float Set,float Actual);
void pid_init(void);
void turn_init(void);
#endif