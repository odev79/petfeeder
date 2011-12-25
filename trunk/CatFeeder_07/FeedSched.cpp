
#include "FeedSched.h"


stFeed mSchedule[ScheduleSets][ScheduleFeeds];    //4 Sets and each with up to 16 Feeds


void FeedSched::ClearSet(int SetN)
{
   InitCyclicSchedule(SetN,ScheduleFeeds-1,0,0);
}

void FeedSched::InitCyclicSchedule(int FeedsCount, int FeedInterval, int FeedDur)
{
    InitCyclicSchedule(ActiveSet,FeedsCount, FeedInterval, FeedDur);
}

void FeedSched::InitCyclicSchedule(int SetN, int FeedsCount, int FeedInterval, int FeedDur)
{
  if (FeedsCount>=ScheduleFeeds)
    FeedsCount=ScheduleFeeds-1;
  int FeedTime=0;  
  for (int i=0; i<FeedsCount; i++)
  {
    SetFeed(SetN,i,FeedTime,FeedDur);
    FeedTime+=FeedInterval;
  }
  
  for (int i=FeedsCount; i<ScheduleFeeds; i++)
    SetFeed(SetN,i,0,0);
  
}

void FeedSched::SetFeed(int SetN, int FeedN, int FeedTime, int FeedDur)
{
  
  DEBUG_PRINT("SetSchedule Set:");
  DEBUG_PRINT(SetN);
  DEBUG_PRINT(" FeedN:");
  DEBUG_PRINT(FeedN);
  DEBUG_PRINT(" FeedTime:");
  DEBUG_PRINT(FeedTime);
  DEBUG_PRINT(" FeedDur:");
  DEBUG_PRINTLN(FeedDur);
  
  mSchedule[SetN-1][FeedN].FeedTime=FeedTime;
  mSchedule[SetN-1][FeedN].FeedDur=FeedDur; 
}


void FeedSched::OnRise()
{
    CurrSeconds = 0;
}

void FeedSched::OnTimer(int SecondsPassed)
{
    CurrSeconds += SecondsPassed;
    
    IsMotorOn=false;  
 
    if (ActiveSet>0) 
    {  
      
//      DEBUG_PRINT("OnTime");
//      DEBUG_PRINTLN(CurrSeconds);
      
      for (int i=0; i<ScheduleFeeds; i++)
      {
         stFeed fi= mSchedule[ActiveSet-1][i];
         if (fi.FeedDur==0)
           break;    //end of feeds
         
//         DEBUG_PRINT("Check i ");
//         DEBUG_PRINTLN(i);
         if (CurrSeconds>=fi.FeedTime && CurrSeconds < (fi.FeedTime+fi.FeedDur))
         {
             IsMotorOn=true;
             break;
         }
         
      }
    }
    
    
}
