#ifndef ChargeControl_h
#define ChargeControl_h

#include "Arduino.h"

#define LevNightDay 4    //Volt
#define NightDayHysteresis 1   //Prevent twilight bouncing.
#define LevBat 6.85   //Volt
#define kVExt 0.013572
#define kVBat 0.00983
 
#define AvgKS 0.99f    //0.8 - 15 Cycles,  0.95 is good for 60 Cycles
//#define AvgKA 0.2f    //AvgKS + AvgKA = 1


class ChargeControl
{
    public :
      
      int ChargePin;
      int VExtPin;
      int VBatPin;    
    
      bool IsDay;
      bool IsCharging;
      float VBat;
      float VExt;
      
      void InitCharger(int pChargePin, int pVExtPin, int pVBatPin);
      void DoControl();
      void SetCharge(bool OnFlag);
      
     // int InitCharger (int ChargePin);
      
  
    private :
      float SAn;
      float AvgKA;
      float LevNigth;
      float LevDay;
};

#endif
