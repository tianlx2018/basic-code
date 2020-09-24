#include "hslrgb.h"

//float Hue2RGB(float v1, float v2, float vH);
//
//void HSL2RGB(float H,float S,float L,uint8_t *p_red,uint8_t *p_green,uint8_t *p_blue)
//{
//    float R,G,B;
//    float var_1, var_2;
//    if (S == 0)                       //HSL values = 0 ¡Â 1
//    {
//        R = L * 255.0;                   //RGB results = 0 ¡Â 255
//        G = L * 255.0;
//        B = L * 255.0;
//    }
//    else
//    {
//        if (L < 0.5) 
//          var_2 = L * (1 + S);
//        else         
//          var_2 = (L + S) - (S * L);
//
//        var_1 = 2.0 * L - var_2;
//
//        R = 255.0 * Hue2RGB(var_1, var_2, H + (1.0 / 3.0));
//        G = 255.0 * Hue2RGB(var_1, var_2, H);
//        B = 255.0 * Hue2RGB(var_1, var_2, H - (1.0 / 3.0));
//    }
//    
//    *p_red =(uint8_t)R;
//    *p_green =(uint8_t)G;
//    *p_blue =(uint8_t)B;
//}
//---------------------------------------------------------------------------
//float Hue2RGB(float v1, float v2, float vH)
//{
//    if (vH < 0) vH += 1;
//    if (vH > 1) vH -= 1;
//    if (6.0 * vH < 1) return v1 + (v2 - v1) * 6.0 * vH;
//    if (2.0 * vH < 1) return v2;
//    if (3.0 * vH < 2) return v1 + (v2 - v1) * ((2.0 / 3.0) - vH) * 6.0;
//    return (v1);
//}


uint32_t Hue2RGB(int32_t v1, int32_t v2, int32_t vH);

//H,S,L 0-1000
void HSL2RGB(uint32_t H,uint32_t S,uint32_t L,uint8_t *p_red,uint8_t *p_green,uint8_t *p_blue)
{
    uint32_t R,G,B;
    int32_t var_1, var_2;
    if (S == 0)                       //HSL values = 0 ¡Â 1
    {
        R = L * 255/1000;                   //RGB results = 0 ¡Â 255
        G = L * 255/1000;
        B = L * 255/1000;
    }
    else
    {
        if (L < 500) 
          var_2 = L * (1000 + S)/1000;
        else         
          var_2 = (L + S) - (S * L)/1000;

        var_1 = 2 * L - var_2;

        R = 255 * Hue2RGB(var_1, var_2, H + (1000 / 3));
        G = 255 * Hue2RGB(var_1, var_2, H);
        B = 255 * Hue2RGB(var_1, var_2, H - (1000 / 3));
        
        R /= 1000;
        G /= 1000;
        B /= 1000;
    }
    
    *p_red =(uint8_t)R;
    *p_green =(uint8_t)G;
    *p_blue =(uint8_t)B;
}


//*1000
//
uint32_t Hue2RGB(int32_t v1, int32_t v2, int32_t vH)
{
    if (vH < 0) vH += 1000;
    if (vH > 1000) vH -= 1000;
    
    if (6 * vH < 1000) 
      return v1 + (v2 - v1) * 6 * vH/1000;
    if (2 * vH < 1000) 
      return v2;
    if (3 * vH < 2000) 
      return v1 + (v2 - v1) * ((2000 / 3) - vH) * 6/1000;
    
    return (v1);
}