/**
  ******************************************************************************
  * @file    utilities.h
  * @author  tianlx1985
  * @version V1.0.0
  * @date    2020-09-24
  * @brief   This file contains all the functions prototypes for the miscellaneous
  *          firmware library functions (add-on to CMSIS functions).
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */
#ifndef __UTILITY_H
#define __UTILITY_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stdint.h"

uint8_t num_bcd_to_dec(uint8_t *pBcdCode);
uint8_t num_dec_to_bcd(uint8_t *pDecCode);
uint32_t num_bcd_to_dec_batch(uint8_t const* pBcdCode, uint8_t* pDecCode, uint16_t Length);
uint32_t num_dec_to_bcd_batch(uint8_t const* pDecCode, uint8_t* pBcdCode, uint16_t Length);
uint8_t num_bcd_to_ascii(uint8_t *pBCD,uint8_t *pASCII,uint16_t length);

void time_to_bcd(uint32_t Second,uint8_t *pTimeBCD);
void time_to_dec(uint32_t Second,uint8_t *pTimeDEC);

uint8_t time_increase(uint8_t *pTimeBCD);
uint8_t time_bcd_to_minutes(uint8_t const *pTimeBCD,uint16_t *pMinutes);
void time_to_dec(uint32_t Second, uint8_t* pTimeDEC);

uint8_t is_bcd_valid(uint8_t const *pBcd,uint32_t Length);
uint8_t is_bcd_time_valid(uint8_t const *pTimeBCD);

void u32_to_bytes_big(uint32_t Num,uint8_t *pStr);
uint32_t bytes_to_u32_big(uint8_t *pStr);

#ifdef __cplusplus
}
#endif

#endif /*__UTILITY_H*/