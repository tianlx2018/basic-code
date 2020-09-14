
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>


/***************************************************************************//**
 * @brief
 *   convert two ascii hex number to hex number
 *   eg. "AB"->0xAB
 * @param[in] str data input pointer
 *
 * @param[in] pdata data output pointer
 *
 * @note
 *  
 *   return 0 no error,or error occured
 ******************************************************************************/
uint8_t str_to_hex_byte(char *p_str,uint8_t *pdata)
{
  uint8_t temp = 0;
  
  if(p_str == 0 || pdata == 0)
    return 1;
  
  if(*p_str <= '9' && *p_str >= '0')
  {
    temp |= *p_str - '0';
  }
  else if(*p_str <= 'F' && *p_str >= 'A')
  {
    temp |= (*p_str - 'A'+ 10);
  }
  else if(*p_str <= 'f' && *p_str >= 'a')
  {
    temp |= (*p_str - 'a'+ 10);
  }
  else
    return 2;		 
  
  p_str++;
  temp <<= 4;
  
  if(*p_str <= '9' && *p_str >= '0')
  {
    temp |= *p_str - '0';
  }
  else if(*p_str <= 'F' && *p_str >= 'A')
  {
    temp |= (*p_str - 'A'+ 10);
  }
  else if(*p_str <= 'f' && *p_str >= 'a')
  {
    temp |= (*p_str - 'a'+ 10);
  }
  else
    return 2;	 
  
  *pdata = temp;
  
  return 0;
}


/***************************************************************************//**
* @brief
*   convert hex MAC to ascii MAC 
*   eg. 0x11,0x22,0x33,0x44,0x55,0x66 ->"0x112233445566"
* @param[in] uint8_t * hex_src
*
* @param[in] char * string point to result where to store
*
* @param[in] length 
*
* @return numbers of hex tranformed 
* @note
*  
******************************************************************************/
int hex_to_ascii(char * hex_src,char * string,int length)
{
  if(hex_src == 0 || string == 0 || length <= 0)
    return 0;

  char k = 0;
  for(k = 0;k < length;k++)
  {
    if((*hex_src >> 4) > 9)
      *string++ = (*hex_src >> 4) + 'A' - 10;
    else
      *string++ = (*hex_src >> 4) + '0';
    
    if((*hex_src & 0X0F) > 9)
      *string++ = (*hex_src++ & 0X0F) + 'A' - 10;
    else
      *string++ = (*hex_src++ & 0X0F) + '0';			 
  }
}


int main(int arg,char *argv[])
{

}