#ifndef _MYLIB_H
#define _MYLIB_H

#include "stdint.h"

uint8_t ConvBcd2Dec(uint8_t *pBcdCode);
uint8_t ConvDec2Bcd(uint8_t *pDecCode);
uint8_t ConvBcds2Decs(uint8_t const *pBcdCode,uint8_t *pDecCode,uint16_t Length);
uint8_t ConvDecs2Bcds(uint8_t const *pDecCode,uint8_t *pBcdCode,uint16_t Length);
uint8_t ConvBCD2ASCII(uint8_t *pBCD,uint8_t *pASCII,uint16_t length);

void ConvSecond2TimeBCD(uint32_t Second,uint8_t *pTimeBCD);
void ConvSecond2TimeDEC(uint32_t Second,uint8_t *pTimeDEC);

uint8_t TimeUpdate(uint8_t *pTimeBCD);
uint8_t TimeGetMinute(uint8_t const *pTimeBCD,uint16_t *pMinutes);

uint8_t IsBcdValid(uint8_t const *pBcd,uint32_t Length);
uint8_t IsTimeBcdValid(uint8_t const *pTimeBCD);

void U32ToString(uint32_t Num,uint8_t *pStr);
uint32_t StringToU32(uint8_t *pStr);

uint16_t DataPacket(uint8_t *pSrc,uint8_t *pDst,uint16_t Length);
#endif