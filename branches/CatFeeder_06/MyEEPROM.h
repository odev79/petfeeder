#ifndef MyEEPROM_h
#define MyEEPROM_h


#include <EEPROM.h>
#include <inttypes.h>

#define EEPRAddr_DefSched 0


class MyEEPROM
{
  public:
    void SaveBytes(int EEPRAddr, uint8_t pData[], int DOffset, int DLen);
    void ReadBytes(int EEPRAddr, uint8_t pData[], int DOffset, int DLen);

    void SaveCyclSched(int FeedsCount, int FeedInterval, int FeedDur);
    void ReadCyclSched(int *FeedsCount, int *FeedInterval, int *FeedDur);
  private:
   
};


#endif
