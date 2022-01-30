#include "BNO055_driver.h"
#include "MW_I2C.h"
#include "MW_target_hardware_resources.h"

#define BNO055_ADDR 40                                                                                                                       
#define BNO 59

uint8_T data[24] =                                                                                                                           
{0x3D, 0x00, 0x07, 0x01, 0x08, 0x1F, 0x0A, 0x00, 0x0B, 0x00, 0x09, 0x1F, 0x07, 0x00, 0x40, 0x01, 0x3B, 0x01, 0x3E, 0x00, 0x3D,12, 0x07,0x00};
uint8_T i = 0; 
uint8_T temp[6] = {0,0,0,0,0,0};
float all[6] = {0,0,0,0,0,0};                                                                                                                       


 
uint8_T iterator = 0;                                                                                                                        
uint16_T coeff[8] = {0,0,0,0,0,0,0,0};                                                                                                       

void sleepAbit(void)
{
    DELAY_US(500000);
}
void Dontwait(void)
{
    I2caRegs.I2CPSC.all = 9;         
    I2caRegs.I2CCLKL = 95;               
    I2caRegs.I2CCLKH = 95;               
}

 void WhyWait(void)
 {
     I2caRegs.I2CIER.all = 60;
     while (i < 24)
     {
       while (I2caRegs.I2CSTR.bit.BB == 1);        // busy loop (receive or send a start bit)
       I2caRegs.I2CSTR.bit.SCD = 1;                // Clear the SCD bit (stop condition bit)
       while(I2caRegs.I2CMDR.bit.STP == 1);        // make sure the i2c bus has stopped
       I2caRegs.I2CSAR.bit.SAR = BNO055_ADDR;    /* Set slave address*/
       I2caRegs.I2CCNT= 2;              /* Set data length */
       I2caRegs.I2CFFTX.bit.TXFFIL = 2;
       I2caRegs.I2CMDR.all = 28192;
       I2caRegs.I2CDXR.bit.DATA = data[i];
       I2caRegs.I2CDXR.bit.DATA = data[i+1];
       i = i + 2;
       while(I2caRegs.I2CMDR.bit.STP == 1);
       I2caRegs.I2CFFTX.bit.TXFFINTCLR = 1;
       DELAY_US(500);
     }
 }
// 
 void HitIt(float* hey)
 {
     while (I2caRegs.I2CSTR.bit.BB == 1);
     I2caRegs.I2CSTR.bit.SCD = 1;
     while(I2caRegs.I2CMDR.bit.STP == 1);
     I2caRegs.I2CCNT= 1;
     I2caRegs.I2CFFTX.bit.TXFFIL = 1;
     I2caRegs.I2CMDR.all = 28192;
     I2caRegs.I2CDXR.bit.DATA = 0x14;
     while(I2caRegs.I2CMDR.bit.STP == 1);
     I2caRegs.I2CFFTX.bit.TXFFINTCLR = 1;
     while (I2caRegs.I2CSTR.bit.BB == 1);
     I2caRegs.I2CSTR.bit.SCD = 1;
     while(I2caRegs.I2CMDR.bit.STP == 1);
     I2caRegs.I2CCNT= 6;
     I2caRegs.I2CMDR.all = 27680;
     for (i = 0; i < 6; i++)
     {
         temp[i] = I2caRegs.I2CDRR.bit.DATA;
     }
     hey[0] = (int16_T)temp[1] << 8 | (int16_T)temp[0];
     hey[1] = (int16_T)temp[3] << 8 | (int16_T)temp[2];
     hey[2] = (int16_T)temp[5] << 8 | (int16_T)temp[4];

     while (I2caRegs.I2CSTR.bit.BB == 1);
     I2caRegs.I2CSTR.bit.SCD = 1;
     while(I2caRegs.I2CMDR.bit.STP == 1);
     I2caRegs.I2CCNT= 1;
     I2caRegs.I2CFFTX.bit.TXFFIL = 1;
     I2caRegs.I2CMDR.all = 28192;
     I2caRegs.I2CDXR.bit.DATA = 0x1A;
     while(I2caRegs.I2CMDR.bit.STP == 1);
     I2caRegs.I2CFFTX.bit.TXFFINTCLR = 1;
     DELAY_US(10);
     while (I2caRegs.I2CSTR.bit.BB == 1);
     I2caRegs.I2CSTR.bit.SCD = 1;
     while(I2caRegs.I2CMDR.bit.STP == 1);
     I2caRegs.I2CCNT= 6;
     I2caRegs.I2CMDR.all = 27680;
     for (i = 0; i < 6; i++)
     {
         temp[i] = I2caRegs.I2CDRR.bit.DATA;
     }
     hey[3] = (int16_T)temp[1] << 8 | (int16_T)temp[0];
     hey[4] = (int16_T)temp[3] << 8 | (int16_T)temp[2];
     hey[5] = (int16_T)temp[5] << 8 | (int16_T)temp[4];
     hey[0] = hey[0]/16;
     hey[1] = hey[1]/16;
     hey[2] = hey[2]/16;
     hey[3] = hey[3]/16;
     hey[4] = hey[4]/16;
     hey[5] = hey[5]/16;
     DELAY_US(10);
     
 }




