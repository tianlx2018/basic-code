#include "stdio.h"
#include "fifo.h"

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
*	convert 0x5e 0x5d->0x0d ,0x5e 0x7d->0x5e
*	uint8_t *p_buf_in,
*	uint8_t length, p_buf_in bytes
*	uint8_t *p_buf_out
*   return numbers of byte for *p_buf_out
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


uint8_t test1[20] = {0x01,0x02,0x0a,0x5e,0x5d,0x5e,0x7d,0x5d,0x5e,0x5a};
uint8_t t_out[20] = {};
uint8_t t_back[20] = {};
uint8_t length = 0;
uint8_t length2 = 0;


int main()
{
  length =  Data_ChangeInto(test1, 10, t_out);
  
   length2 = Data_ChangeBack(t_out,length,t_back);
  
  while(1)
  {
  }
}
