
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
void itoa(int n,char *s)
{
  int i = 0,j = 0,sign = n;
  char temp[20] = {0};

  if(s == 0)
    return;
  
  if(n < 0)
    n =-n;//使n成为正数
  
  do
  {
    temp[i++] = n % 10 + '0';//取下一个数字
  }while ((n /= 10) > 0);//删除该数字
  
  if(sign < 0)
    temp[i] = '-';
  else
    i--;
  
  for(j = i; j >= 0; j--)//生成的数字是逆序的，所以要逆序输出
  {
    *s++ = temp[j];
    //printf("%c",s[j]);
  }  
} 

/***************************************************************************//**
 * @brief
 *   convert ascii float number to float number
 *   double atof(const char *str)
 *   
 * @param[in] str
 *   point to the number string
 *   eg."3.1415926"->3.1415926
 *   eg."3.12x5926"->3.12
 * @note
 *   for the reason of float number,the may little difference with the result!
 * @param[out] double
 *   return the number in precision of double
 ******************************************************************************/




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
* return 1 pointer error
* return 2 string input format error
* return 0 error none
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
* return -1 pointer error
* return -2 length error
* return 0 error none
******************************************************************************/
int8_t ms_slice_string(char *src,char *dst1,char *dst2,char* dst3)
{
#define MAX_LENGTH 10
  
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


/////////////////////////////////TEST///////////////////////////////////////////
float num = 0;
int num2 = 0;


//main functions for demo or test cases
int main(void)
{
  /* double atof(const char *str) */
#if 0
  char num_str[] = "3.15x15926x";
  char num_str2[] = "3.1215926";
  char num_str3[] = "3.1015926";

  
  num = atof(num_str);
  
  num = atof(num_str2);
  
  num = atof(num_str3);
#endif
  
  /* int atoi(const char *str) */
  
#if 0
  char num_str1[] = "32";
  char num_str2[] = "-320";
  char num_str3[] = "0x12";//must integer
  
  num2 = atoi(num_str1);
  
  num2 = atoi(num_str2);
  
  num2 = atoi(num_str3);
#endif 
  
  /* void itoa(int n,char *s) */
#if 1
  char num_str[10] = {0};
  int num3 = 1003;
  
  itoa(num3,num_str);
  
  num3 = -10023;
  
  itoa(num3,num_str);
#endif   
  
  
  
  while(1)
  {
  }
}


