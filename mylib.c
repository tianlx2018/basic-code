#include "mylib.h"
#include "string.h"
/**
  * @brief  Converse BCD to ASCII,with BCD check
  * @param  uint8_t *pBCD,uint8_t *pASCII,uint16_t length
  * @retval 0 no error, or error
  * @test ok
  */
uint8_t ConvBCD2ASCII(uint8_t *pBCD,uint8_t *pASCII,uint16_t length)
{
  if(IsBcdValid(pBCD,length))
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
uint8_t ConvBcds2Decs(uint8_t const *pBcdCode,uint8_t *pDecCode,uint16_t Length)
{
  uint8_t temp = 0;
  uint8_t temp2 = 0;
    
  for(uint16_t k = 0; k < Length; ++k)
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
  * @test ok
  */
uint8_t ConvDecs2Bcds(uint8_t const *pDecCode,uint8_t *pBcdCode,uint16_t Length)
{   
  for(uint16_t k = 0; k < Length; ++k)
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
uint8_t ConvBcd2Dec(uint8_t *pBcdCode)
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
uint8_t ConvDec2Bcd(uint8_t *pDecCode)
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
void ConvSecond2TimeBCD(uint32_t Second,uint8_t *pTimeBCD)
{
  uint8_t TimeDec[3];
  
  ConvSecond2TimeDEC(Second,TimeDec);
  
  ConvDecs2Bcds(TimeDec,pTimeBCD,3);
        
}

/**
  * @brief  Converse Second to dec code
  * @param  uint32_t Second,uint8_t *pTimeDEC
  * @retval none
  * @test ok
  */
void ConvSecond2TimeDEC(uint32_t Second,uint8_t *pTimeDEC)
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
uint8_t TimeUpdate(uint8_t *pTimeBCD)
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
uint8_t TimeGetMinute(uint8_t const *pTimeBCD,uint16_t *pMinutes)
{  
  //time value illegal
  if(IsTimeBcdValid(pTimeBCD))
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
uint8_t IsBcdValid(const uint8_t *const pBcd,uint32_t Length)
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
uint8_t IsTimeBcdValid(uint8_t const *pTimeBCD)
{
  if(IsBcdValid(pTimeBCD,3))
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
void U32ToString(uint32_t Num,uint8_t *pStr)
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
  * @test ok
  */
uint32_t StringToU32(uint8_t *pStr)
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


//uint8_t *Src  sourse data
//uint8_t *Dst  distance data
//uint16_t Length sourse length
//every packet 22 data
//length <= 440
//max packet 20 * 22 = 440
//dst should large than 20*24 = 480

#define MAX_PACKET        20
#define PACKECT_NUM       22
#define MAX_BYTES         MAX_PACKET*PACKECT_NUM
#define _SLV_PACKET_START  0x0A
#define _SLV_PACKET_CONT   0x0B
#define _SLV_PACKET_END    0x0C
#define _SLV_PACKET_NONE   0x0D


//测试要点
//不足22字节
//不足44字节
//超过20包的
//正常300字节
//整数包22*10
//测试OK
//返回真实数据包数

uint16_t DataPacket(uint8_t *pSrc,uint8_t *pDst,uint16_t Length)
{  
  if(Length > MAX_BYTES)
    Length = MAX_BYTES;
  
  if(Length <= PACKECT_NUM)//one packet
  {
    //add end type header
    *pDst++ = _SLV_PACKET_END;
    
    //fill length
    *pDst++ = (uint16_t)Length;
    
    //copy data
    memcpy(pDst,pSrc,Length);
        
    return 1;//return 1 packet
  }
  else if(Length <= 2*PACKECT_NUM)//two packet
  {
    //add start type header
    *pDst++ = _SLV_PACKET_START;
    
    //fill length
    *pDst++ = 22;
      
    //copy data
    memcpy(pDst,pSrc,22);
    
    //fill the second packet
    pSrc += 22;
    pDst += 22;
    
    *pDst++ = _SLV_PACKET_END;
    
    *pDst++ = Length - 22; 
    
    memcpy(pDst,pSrc,(Length - 22));
    
    return 2;
  }
  else//more than 2 packet
  {
    //if Length % 22 = 0,and numofpackets = Length / 22
    //then start_packet -1 ,cont_packet -2: numofpackets-1,end_packet = numofpackets
    //if length % 22 != 0
    //then start_packet -1,cont_packet -2: numofpackets,end_packet = numofpackets
        
    uint16_t numofpackets = Length / 22;
    uint8_t restbytes = Length % 22;
    //if num of rest bytes is 0,then repeat numofpackets-1 time for PACKET_CONT
    uint16_t stoppoint = restbytes? numofpackets:(numofpackets-1);
    uint16_t sendpacket = restbytes? (numofpackets + 1):numofpackets;   
    
    if(restbytes == 0)
    {
      restbytes = 22;
    }
    
    /*fill the first packet*/
    //add start type header
    *pDst++ = _SLV_PACKET_START;
    
    //fill length
    *pDst++ = 22;
      
    //copy data
    memcpy(pDst,pSrc,22);
    
    /*fill 2 - stoppoint Packet */
    for(int k = 2; k <= stoppoint;k++)
    {
      pDst += 22;
      pSrc += 22;
      
      *pDst++ = _SLV_PACKET_CONT;
    
      //fill length
      *pDst++ = 22;
      
      //copy data
      memcpy(pDst,pSrc,22);
    }
    
    /*fill the last Packet if possable*/    
    //fill end packet
    pDst += 22;
    pSrc += 22;
    
    *pDst++ = _SLV_PACKET_END;
    
    *pDst++ = restbytes; 
    
    memcpy(pDst,pSrc,restbytes);
    
    return sendpacket;    
  }  
}