#ifndef _BNO055_DRIVER_
#define _BNO055_DRIVER_
#include "rtwtypes.h"

extern uint8_T i;        
extern uint8_T data[24]; 
   
extern uint8_T iterator; 
extern uint16_T coeff[8];
extern float Yaw; 
extern float Roll;
extern float Pitch;
extern float all[6];
extern float Gyro_x;    
extern float Gyro_y;  
extern float Gyro_z;

void Dontwait(void);

void WhyWait(void);

void HitIt(float* hey);

void sleepAbit(void);

#endif
