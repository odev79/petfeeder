#ifndef FeedSched_h
#define FeedSched_h

#define ScheduleSets 4
#define ScheduleFeeds 16

#include "MyDebug.h"
#include "Arduino.h"

typedef struct 
{
   int FeedTime;  //By Interrupts Count
   int FeedDur;     //By Interrupts Count,
} stFeed ;



class FeedSched
{
  
  public:
    int ActiveSet;  //1-4, 0 - means no active schedule
    bool IsMotorOn;
    //int CurrFeedN;
    
    unsigned int CurrSeconds;

    
    void ClearSet(int SetN);
    void InitCyclicSchedule(int FeedsCount, int FeedInterval, int FeedDur);
    void InitCyclicSchedule(int SetN, int FeedsCount, int FeedInterval, int FeedDur);
    void SetFeed(int SetN, int FeedN, int FeedTime, int FeedDur);
    
    void OnRise();
    void OnTimer(int SecondsPassed);
    
    
  private:
  
  
};




#endif
