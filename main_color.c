
#include <stdio.h>

int main(void)
{

  while (1)
  {
  }
}

//this function convert data allien left
static uint8_t uint_to_asc(uint16_t Num, uint8_t *pData)
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
  *pData++ = Num;
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