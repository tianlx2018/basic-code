#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
 /*
examples:

char *p_str1 = '12';
char *p_str2 = 'AB';//must not with 0x
char *p_str3 = 'ab';//can use a~f or A~F combination
char *p_str4 = 'cD';

uint8_t result = 0;
uint8_t ret = 0;

ret = str_to_hex_byte(p_str,&result);
ret = str_to_hex_byte(p_str,&result);
ret = str_to_hex_byte(p_str,&result);
ret = str_to_hex_byte(p_str,&result);

*/
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
*   eg. 0x11,0xab,0xcd,0x44,0x55,0x66 ->"11ABCD445566"
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
 /*
examples:
char * hex_src = {0x11,0xab,0xcd,0x44,0x55,0x66};
char string[14] = {0};
int length = hex_to_ascii(hex_src,string,sizeof(hex_src));
result:'11ABCD445566'
*/
int hex_to_ascii(char * hex_src,char * string,int length)
{
  if(hex_src == 0 || string == 0 || length <= 0)
    return 0;

  int k = 0;
	
  for(k = 0; k < length; k++)
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
	
	return length;
}





/***************************************************************************//**
 * @brief this function convert 0~9999 to bcd
 * 
 * @note max 4 digit!  
 *
 * @param[in] uint16_t Num 0~9999
 * 
 * @param[out] uint8_t *pData point to string buffer
 ******************************************************************************/
uint8_t num_to_asc(uint16_t Num, uint8_t *pData)
{
  uint8_t length = 0;

  memset(pData, 0, 4);

  if (Num > 9999)
    Num = 9999;

#if 1
  if (Num / 1000)
  {
    length += 1;

    *pData++ = Num / 1000;
    Num %= 1000;
  }

  if (Num / 100 || length)
  {
    length += 1;

    *pData++ = Num / 100;
    Num %= 100;
  }

  if (Num / 10 || length)
  {
    length += 1;

    *pData++ = Num / 10;
    Num %= 10;
  }

  length += 1;
  *pData++ = (uint8_t)Num;
#else
  if (Num / 1000)
  {
    length += 1;

    *pData++ = Num / 1000 + '0';
    Num %= 1000;
  }

  if (Num / 100 || length)
  {
    length += 1;

    *pData++ = Num / 100 + '0';
    Num %= 100;
  }

  if (Num / 10 || length)
  {
    length += 1;

    *pData++ = Num / 10 + '0';
    Num %= 10;
  }

  length += 1;
  *pData++ = Num + '0';
#endif

  return length;
}

/***************************************************************************//**
 * @brief
 *  convert integer to string
 * 
 * @note max 20 digit!  
 *
 * @param[in] n integer input
 * 
 * @param[in] s point to string buffer
 ******************************************************************************/
//void itoa(int n,char *s)
//{
//  int i = 0,j = 0,sign = n;
//  char temp[20] = {0};
//
//  if(s == 0)
//    return;
//  
//  if(n < 0)
//    n =-n;//使n成为正数
//  
//  do
//  {
//    temp[i++] = n % 10 + '0';//取下一个数字
//  }while ((n /= 10) > 0);//删除该数字
//  
//  if(sign < 0)
//    temp[i] = '-';
//  else
//    i--;
//  
//  for(j = i; j >= 0; j--)//生成的数字是逆序的，所以要逆序输出
//  {
//    *s++ = temp[j];
//    //printf("%c",s[j]);
//  }  
//} 

///***************************************************************************//**
// * @brief
// *   convert two ascii hex number to hex number
// *   eg. "AB"->0xAB
// * @param[in] str data input pointer
// *
// * @param[in] pdata data output pointer
// *
// * @note
// *  
// * @return 0 no error,or error occured
// ******************************************************************************/
//uint8_t str_to_hex_byte(char *p_str,uint8_t *pdata)
//{
//  uint8_t temp = 0;
//  
//  if(p_str == 0 || pdata == 0)
//    return 1;
//  
//  if(*p_str <= '9' && *p_str >= '0')
//  {
//    temp |= *p_str - '0';
//  }
//  else if(*p_str <= 'F' && *p_str >= 'A')
//  {
//    temp |= (*p_str - 'A'+ 10);
//  }
//  else if(*p_str <= 'f' && *p_str >= 'a')
//  {
//    temp |= (*p_str - 'a'+ 10);
//  }
//  else
//    return 2;		 
//  
//  p_str++;
//  temp <<= 4;
//  
//  if(*p_str <= '9' && *p_str >= '0')
//  {
//    temp |= *p_str - '0';
//  }
//  else if(*p_str <= 'F' && *p_str >= 'A')
//  {
//    temp |= (*p_str - 'A'+ 10);
//  }
//  else if(*p_str <= 'f' && *p_str >= 'a')
//  {
//    temp |= (*p_str - 'a'+ 10);
//  }
//  else
//    return 2;	 
//  
//  *pdata = temp;
//  
//  return 0;
//}

/***************************************************************************//**
* @brief
*   convert hex MAC to ascii MAC 
*   eg. 0x11,0x22,0x33,0x44,0x55,0x66 ->"112233445566"
* @param[in] mac input MAC hex
*
* @param[in] string point to result where to store
*
* @note
*  
******************************************************************************/
void mac_to_string(uint8_t * mac,char * string)
{
  if(mac == 0 || string == 0)
    return;
  
  *string++ = '0';
  *string++ = 'x';
  
  for(uint8_t k = 0;k < 6;k++)
  {
    if((*mac >> 4) > 9)
      *string++ = (*mac >> 4) + 'A' - 10;
    else
      *string++ = (*mac >> 4) + '0';
    
    if((*mac & 0X0F) > 9)
      *string++ = (*mac++ & 0X0F) + 'A' - 10;
    else
      *string++ = (*mac++ & 0X0F) + '0';			 
  }
}

/***************************************************************************//**
* @brief
*   convert ascii MAC hex MAC
*   eg. "112233445566"->0x11,0x22,0x33,0x44,0x55,0x66
* @param[in] string input ascii
*
* @param[in] mac data output pointer
*
* @note
* @return 1 pointer error,2 string input format error,0 error none
******************************************************************************/
uint8_t string_to_mac_hex(char * string,uint8_t * mac)
{
  if(mac == 0 || string == 0)
    return 1;
  
  string+= 2;
  
  for(uint8_t k = 0;k < 6;k++)
  {
    if(str_to_hex_byte(string,mac))
      break;
    
    string+=2;
    mac++;
  }
  
  return 0;
}

/***************************************************************************//**
* @brief
*  slice string into three part with ','
*  eg. "abc,efg,higk"->dst1 "abc",dst2 "efg", dst3 "higk"
*  sub string must not excced MAX_LENGTH
* @param[in] src:string input
*
* @param[in] dst1:string out
*
* @param[in] dst2:string out
*
* @param[in] dst3:string out
* 
* @return -1 pointer error,-2 length error, 0 error none
******************************************************************************/
int8_t string_slice(char *src,char *dst1,char *dst2,char* dst3)
{
#define MAX_DEV_LEN 10
  
  uint8_t count = 0;
  
  if(dst1 == 0 || src == 0 || dst2 == 0 || dst3 == 0)//if pointer null
    return -1;
  
  while(*src != 0 && *src != ',')
  {
    *dst1++ = *src++;
    count++;//count for bytes
    if(count > MAX_DEV_LEN)
      return -2;
  }
  
  if(*src == 0)//if reach end of string
    return 0;
  else if(*src == ',')//if reach delimiter symbol
    src++;
  
  count = 0;
  
  while(*src != 0 && *src != ',')
  {
    *dst2++ = *src++;
    count++;//count for bytes
    if(count > MAX_DEV_LEN)
      return -2;
  }	
  
  if(*src == 0)
    return 0;
  else if(*src == ',')
    src++;	
  
  count = 0;
  
  while(*src != 0 && *src != ',')
  {
    *dst3++ = *src++;
    count++;//count for bytes
    if(count > MAX_DEV_LEN)
      return -2;
  }	
  
  return 0;		
}




#define LOG(...) printf(__VA_ARGS__)



/**
  * @brief  Converse BCD to ASCII,with BCD check
  * @param  uint8_t *pBCD,uint8_t *pASCII,uint16_t length
  * @retval 0 no error, or error
  * @test ok
  */
uint8_t num_bcd_to_ascii(uint8_t *pBCD,uint8_t *pASCII,uint16_t length)
{
  if(is_bcd_valid(pBCD,length))
    return 1;
  else
  {
    for(int i = 0; i < length; ++i)
    {
      *pASCII++ = (*pBCD >> 4) + '0';
      *pASCII++ = (*pBCD++ & 0xf) + '0';
    }
    
    return 0;
  }
}


/**
  * @brief  Converse BCD string to DEC string
  * @param  uint8_t const *pBcdCode,
            uint8_t *pDecCode,
            uint16_t Length
  * @retval how many bytes conversed
  * @test ok
  */
uint32_t num_bcd_to_dec_batch(uint8_t const *pBcdCode,uint8_t *pDecCode,uint16_t Length)
{
  uint8_t temp = 0;
  uint8_t temp2 = 0;
    
  for(uint32_t k = 0; k < Length; ++k)
  {
    temp = *pBcdCode >> 4;
    temp2 = *pBcdCode++ & 0x0f;
        
    if(temp > 9 && temp2 > 9)
      return k;
    
    *pDecCode++ = (temp * 10 + temp2);
  }
  
  return Length;
}
/**
  * @brief  Converse BCD string to DEC string
  * @param  uint8_t const *pDecCode,
            uint8_t *pBcdCode,
            uint16_t Length
  * @retval how many bytes conversed
  * @example
  */
uint32_t num_dec_to_bcd_batch(uint8_t const *pDecCode,uint8_t *pBcdCode,uint16_t Length)
{   
  for(uint32_t k = 0; k < Length; ++k)
  {        
    if(*pDecCode > 99)
      return k;
    
    *pBcdCode++ = ((*pDecCode / 10) << 4) | (*pDecCode % 10);
    
    pDecCode++;
  }
  
  return Length;
}

/**
  * @brief  Converse BCD to DEC code
  * @param  uint8_t *pBcdCode
  * @retval uint8_t Dec value
  * @test ok
  */
uint8_t num_bcd_to_dec(uint8_t *pBcdCode)
{  
  uint8_t temp = 0;
  uint8_t temp2 = 0;
  
  temp = *pBcdCode >> 4;
  temp2 = *pBcdCode & 0x0f;
  
  if(temp < 10 && temp2 < 10)
  {    
    return (temp * 10 + temp2);
  }
  else
    return 0;
}
/**
  * @brief  Converse DEC to BCD code
  * @param  uint8_t *pDecCode  DEC 0-99
  * @retval uint8_t
  * @test ok
  */
uint8_t num_dec_to_bcd(uint8_t *pDecCode)
{
  if(*pDecCode < 100)  
    return(((*pDecCode / 10) << 4) | (*pDecCode % 10));
  else
    return 0;
}


/**
  * @brief  Converse Second to bcd code
  * @param  uint32_t Second,uint8_t *pTimeDEC
  * @retval none
  * @test ok
  */
void time_to_bcd(uint32_t Second,uint8_t *pTimeBCD)
{
  uint8_t TimeDec[3];
  
  time_to_dec(Second,TimeDec);
  
  num_dec_to_bcd_batch(TimeDec,pTimeBCD,3);        
}

/**
  * @brief  Converse Second to dec code
  * @param  uint32_t Second,uint8_t *pTimeDEC
  * @retval none
  * @test ok
  */
void time_to_dec(uint32_t Second,uint8_t *pTimeDEC)
{
  uint32_t temp = Second % (24 * 3600);
  
  *pTimeDEC++ = temp / 3600;
  temp %= 3600;
  
  *pTimeDEC++ = temp / 60;
  *pTimeDEC   = temp % 60;
}

/**
  * @brief  Time Update,called every minute
  * @param  uint8_t *pTimeBCD
  * @retval 1,reach end of a day,else 0
  * @test ok
  */
uint8_t time_increase(uint8_t *pTimeBCD)
{
  uint8_t hour = *pTimeBCD;
  uint8_t min  = *(pTimeBCD+1);
  uint8_t overflow = 0;
  
	min++;
  
  if((min & 0x0f) == 0x0a)
  {
		min &= 0xf0;
    min += 0x10;
    
    if(min == 0x60)
    {
      min = 0;
      hour++;
      
      if(hour == 0x24)
      {
        hour = 0;
        overflow = 1;
      }
      else if((hour & 0x0f) == 0x0a)
      {
        hour &= 0xf0;
        hour += 0x10;        
      }      
    }       
  }
  
  *pTimeBCD = hour;
  *(pTimeBCD+1) = min;  
  
  return overflow;
}
/**
  * @brief  Get time in form of minutes
  * @param  uint8_t const *pTimeBCD,uint16_t *pMinutes result
  * @retval 0 no error,1 error
  * @test ok
  */
uint8_t time_bcd_to_minutes(uint8_t const *pTimeBCD,uint16_t *pMinutes)
{  
  //time value illegal
  if(is_bcd_time_valid(pTimeBCD))
    return 1;

  *pMinutes =  (*pTimeBCD >> 4)*600 + (*pTimeBCD & 0x0f)*60;
  *pMinutes += (*(pTimeBCD+1) >> 4)*10 + (*(pTimeBCD+1) & 0xf);
    
  return 0;
}
/**
  * @brief  Check bcd array if valid
  * @param  const uint8_t *const pBcd,uint32_t Length
  * @retval 0 no error, or error
  * @test ok
  */
uint8_t is_bcd_valid(const uint8_t *const pBcd,uint32_t Length)
{
  const uint8_t *pTemp = pBcd; 
  
  while(Length--)
  {    
    if(*pTemp > 0x99 || (*pTemp & 0xf) > 9)
      return 1;
    
    pTemp++;
  }
  
  return 0;  
}

/**
  * @brief  Check bcd form of time if valid
  * @param  uint8_t const *pTimeBCD
  * @retval 0 no error, or error
  * @test ok
  */
uint8_t is_bcd_time_valid(uint8_t const *pTimeBCD)
{
  if(is_bcd_valid(pTimeBCD,3))
    return 1;//error
  
  if(*pTimeBCD > 0x23 || *(pTimeBCD+1) > 0x59 || *(pTimeBCD+2) > 0x59)
    return 2;//error
  else
    return 0;
}


//32位数转换成4个8位数
//考虑到不同编译器选择大小端模式不一样
//测试OK
/**
  * @brief  conver uint32_t to 4 byte uint8_t
  * @param  uint32_t Num,uint8_t *pStr
  * @retval none
  * @test ok
  */
void u32_to_bytes_big(uint32_t Num,uint8_t *pStr)
{
  *pStr++ = (uint8_t)(Num >> 24);
  *pStr++ = (uint8_t)(Num >> 16);
  *pStr++ = (uint8_t)(Num >> 8);
  *pStr   = (uint8_t)(Num);
}



//void U32ToString(uint32_t Num,uint8_t *pStr)
//{
//  uint8_t temp = 0;
//  
//  for(uint8_t k = 0;k < 4;k++)
//  {
//    temp = (uint8_t)(Num >> 28);
//
//    if(temp > 9)
//      temp = temp + 'a'-10;
//    else
//      temp = temp + '0'; 
//    
//    *pStr++ = temp;
//    
//    Num <<= 4;
//  }  
//}




/**
  * @brief  conver 4 uint8_t to uint32_t
  * @param  uint8_t *pStr
  * @retval result
  *
  */
/*
@example:

uint8_t num[4] = {0x12,0x34,0x56,0x78};
uint32_t result = bytes_to_u32_big(num);
//result is 0x12345678
*/
uint32_t bytes_to_u32_big(uint8_t *pStr)
{
  uint32_t Temp = 0;
  
  Temp |= *pStr++;
  Temp <<= 8;
  
  Temp |= *pStr++;
  Temp <<= 8;

  Temp |= *pStr++;
  Temp <<= 8;

  Temp |= *pStr;
  
  return Temp;
}

/*
@example:the use of itoa

int main(void)
{
 
    int number = 123456;
    char string[25];
    itoa(number,string,10);
    printf("integer=%d string=%s\n", number, string);
  
  while(1)
  {
	
  }
}
*/

#define SYMBOL  0x0d    //SYMBOL -> SYMBOL_R1,SYMBOL_R2,SYMBOL_R1->SYMBOL_R1,SYMBOL_R3
#define SYMBOL_R1 0x5e
#define SYMBOL_R2 0x5D
#define SYMBOL_R3 0x7D

/*
*	convert 0x0a->0x5e 0x5d,0x5e ->0x5e 7d,copy other data
        add:0x0a to the end
*	uint8_t *p_buf_in,
*	uint8_t length, p_buf_in bytes
*	uint8_t *p_buf_out
*   return numbers of byte for *p_buf_out
*/
uint8_t convert_into(uint8_t *p_buf_in, uint8_t length, uint8_t *p_buf_out)
{
  uint8_t len_out = 0;
  uint8_t i;
  
  if(p_buf_in == 0 || p_buf_out == 0|| length == 0)
    return 0;	
  
  for(i = 0;i < length;i++)
  {
    if( p_buf_in[i] == SYMBOL )
    {
      p_buf_out[len_out] = SYMBOL_R1;
      p_buf_out[len_out+1] = SYMBOL_R2;
      len_out = len_out + 2;
    }
    else if( p_buf_in[i] == 0x5e )
    {
      p_buf_out[len_out] = SYMBOL_R1;
      p_buf_out[len_out+1] = SYMBOL_R3;
      len_out = len_out + 2;
    }			
    else
    {
      p_buf_out[len_out] = p_buf_in[i];
      len_out++;
    }
  }
  
  p_buf_out[len_out] = SYMBOL;//fill end symbol
  
  return len_out;
}

/*
*	@brief convert 0x5e 0x5d->0x0d ,0x5e 0x7d->0x5e
*	@param[in] uint8_t *p_buf_in,
*	@param[in] uint8_t length, p_buf_in bytes
*	@param[in] uint8_t *p_buf_out
* @return uint8_t number of bytes
*/
uint8_t convert_back(uint8_t *p_buf_in, uint8_t length, uint8_t *p_buf_out)
{
  uint8_t len_out = 1;
  uint8_t i;
  
  if(p_buf_in == 0 || p_buf_out == 0|| length == 0)
    return 0;
  
  p_buf_out[0] = p_buf_in[0];
  
  for(i = 1;i < length;i++)
  {
    if( p_buf_in[i] == SYMBOL_R3 && p_buf_in[i-1] == SYMBOL_R1 )
    {p_buf_out[len_out-1] = SYMBOL_R1;}
    else if( p_buf_in[i] == SYMBOL_R2 && p_buf_in[i-1] == SYMBOL_R1 )
    {p_buf_out[len_out-1] = SYMBOL;}
    else
    {
      p_buf_out[len_out] = p_buf_in[i];
      len_out++;
    }
  }
  
  return len_out;
}

/* how to use convert
uint8_t test1[20] = {0x01,0x02,0x0a,0x5e,0x5d,0x5e,0x7d,0x5d,0x5e,0x5a};
uint8_t t_out[20] = {};
uint8_t t_back[20] = {};
uint8_t length = 0;
uint8_t length2 = 0;

length =  convert_int(test1, 10, t_out);  
length2 = convert_back(t_out,length,t_back); 
*/

