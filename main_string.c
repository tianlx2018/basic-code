
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
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

int32_t get_steps(char *p_src)
{
  if(*p_src == 0)//no parameters
    return 0;

  if(p_src[0] == 'R')
  {
    return 0X7FFFFFFF;
  }
  else if(p_src[0] == 'L')
  {
    return 0X80000000;
  }
  else
  {
    return atoi(p_src);   
  }
}


int32_t  get_dev_addr(char *p_src)
{
  if(*p_src == 0)//no parameters
    return 0;//local

  if(strcmp(p_src,"ALL") == 0)
  {
    return 0xff;
  }
  else
  {
    return atoi(p_src);   
  }
}

//return 0,error
uint8_t  get_speed(char *p_src)
{
  if(p_src[0] == '1')
  {
    return 3;
  }
  else if(p_src[0] == '2')
  {
    return 6;//2~30
  }
  else if(p_src[0] == '3')
  {
    return 12;//2~30
  }
  else if(p_src[0] == '4')
  {
    return 24;//2~30
  }
  else  
    return 0;
}


char at_motor_run(char * value)
{
  //input string
  //<STEP>,<SPEED>,<ADDR>
#define MAX_PARA_LEN    11
  char str_step[MAX_PARA_LEN] = {0};
  char str_speed[MAX_PARA_LEN] = {0};
  char str_addr[MAX_PARA_LEN] = {0};

  int8_t ret = ms_slice_string(value,str_step,str_speed,str_addr);
  
  if(ret != 0)
    return 0;//ERROR

  int steps = get_steps(str_step);

  uint8_t speed = get_speed(str_speed);
  
  uint8_t addr = get_dev_addr(str_addr);

  return 0;
}

//main functions for demo or test cases
char input1[] = "100";//case 1
char input2[] = "100,3";//case 1
char input3[] = "100,3,12";//case 1
char input4[] = "100,,12";//case 1


#define LOG(...) printf(__VA_ARGS__)

//void log_fatal(uint32_t module_id,  char *p_str, ...)
//{
//  LOG(p_str,...);
//}




int main(void)
{
//  at_motor_run(input1);
//  at_motor_run(input2);
//  at_motor_run(input3);
//  at_motor_run(input4);
  #include <stdlib.h>
  LOG("hello %d\r\n", 10);
  
    int number = 123456;
    char string[25];
    itoa(number,string,10);
    printf("integer=%d string=%s\n", number, string);
  
  while(1)
  {
  }
}


