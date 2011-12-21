
#include "MyEEPROM.h"

uint8_t buf[16];

void MyEEPROM::SaveBytes(int EEPRAddr, uint8_t pData[], int DOffset, int DLen)
{
  for (int i=0; i<DLen; i++)
    EEPROM.write(EEPRAddr+i, pData[i]);
}


void MyEEPROM::ReadBytes(int EEPRAddr, uint8_t pData[], int DOffset, int DLen)
{
    for (int i=0; i<DLen; i++)
      pData[i] = EEPROM.read(EEPRAddr+i);
}


void MyEEPROM::SaveCyclSched(int FeedsCount, int FeedInterval, int FeedDur)
{

  buf[0] = FeedsCount;
  buf[2] = FeedInterval % 256 ;
  buf[1] = FeedInterval / 256 ;
  buf[3] = FeedDur;
  
  SaveBytes(EEPRAddr_DefSched,buf,0,4);
    
}

void MyEEPROM::ReadCyclSched(int *FeedsCount, int *FeedInterval, int *FeedDur)
{
  
  ReadBytes(EEPRAddr_DefSched,buf,0,4);
  
  *FeedsCount = buf[0];
  *FeedInterval = buf[1]*256 + buf[2];
  *FeedDur = buf[3];
   
}
