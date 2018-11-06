
#include <stdio.h>
#include <stdlib.h>

/***************************************************************************//**
 * @brief
 *   Configure GPIO external pin interrupt.
 *
 * @details
 *   If reconfiguring a GPIO interrupt that is already enabled, it is generally
 *   recommended to disable it first, see GPIO_Disable().
 *
 *   The actual GPIO interrupt handler must be in place before enabling the
 *   interrupt.
 *
 *   Notice that any pending interrupt for the selected pin is cleared by this
 *   function.
 *
 * @note
 *   On platform 1 devices the interrupt number parameter is not used. The
 *   interrupt number used on these devices is hardwired to the same number as
 *   the pin number. @n
 *   On platform 2 devices, interrupt number can be selected freely within the
 *   same group as pin number, the groups are 0-3, 4-7, 8-11 and 12-15.
 *
 * @param[in] port
 *   The port to associate with @p pin.
 *
 * @param[in] pin
 *   The pin number on the port.
 *
 * @param[in] intNo
 *   The interrupt number to trigger.
 *
 * @param[in] risingEdge
 *   Set to true if interrupts shall be enabled on rising edge, otherwise false.
 *
 * @param[in] fallingEdge
 *   Set to true if interrupts shall be enabled on falling edge, otherwise false.
 *
 * @param[in] enable
 *   Set to true if interrupt shall be enabled after configuration completed,
 *   false to leave disabled. See GPIO_IntDisable() and GPIO_IntEnable().
 ******************************************************************************/

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


