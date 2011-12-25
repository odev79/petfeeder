

#include "ChargeControl.h"


void ChargeControl::InitCharger(int pChargePin, int pVExtPin, int pVBatPin)
{
    ChargePin = pChargePin ;
    VExtPin = pVExtPin;
    VBatPin = pVBatPin;    
    
    IsDay=false;
    IsCharging = false;
    
    VBat = 0;
    VExt = 0;
    
    AvgKA = 1 - AvgKS;
    LevNigth = LevNightDay - NightDayHysteresis ;
    LevDay = LevNightDay + NightDayHysteresis ;  
    SAn=0; //analogRead(VExtPin);
    
    
}

void ChargeControl::DoControl()
{
    
    SetCharge(false);
    
    VExt=kVExt*analogRead(VExtPin);
    VBat=kVBat*analogRead(VBatPin);
    
    if((VExt>VBat) && (VBat<LevBat))
        SetCharge(true);
    
    SAn=AvgKS*SAn+AvgKA*VExt;    
    IsDay = IsDay ? SAn >= LevNigth : SAn > LevDay;
    
}


void ChargeControl::SetCharge(bool OnFlag)
{
  IsCharging=OnFlag;
  digitalWrite(ChargePin,(OnFlag ? HIGH : LOW));
}
