/******************************************************************************
* @file main.c
* @brief USART/UART Asynchronous mode Application Note software example
* @author Silicon Labs
* @version 1.04
******************************************************************************
* @section License
* <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
*******************************************************************************
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
* DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
* obligation to support this Software. Silicon Labs is providing the
* Software "AS IS", with no express or implied warranties of any kind,
* including, but not limited to, any implied warranties of merchantability
* or fitness for any particular purpose or warranties against infringement
* of any proprietary rights of a third party.
*
* Silicon Labs will not be liable for any consequential, incidental, or
* special damages, or any other relief, or for any claim by any third party,
* arising from your use of this Software.
*
******************************************************************************/

#include <stdint.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_gpio.h"

#include "remind.h"
/* Function prototypes */

/* Declare some strings */

//about 1ms delay under 32Mhz


/******************************************************************************
* @brief  Main function
*
*****************************************************************************/

uint32_t test = 0;

int main(void)
{
  /* Initialize chip - handle erratas */
  CHIP_Init( );
  
//  do_not_disturb_set(200,100);//err1
//  do_not_disturb_set(100,100);//err2
//  do_not_disturb_set(200,1500);//err3
//  do_not_disturb_set(1500,200);//err4
//  do_not_disturb_set(1500,1500);//err5
//  do_not_disturb_set(20,150);//ok 1
//  
//  do_not_disturb_time_update(10);
//  test = do_not_disturb_is_valid();
//  
//  do_not_disturb_time_update(100);
//  test = do_not_disturb_is_valid();
//  
//  do_not_disturb_time_update(200);
//  test = do_not_disturb_is_valid();  
  
//  water_time_out_set(100);
//  water_time_out_set(1000);
//  water_time_out_set(200);
  
//  water_time_out_set(200);
//
//  for(uint16_t k = 0; k < 202;k++)
//  {
//    water_time_out_update();
//  }
//  
//  test = water_time_out_query();
//  
//  water_time_out_reset();
  
  
//  water_hot_warming_set(10,10);
//  water_hot_warming_set(70,80);
//  water_hot_warming_set(60,50);
  
   water_hot_warming_update(30);
   test = water_hot_query();
   
   water_hot_warming_update(50);
   test = water_hot_query();
   
   water_hot_warming_update(60);
   test = water_hot_query();
   
   water_hot_warming_update(70);
   test = water_hot_query();
   
   water_hot_warming_update(110);
   test = water_hot_query();
   
   water_hot_warming_update(40);
  test = water_hot_query();
    
  while(1){}
}



