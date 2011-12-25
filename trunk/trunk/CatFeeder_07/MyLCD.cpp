
#include "MyLCD.h"



LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

//String CurrRows[Rows];


//char TimeChars[9];

void MyLCD::InitLCD(uint8_t rs,  uint8_t enable,
			   uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
{
  lcd.init(1, rs, 255, enable, d0, d1, d2, d3, 0, 0, 0, 0);
  InitMyLCDChars();
  
  
//  TimeChars[2]=':';
//  TimeChars[5]=':';
//  TimeChars[8]=0;
  
  lcd.begin(CharsPerRow, Rows);
}


LiquidCrystal MyLCD::GetLCD()
{
   return(lcd); 
}

void MyLCD::Begin()
{
   lcd.begin(CharsPerRow, Rows); 
}


void MyLCD::Clear()
{
   lcd.clear(); 
}

void MyLCD::PrintSleepScreen(
      float EVal, float BVal, bool IsCharge, bool IsDay,
      int CurrSchSetN, unsigned int CurrSeconds, bool IsMotorOn 
                            )
{
    
     static int CurrHour, CurrMin;  
     static int CursPos;  
     static int tmpI;
  
//    lcd.clear();
//    
    
    
    ClearRowBuf();
    CursPos = 0 ;
    RowBuf[CursPos++]=(IsCharge?LCDCharBatCharg:LCDCharBatHalf);
    
    RowBuf[CursPos++]='E';
    FormatFNumb(EVal,2,2,RowBuf, &CursPos);

    RowBuf[CursPos++]='B';
    FormatFNumb(BVal,1,2,RowBuf, &CursPos);
    
    lcd.setCursor(0, 0);    
    lcd.print(RowBuf);
    
    DEBUG_PRINT("LCD Row 1:") ; 
    DEBUG_PRINTLN(RowBuf) ; 
    

    ClearRowBuf();
    CursPos = 0 ;
    RowBuf[CursPos++]=(IsDay?LCDCharSun:LCDCharMoon);
    RowBuf[CursPos++]=CurrSchSetN>0 ? LCDCharSched : ' ';
    RowBuf[CursPos++]=CurrSchSetN>0 ? ('0'+CurrSchSetN) : ' ';
    RowBuf[CursPos++]=IsMotorOn ? LCDCharMotorOn : ' ';
    RowBuf[CursPos++]='T';  
    
    CurrHour = CurrSeconds / 3600;
    CurrMin = (CurrSeconds - CurrHour * 3600) / 60 ;
    FormatNDig(CurrHour,2,RowBuf,CursPos);
    CursPos += 2;
    RowBuf[CursPos++] = ':' ;
    FormatNDig(CurrMin,2,RowBuf,CursPos);
    CursPos += 2;
    RowBuf[CursPos++] = ':' ;
    FormatNDig(CurrSeconds - (CurrHour * 60 + CurrMin) * 60 , 2,RowBuf, CursPos) ;
    
    lcd.setCursor(0, 1);
    lcd.print(RowBuf);
    
    DEBUG_PRINT("LCD Row 2:") ; 
    DEBUG_PRINTLN(RowBuf) ;
    
//    lcd.print(CurrSeconds);
//    lcd.print("Mot:");
//    lcd.print(IsMotorOn ? "ON" : "OFF");  
//    lcd.print(" ms:");
//    lcd.print((int)(millis()));
//    lcd.print("   ");
  
}



void MyLCD::ClearRowBuf()
{
    for (int i=0; i<=CharsPerRow; i++)
      RowBuf[i]=0;
}

void MyLCD::FormatFNumb(float FNumb, int IntDigN, int FracDigN, char Buff[], int * BuffOff)
{
    static int tmpI;
    tmpI = FNumb ;
    FormatNDig(tmpI,IntDigN,Buff,*BuffOff);
    (*BuffOff) += IntDigN;
    Buff[(*BuffOff) ++]='.';
    tmpI = (FNumb - tmpI) * 100 ;
    FormatNDig(tmpI,FracDigN,Buff,*BuffOff);
    (*BuffOff) += FracDigN;
}

void MyLCD::FormatNDig(int Numb, int DigNumb, char Buff[], int BuffOff)
{
  for (int i=DigNumb-1; i>=0; i--)
  {
    Buff[BuffOff+i]='0'+Numb%10;
    Numb /= 10;  
  }
}
    
void MyLCD::PrintRow(int RowN, String Text2Print, bool BlinkCursor)
{
//  
//   DEBUG_PRINT("Print LCD Row");
//   DEBUG_PRINT(RowN);
//   DEBUG_PRINT(" Text ");
//   DEBUG_PRINTLN(Text2Print);
//  
   lcd.setCursor(0,RowN-1);
   Text2Print.toCharArray(RowBuf,CharsPerRow);
   

   
   if(Text2Print.length()<=CharsPerRow)
     for (int i=Text2Print.length();i<CharsPerRow;i++)
       RowBuf[i]=' ';
   
//   #ifdef DEBUG
//     DEBUG_PRINTLN(Text2Print.length());
//     DEBUG_PRINTLN(CharsPerRow);
//     String a2=String(RowBuf);    
//     DEBUG_PRINTLN(a2);
//   #endif
//   

   lcd.print(RowBuf);
   
   if (BlinkCursor)
   {
      lcd.setCursor(Text2Print.length()-1,RowN-1);
      lcd.blink();  
   }
   else
      lcd.noBlink();
   
}

void MyLCD::NoBlink()
{
  lcd.noBlink();
}

void MyLCD::InitMyLCDChars()
{
   byte MyChar[]={
        0x0,0x4,0xe,0x15,0x17,0x11,0xe,0x0,    //1 Schedule 
//        0x0,0x4,0x15,0xe,0x1b,0xe,0x15,0x4,    //2 Sun
//        0x4, 0x4, 0x4, 0x15, 0xa, 0x11, 0xa, 0x15,
//        0x14, 0x3, 0x14, 0xa, 0x9, 0x8, 0x0, 0x0,
        0x0, 0xe, 0x11, 0x11, 0x11, 0x11, 0xe, 0x0,
//        0x0, 0x9, 0x2, 0x6, 0x6, 0x6, 0x2, 0x1,       //3 Moon
//        0x0, 0xe, 0x1d, 0x1d, 0x1d, 0x1d, 0xe, 0x0,
        0x0, 0xe, 0x1d, 0x19, 0x1d, 0x19, 0xe, 0x0,
        0xa, 0x4, 0x0, 0x4, 0xa, 0xa, 0xe, 0xe,    //4 Bat Charging
      	0x0, 0x0, 0x4, 0xa, 0xe, 0xe, 0xe, 0x0,   //5 Bat Half
        0x0,0x0,0x0,0x4,0xa,0xa,0xa,0x0,      // 6 Bat Empty
        0x0, 0x1, 0x0, 0xa, 0x0, 0x4, 0x11, 0xe     //7 Motor On
        
                 };
         
   for (int i=0;i<7;i++)
   {
      lcd.createChar(i+1, MyChar+i*8);
   }
       
                 
        
//        B01000,B01000,B00100,B00010,B00001,B10001,B10001,B01110,
//        B11100,B00100,B00100,B00100,B11011,B10001,B10001,B01110,
//        B11100,B10010,B00010,B01101,B10011,B10001,B10001,B01110,
//        B01001,B00101,B00011,B00110,B01111,B10101,B10100,B11100,
//        B11111,B10001,B10001,B00111,B11001,B10001,B10001,B11110,
//        B01110,B10101,B10101,B10101,B10001,B10001,B10001,B10001,
//        B01010,B10000,B10000,B11110,B10001,B10001,B10001,B10001
               
  
 // MyChar={B01000,B01000,B00100,B00010,B00001,B10001,B10001,B01110};
 // MyChar={B11100,B00100,B00100,B00100,B11011,B10001,B10001,B01110};

  
  
}
