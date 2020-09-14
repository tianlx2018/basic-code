/*
 * u16 hue 0-0xffff ->0~360
 * u16 sat 0-0xffff ->0~100
 * u16 lightness 0-0xffff ->0~100
 * */

#include "stdint.h"

/*
b) HSL→RGB的算法描述。
步骤1：If S=0,表示灰色，定义R,G和B都为L.
步骤2：否则，测试L:
If L<0.5,temp2=L*(1.0+S)
If L>=0.5,temp2=L+S-L*S
步骤3：temp1=2.0*L-temp2
步骤4：把H转换到0～1。
步骤5：对于R,G,B，计算另外的临时值temp3。方法如下：
for R, temp3=H+1.0/3.0
for G, temp3=H
for B, temp3=H-1.0/3.0
if temp3<0, temp3=temp3+1.0
if temp3>1, temp3=temp3-1.0
步骤6：对于R,G,B做如下测试：
If 6.0*temp3<1,color=temp1+(temp2-temp1)*6.0*temp3
Else if 2.0*temp3<1,color=temp2
Else if 3.0*temp3<2,
color=temp1+(temp2-temp1)*((2.0/3.0)-temp3)*6.0
Else color=temp1
*/
void hslToRgb_int(uint16_t H, uint16_t S, uint16_t L,uint8_t *p_red,uint8_t *p_green,uint8_t *p_blue)
{
  uint32_t temp = 0;
  if(p_red && p_green && p_blue)
  {
      /* change scale from 0-0xffff*/

      temp = H*360/0xffff;//0-360
      H = (uint16_t)temp;
      temp = S*100/0xffff;//0-100
      S = (uint16_t)temp;
      temp = L*100/0xffff;//0-100
      L = (uint16_t)temp;

      //C = (1-|2L-1)x S [0-1]
      
      uint32_t C = L > 50?(200-2*L)*S/100:2*L*S/100;//0-100

      //X = C*(1-|(h/60)mode 2-1|) ->0 or C
      uint32_t X = ((H/60)%2)?C:0;//0-100

      uint32_t m = L - C/2;//0-100

      uint32_t R1,G1,B1;

      if(H < 60)
      {
        R1 = C;
        G1 = X;
        B1 = 0;
      }
      else if(60 <= H && H < 120)
      {
        R1 = X;
        G1 = C;
        B1 = 0;
      }
      else if(120 <= H && H < 180)
      {
        R1 = 0;
        G1 = C;
        B1 = X;
      }
      else if(180 <= H && H < 240)
      {
        R1 = 0;
        G1 = X;
        B1 = C;
      }
      else if(240 <= H && H < 300)
      {
        R1 = X;
        G1 = 0;
        B1 = C;
      }
      else// if(300 <= H && H < 360)
      {
        R1 = C;
        G1 = 0;
        B1 = X;
      }

      *p_red = (uint8_t)((R1+m)*255/100);//0-255
      *p_green =(uint8_t)((G1+m)*255/100);
      *p_blue =(uint8_t)((B1+m)*255/100);
    }
}


uint16_t hue = 0;
uint16_t sat = 0;
uint16_t lum = 0;
uint8_t red = 0xff;
uint8_t blue = 0xff;
uint8_t green = 0xff;





#include "stdio.h"

uint16_t a[][3]={{0,0,0},{0,0,100},{0,100,50},{120,100,50},{240,100,50},{60,100,50},{180,100,50},{300,100,50}};

void main()
{
//  a[0][0] = 0;
//  a[0][1] = 100;
//  a[0][2] = 50;
//  //hue 0-360
//  for(uint8_t i = 0;i < 36;i++)
//  {
//    a[0][0] = i*10;
//    
//    hue = (uint16_t)(a[0][0]*0xffff/360);
//    sat = (uint16_t)(a[0][1]*0xffff/100);
//    lum = (uint16_t)(a[0][2]*0xffff/100);
//    
//    hslToRgb_int(hue, sat, lum,&red,&blue,&green);
//    
//    printf("%d %d,%d----%d %d %d\n",hue,sat,lum,red,blue,green);
//  }
  
  //
//  a[0][0] = 0;
//  a[0][1] = 0;
//  a[0][2] = 50;  
//  for(uint8_t i = 0;i <= 100;i+=5)
//  {
//    a[0][1] = i;
//    
//    hue = (uint16_t)(a[0][0]*0xffff/360);
//    sat = (uint16_t)(a[0][1]*0xffff/100);
//    lum = (uint16_t)(a[0][2]*0xffff/100);
//    
//    hslToRgb_int(hue, sat, lum,&red,&blue,&green);
//    
//    printf("%d %d,%d----%d %d %d\n",hue,sat,lum,red,blue,green);
//  }  
  
//  //lum 0-360
//  a[0][0] = 0;
//  a[0][1] = 0;
//  a[0][2] = 50;    
//  for(uint8_t i = 0;i <= 100;i+=5)
//  {
//    a[0][2] = i;
//    
//    hue = (uint16_t)(a[0][0]*0xffff/360);
//    sat = (uint16_t)(a[0][1]*0xffff/100);
//    lum = (uint16_t)(a[0][2]*0xffff/100);
//    
//    hslToRgb_int(hue, sat, lum,&red,&blue,&green);
//    
//    printf("%d %d,%d----%d %d %d\n",hue,sat,lum,red,blue,green);
//  }    
  

#include "hslrgb.h"


  while(1)
  {
    HSL2RGB(hue, sat, lum,&red,&blue,&green);
    
    printf("%d %d,%d----%d %d %d\n",hue,sat,lum,red,blue,green);    
  }
}