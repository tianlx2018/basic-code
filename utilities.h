#ifndef __UTILITIES_H
#define __UTILITIES_H

#include "stdint.h"

uint8_t num_bcd_to_dec(uint8_t *pBcdCode);
uint8_t num_dec_to_bcd(uint8_t *pDecCode);
uint8_t num_bcd_to_dec_batch(uint8_t const *pBcdCode,uint8_t *pDecCode,uint16_t Length);
uint8_t num_dec_to_bcd_batch(uint8_t const *pDecCode,uint8_t *pBcdCode,uint16_t Length);
uint8_t num_bcd_to_ascii(uint8_t *pBCD,uint8_t *pASCII,uint16_t length);

void time_to_bcd(uint32_t Second,uint8_t *pTimeBCD);
void time_to_dec(uint32_t Second,uint8_t *pTimeDEC);

uint8_t time_increase(uint8_t *pTimeBCD);
uint8_t time_bcd_to_minutes(uint8_t const *pTimeBCD,uint16_t *pMinutes);

uint8_t is_bcd_valid(uint8_t const *pBcd,uint32_t Length);
uint8_t is_bcd_time_valid(uint8_t const *pTimeBCD);

void u32_to_bytes_big(uint32_t Num,uint8_t *pStr);
uint32_t bytes_to_u32_big(uint8_t *pStr);
#endif /*__UTILITIES_H*/