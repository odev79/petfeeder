


#include "KeyPad.h"
#include "MyEEPROM.h"


char mKeys[mKeyCount+1]="123A456B789C*0#D";
int mKeyIntsL[mKeyCount]={0,180,323,408,466,527,575,612,645,673,700,721,745,762,778,793};
int mKeyIntsH[mKeyCount]={2,185,330,416,478,535,593,628,670,696,720,740,761,777,792,804};
int KD;

MyEEPROM _MyEEPROM;

void KeyPad::InitKeyPad(int pKeyPadPin, int pStandByTime, FeedSched *pFS)
{
    mFeedSch = pFS;
    ResetKeyPad();
    
    KeyPadPin = pKeyPadPin;
    
    StandByMillis = pStandByTime*1000;

}

void KeyPad::ResetKeyPad()
{
    CurrState = 0;
    CurrSubState = 0;
    CurrString = "";
    CurrKey = NoKeyChar;
    
    P1 = 0;
    P2 = 0;
    P3 = 0;
    
    LCDRow1="";
    LCDRow2="";
}

void KeyPad::ProcessKey()
{
   char K=ReadKey();
   KD = Char2Digit(K);
   
   

   
   
//   if (K!=NoKeyChar)
   {  
     switch (CurrState)
     {  
       case 0:
       
         LCDRow1 = "A-Sch/B-SetUp";
       
         switch (K)
         {
           case FKeySetCurrSched:
             CurrState = KSTATE_SETCURRSCHED;
             break;
           
           case FKeySetUpSched:
             CurrState = KSTATE_SETUPSCHED;
             CurrSubState = 0;
             break;  
           
           
         }
         break; 
       
       case KSTATE_SETCURRSCHED :
         
         LCDRow1 = "Choose Schedule";
         
         if (KD>=0 && KD < ScheduleSets)
         {
           //Set Current Schedule KD
           (*mFeedSch).ActiveSet=KD;
           CurrState = 0;
         }  
         break;
       
       case KSTATE_SETUPSCHED :
         
         LCDRow1 = "S"+String((*mFeedSch).ActiveSet,DEC)+"~";
         
         switch (CurrSubState)
         {
           case 0:  //Choose Sched Type - Cyclic (1) or OnTime (2),
                    //Cyclic : 1 / OnTime : 4
             
             LCDRow1 += "1Cycl/2OnTime";
                    
             CurrNumber = 0;
             CurrSubState = KD==1 ? 1 : (KD==2 ? 4 : 0) ;
             P1 = 0;
             P2 = 0;
             P3 = 0; 
             break; 
             
           case 1:  //Cyclic Chosen, Choose FeedsCount
           
             LCDRow1 += "Count";
           
             NumbEntering (K,2,0,&P1);
             break;
             
           case 2:  //Cyclic Chosen, Choose FeedsInterval
           
             LCDRow1 += "Interval";
           
             NumbEntering (K,3,1,&P2);
             break;
            
           case 3:  //Cyclic Chosen, Choose FeedDur
           
             LCDRow1 += "Duration";
           
             NumbEntering (K,0,2,&P3);
             if (CurrSubState == 0)
             {
               InitCyclicSchedule(P1,P2*60,P3); 
               CurrState = 0;
             }
             break;

//           case 4:  //OnTime Chosen, Choose FeedN
//           
//           case 5:  //OnTime Chosen, Choose FeedTime
//           
//           case 6:  //OnTime Chosen, Choose FeedDur
           
         }
       
         
         break;
       
        
       default :
         break;
         
     } 
   }
  
   if (CurrState == KSTATE_SETUPSCHED)
   {
     LCDRow2="";
     
     if (CurrSubState >= 1)
       LCDRow2 = "C";
     if (CurrSubState >= 2)  
       LCDRow2 += String(P1,DEC) + "|I";
     if (CurrSubState >= 3)
       LCDRow2 += String(P2,DEC) + "|D";

   
     LCDRow2 += CurrString;
     
 //    LCDRow2 +=".";
     
   }  
   else 
     LCDRow2= ""; //CurrString;
     
}



void KeyPad::InitCyclicSchedule(int FeedsCount, int FeedInterval, int FeedDur)
{
    _MyEEPROM.SaveCyclSched(FeedsCount,FeedInterval,FeedDur);    
   (*mFeedSch).InitCyclicSchedule(FeedsCount,FeedInterval,FeedDur);
 
}

void KeyPad::NumbEntering(char K, int NextSubState, int PrevSubState, int *P)
{
  if (KD>=0)
  {
    CurrNumber = CurrNumber * 10 + KD;
    CurrString = String(CurrNumber,DEC);
  }
  else
  {  
    if (K == FKeyOK)
    {
      *P=CurrNumber;
      CurrNumber=0;
      CurrString="";      
      CurrSubState = NextSubState;
    }
    else  
      if (K == FKeyCancel)
      {
        if (CurrString.length()>0)
        {
          CurrString = "";
          CurrNumber = 0;
        }
        else
          CurrSubState = PrevSubState;
      }
  }
}


char KeyPad::ReadKey()
{
  
  
   char K=ReadKey(mKeyReads,mKeyReadDelay);
   if (
         ( CurrKey==NoKeyChar ? K!=NoKeyChar : K==NoKeyChar ) &&
         ((millis()-PrevKeyMillis)>DebounceMillis)
      )
    {
      PrevKeyMillis = millis(); 
      CurrKey = K;  
      return (CurrKey);    
  //    if(K=='#')
  //      sleepNow(); 
  
      
    }
    else
      return(NoKeyChar);
      
}


void KeyPad::BlockWakeUpKey()
{
   CurrKey = BlockKeyChar;
}


char KeyPad::ReadKey(int KeyReads, int KeyReadDelay) 
{
   char ret=NoKeyChar;
   int ai;
   int aiMin=1024, aiMax=0;
   float aiAvr=0;
   for (int i=0;i<KeyReads;i++)
   {
      ai=analogRead(KeyPadPin);
      if (ai<aiMin)
        aiMin=ai;
      if (ai>aiMax)
        aiMax=ai;
      aiAvr+=ai;
      delay(KeyReadDelay);
   }
   aiAvr/=(float)mKeyReads;
   float dev;
   if (aiAvr==0)
     dev=0;
   else
     dev=(aiMax-aiMin)/aiAvr;
   if (dev<KeyReadPrec)
   {
     ai=aiAvr;
     for (int i=0;i<mKeyCount;i++)
     {
       if(ai>=mKeyIntsL[i] and ai<=mKeyIntsH[i])
       {
           ret=mKeys[i];
           break;
       }
     }
   }
  return(ret);  
  
  
  
}

int KeyPad::Char2Digit(char K)
{
   int r=K-'0';
   if (r<0 || r>9)
     r=-1;
   return(r);
}


bool KeyPad::CheckStandby()
{
   return((millis()-PrevKeyMillis)>StandByMillis); 
}
