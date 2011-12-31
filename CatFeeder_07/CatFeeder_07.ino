#include <LiquidCrystal.h>

#include "LowPower.h"

#include <EEPROM.h>
#include "MyEEPROM.h"
#include "ChargeControl.h"
#include "FeedSched.h"
#include "KeyPad.h"
#include "MyLCD.h"
#include "MyDebug.h"


#define EEPROMADDR_DefSched 0

#define KeyStandByTime 10

#define wakePin 2                 // pin used for waking up, Allowed values 2 and 3

#define KeyPadPin  0
#define VExtPin  1
#define VBatPin  2
#define ChargePin  12
#define MotorPin 10

/////// LCD Connection /////////
// Vss GND - LCD(1)
// Vdd - LCD(2)
// Vo Contrast - LCD(3)
#define LCD_RSPin  9   //-LCD(4)
//  R/W (Connect Vss LCD(1)) - LCD(5)
#define LCD_EnablePin  8  //LCD(6)
#define LCD_D4Pin  7  //LCD(7)
#define LCD_D5Pin  6  //LCD(8)
#define LCD_D6Pin  5  //LCD(9)
#define LCD_D7Pin  4  //LCD(10)

#define SecondsPerCycle 1


boolean WokeByKey = false;
bool IsDay=false;

int KeyInterruptCode = wakePin-2;

ChargeControl mCharger;
KeyPad mKey;
MyLCD mLCD;
FeedSched mFeedSched;

MyEEPROM mEEPR;

void wakeUpNow()        // here the interrupt is handled after wakeup

{
 
  detachInterrupt(KeyInterruptCode);
  
    WokeByKey =true;
    mKey.BlockWakeUpKey();
    mLCD.Begin();

}

void sleepNow()
{
    WokeByKey = false;
    mKey.ResetKeyPad();
    attachInterrupt(KeyInterruptCode, wakeUpNow, LOW);
    
    DEBUG_PRINTLN("prepare sleep") ; 

#ifdef DEBUG    
    delay(1000);    
#endif
#ifndef DEBUG
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);  
#endif  

}



void setup() {
  
  #ifdef DEBUG
    Serial.begin(9600);    
    Serial.println("Start Debug");
  #endif
 
  { 
    int FeedsCount,FeedInterval,FeedDur;
    mEEPR.ReadCyclSched(&FeedsCount,&FeedInterval,&FeedDur);
    if(FeedsCount>0) 
    {
      mFeedSched.ActiveSet=1;
      mFeedSched.InitCyclicSchedule(FeedsCount,FeedInterval,FeedDur);
    }
    mFeedSched.OnRise();
  }
  
  mCharger.InitCharger(ChargePin,VExtPin,VBatPin);    
  mKey.InitKeyPad(KeyPadPin,KeyStandByTime,&mFeedSched);
  mLCD.InitLCD(LCD_RSPin,LCD_EnablePin,LCD_D4Pin,LCD_D5Pin,LCD_D6Pin,LCD_D7Pin);
  
  attachInterrupt(KeyInterruptCode, wakeUpNow, LOW);
    
}

void loop() {
    
  if(WokeByKey)
  {
    
    mKey.ProcessKey();
    mLCD.PrintRow(1,mKey.LCDRow1,false);
    mLCD.PrintRow(2,mKey.LCDRow2,true);

    if (mKey.CheckStandby())
    {
      mLCD.NoBlink();
      sleepNow();
    } 
  }
  else
  {
    mCharger.DoControl();

    if(mCharger.IsDay && !IsDay)
    {
       DEBUG_PRINTLN("good morning");
       mLCD.Begin();   
       mLCD.PrintRow(1,"Good Morning",false);
       
       IsDay=true;
       mFeedSched.OnRise();  
    }
    
    else
    {
      if (!mCharger.IsDay)
        IsDay=false;
      
      mFeedSched.OnTimer(SecondsPerCycle);
      
      digitalWrite(MotorPin,mFeedSched.IsMotorOn ? HIGH : LOW );
      
      DEBUG_PRINTLN("print sleep lcd");
      
      mLCD.PrintSleepScreen(
          mCharger.VExt,mCharger.VBat,mCharger.IsCharging, mCharger.IsDay,
          mFeedSched.ActiveSet,mFeedSched.CurrSeconds,mFeedSched.IsMotorOn
                            );
  
    }
    
    sleepNow();
  } 
 
}


