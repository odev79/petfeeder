#ifndef MyLCD_h
#define MyLCD_h

#include "MyDebug.h"
#include <LiquidCrystal.h>
#include "Arduino.h"

#define CharsPerRow 16
#define Rows 2

#define LCDCharSched '\1'
#define LCDCharSun '\2'
#define LCDCharMoon '\3'
#define LCDCharBatCharg '\4'
#define LCDCharBatHalf '\5'
#define LCDCharBatEmpt '\6'
#define LCDCharMotorOn '\7'


//#define HelloText "\3\1\5\1\7\4\6\2\1    "


class MyLCD
{

  public:
    //char CurrChars [Rows][CharsPerRow+1];        
  
    LiquidCrystal GetLCD();
  
    void InitLCD(uint8_t rs,  uint8_t enable,
			   uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
  
    void PrintSleepScreen(
          float EVal, float BVal,  bool IsCharge, bool IsDay,
          int CurrSchSetN, unsigned int CurrSeconds, bool IsMotorOn 
                        );

    void PrintRow(int RowN, String Text2Print, bool BlinkCursor);
    void PrintRowBuffer(int RowN);
    
    void Clear();
    void Begin();
    void NoBlink();

  private:
    //char NewChars [Rows][CharsPerRow];
    char RowBuf[CharsPerRow+1];
//    int CursPos;
   
    void InitMyLCDChars();
    void ClearRowBuf(); 
    void FormatFNumb(float FNumb, int IntDigN, int FracDigN, char Buff[], int * BuffOff);
    void FormatNDig(int Numb, int DigNumb, char Buff[], int BuffOff);
    
};


#endif
