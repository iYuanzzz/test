#ifndef __MOVE_H
#define __MOVE_H
#include "vex.h"
#include "basics.h"
#include "pid.h"

void Pick(double Set,double speed=200);
void Turn(double Angle);
void Straight(float Set,float Speed);//串级
void straight(float Set);
void Shoot_Shoot(double Set,double speed=400);//所传参数均为正值,参数一为时间，单位ms
void Push(double Set,double speed=200);//所传参数均为正值,参数一为时间，单位ms
void Shoot_Push(double Set1,double Set=3000);//所传参数均为正值,参数一为时间，单位ms
void go(double site,double speed,bool mode=0);

#endif
