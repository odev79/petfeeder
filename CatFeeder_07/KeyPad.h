#ifndef KeyPad_h
#define KeyPad_h

#include "Arduino.h"

#include "FeedSched.h"

#define mKeyCount 16

#define mKeyReads 10
#define mKeyReadDelay 10
#define KeyReadPrec 0.2
#define DebounceMillis 200

#define BlockKeyChar '?'
#define NoKeyChar ' '

#define FKeySetCurrSched 'A'
#define FKeySetUpSched 'B'

#define FKeyOK 'D'
#define FKeyCancel 'C'

#define KSTATE_SETCURRSCHED 1
#define KSTATE_SETUPSCHED 2

class KeyPad
{
   public : 
     //char PrevKey;
     char CurrKey;
     int KeyPadPin;
     int CurrState; //0 - ; 1 - Change Current Schedule Set ; 2 Set Up Schedule Set
     int CurrSubState;  // 0 - Step0, 1 - Step1 , ...
     String CurrString;
     int CurrNumber;
     String LCDRow1;
     String LCDRow2;
     
     FeedSched *mFeedSch;
     
     unsigned long StandByMillis; //=5000;
     
     void InitKeyPad(int pKeyPadPin, int pStandByMillis, FeedSched *pFS);
     void ResetKeyPad();
     void ProcessKey();
     char ReadKey(int KeyReads, int KeyReadDelay);
     char ReadKey();
     void BlockWakeUpKey(); 
     bool CheckStandby();
     
     
  
   private :
  
    unsigned long PrevKeyMillis;
    
    int P1;
    int P2;
    int P3;
    
    int Char2Digit(char K);
    void InitCyclicSchedule(int FeedsCount, int FeedInterval, int FeedDur);
    void NumbEntering(char K, int NextSubState, int PrevSubState, int *P);
};

#endif

