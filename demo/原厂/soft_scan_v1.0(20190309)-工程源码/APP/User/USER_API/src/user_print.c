#include "user_conf.h"

void Print_Init(void)
{
  USART1_Config(); //USART1 config for debug
}

void Print_u8_d(u8 *data, u16 len)
{
  u16 i;
  for (i = 0;i <len ;i++)
  {
    u1_printf("\r\n%d",data[i]);
  }
}

void Print_u8_x(u8 *data, u16 len)
{
  u16 i;
  u1_printf("\r\n");
  for (i = 0;i <len ;i++)
  {
    u1_printf("%0.2x ",data[i]);
  }
}

void Print_u16_d(u16 *data, u16 len)
{
  u16 i;
  for (i = 0;i <len ;i++)
  {
    u1_printf("\r\n%d",data[i]);
  }
}

void Print_u16_x(u16 *data, u16 len)
{
  u16 i;
  for (i = 0;i <len ;i++)
  {
    u1_printf("\r\n%x",data[i]);
  }
}

void Print_u32_d(u32 *data, u16 len)
{
  u16 i;
  for (i = 0;i <len ;i++)
  {
    u1_printf("\r\n%d",data[i]);
  }
}
void Print_u32_x(u32 *data, u16 len)
{
  u16 i;
  for (i = 0;i <len ;i++)
  {
    u1_printf("\r\n%x",data[i]);
  }
}

