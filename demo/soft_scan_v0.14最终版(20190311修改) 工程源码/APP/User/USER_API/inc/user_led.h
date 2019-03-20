#ifndef __USER_LED_H__
#define __USER_LED_H__

#include "stm32f10x.h"
#include "user_conf.h"
//========================================LED数码管显示=================================
typedef enum
{
  LED_NUM_SECTION_A = 0x0001,
  LED_NUM_SECTION_B = 0x0002,
  LED_NUM_SECTION_C = 0x0004,
  LED_NUM_SECTION_D = 0x0008,
  LED_NUM_SECTION_E = 0x0010,
  LED_NUM_SECTION_F = 0x0020,
  LED_NUM_SECTION_G = 0x0040,
  LED_NUM_SECTION_DP = 0x0080
}LED_Num_Section_e;

typedef enum
{
  LED_NUM_DIGIT_SINGLE = 0x00,
  LED_NUM_DIGIT_TENS
}LED_Num_Digit_e;

// 2个LED 数码管显示
// D1-->G, D2-->DP, D3-->A, D4-->F, D5-->D, D6-->E, D7-->C, D8-->B, CS1-->GIG2, CS2-->GIG1
// CS1对应个位，即右边的那一位
// CS2对应十位，即左边的那一位
// 0: A,B,C,D,E,F
// 1: B,C
// 2: A,B,G,E,D
// 3: A,B,G,C,D
// 4: B,C,F,G
// 5: A,C,D,F,G,
// 6: A,C,D,E,F,G
// 7: A,B,C
// 8: A,B,C,D,E,F,G
// 9: A,B,C,D,F,G
#define LED_NUM_GPIO GPIOB
#define LED_NUM_GPIO_D1 GPIO_Pin_0 //G
#define LED_NUM_GPIO_D2 GPIO_Pin_1 //DP
#define LED_NUM_GPIO_D3 GPIO_Pin_2 //A
#define LED_NUM_GPIO_D4 GPIO_Pin_3 //F
#define LED_NUM_GPIO_D5 GPIO_Pin_4 //D
#define LED_NUM_GPIO_D6 GPIO_Pin_5 //E
#define LED_NUM_GPIO_D7 GPIO_Pin_6 //C
#define LED_NUM_GPIO_D8 GPIO_Pin_7 //B
#define LED_NUM_GPIO_CS1 GPIO_Pin_8  //个位
#define LED_NUM_GPIO_CS2 GPIO_Pin_9  //十位

#define LED_NUM_D1_SET GPIO_SetBits(LED_NUM_GPIO, LED_NUM_GPIO_D1); //拉高
#define LED_NUM_D2_SET GPIO_SetBits(LED_NUM_GPIO, LED_NUM_GPIO_D2); //拉高
#define LED_NUM_D3_SET GPIO_SetBits(LED_NUM_GPIO, LED_NUM_GPIO_D3); //拉高
#define LED_NUM_D4_SET GPIO_SetBits(LED_NUM_GPIO, LED_NUM_GPIO_D4); //拉高
#define LED_NUM_D5_SET GPIO_SetBits(LED_NUM_GPIO, LED_NUM_GPIO_D5); //拉高
#define LED_NUM_D6_SET GPIO_SetBits(LED_NUM_GPIO, LED_NUM_GPIO_D6); //拉高
#define LED_NUM_D7_SET GPIO_SetBits(LED_NUM_GPIO, LED_NUM_GPIO_D7); //拉高
#define LED_NUM_D8_SET GPIO_SetBits(LED_NUM_GPIO, LED_NUM_GPIO_D8); //拉高

#define LED_NUM_D1_RESET GPIO_ResetBits(LED_NUM_GPIO, LED_NUM_GPIO_D1); //拉低
#define LED_NUM_D2_RESET GPIO_ResetBits(LED_NUM_GPIO, LED_NUM_GPIO_D2); //拉低
#define LED_NUM_D3_RESET GPIO_ResetBits(LED_NUM_GPIO, LED_NUM_GPIO_D3); //拉低
#define LED_NUM_D4_RESET GPIO_ResetBits(LED_NUM_GPIO, LED_NUM_GPIO_D4); //拉低
#define LED_NUM_D5_RESET GPIO_ResetBits(LED_NUM_GPIO, LED_NUM_GPIO_D5); //拉低
#define LED_NUM_D6_RESET GPIO_ResetBits(LED_NUM_GPIO, LED_NUM_GPIO_D6); //拉低
#define LED_NUM_D7_RESET GPIO_ResetBits(LED_NUM_GPIO, LED_NUM_GPIO_D7); //拉低
#define LED_NUM_D8_RESET GPIO_ResetBits(LED_NUM_GPIO, LED_NUM_GPIO_D8); //拉低

#define LED_NUM_CS1_EN GPIO_ResetBits(LED_NUM_GPIO, LED_NUM_GPIO_CS1); //拉低
#define LED_NUM_CS1_DIS GPIO_SetBits(LED_NUM_GPIO, LED_NUM_GPIO_CS1); //拉低

#define LED_NUM_CS2_EN GPIO_ResetBits(LED_NUM_GPIO, LED_NUM_GPIO_CS2); //拉低
#define LED_NUM_CS2_DIS GPIO_SetBits(LED_NUM_GPIO, LED_NUM_GPIO_CS2); //拉低

#define LED_NUM_GPIO_A LED_NUM_GPIO_D3
#define LED_NUM_GPIO_B LED_NUM_GPIO_D8
#define LED_NUM_GPIO_C LED_NUM_GPIO_D7
#define LED_NUM_GPIO_D LED_NUM_GPIO_D5
#define LED_NUM_GPIO_E LED_NUM_GPIO_D6
#define LED_NUM_GPIO_F LED_NUM_GPIO_D4
#define LED_NUM_GPIO_G LED_NUM_GPIO_D1
#define LED_NUM_GPIO_DP LED_NUM_GPIO_D2

#define LED_NUM_A_OFF LED_NUM_D3_SET
#define LED_NUM_B_OFF LED_NUM_D8_SET
#define LED_NUM_C_OFF LED_NUM_D7_SET
#define LED_NUM_D_OFF LED_NUM_D5_SET
#define LED_NUM_E_OFF LED_NUM_D6_SET
#define LED_NUM_F_OFF LED_NUM_D4_SET
#define LED_NUM_G_OFF LED_NUM_D1_SET
#define LED_NUM_DP_OFF LED_NUM_D2_SET

#define LED_NUM_A_ON LED_NUM_D3_RESET
#define LED_NUM_B_ON LED_NUM_D8_RESET
#define LED_NUM_C_ON LED_NUM_D7_RESET
#define LED_NUM_D_ON LED_NUM_D5_RESET
#define LED_NUM_E_ON LED_NUM_D6_RESET
#define LED_NUM_F_ON LED_NUM_D4_RESET
#define LED_NUM_G_ON LED_NUM_D1_RESET
#define LED_NUM_DP_ON LED_NUM_D2_RESET
//=================================End of LED数码管显示=======

//=================================LED灯显示=================================
typedef enum
{
  LED_DIODE_RUN       = 0x01,
  LED_DIODE_TIMER   = 0x02,
  LED_DIODE_POWER = 0x04,
  LED_DIODE_DUST    = 0x08
}LED_Diode_e;
typedef enum
{
  LED_DIODE_TURN_OFF = 0,
  LED_DIODE_TURN_ON,
  LED_DIODE_TURN_SLOW_BLINK,
  LED_DIODE_TURN_FAST_BLINK,
}LED_Diode_Mode_e;
// 4个LED灯显示
#define LED_DIODE_GPIO GPIOB

#define LED_DIODE_GPIO_RUN GPIO_Pin_12  //运行指示灯
#define LED_DIODE_GPIO_TIMER GPIO_Pin_13 //定时指示灯
#define LED_DIODE_GPIO_POWER GPIO_Pin_14 //上电指示灯
#define LED_DIODE_GPIO_DUST GPIO_Pin_15 //尘满指示灯,0.5s闪烁说明尘满

#define LED_DIODE_RUN_ON GPIO_ResetBits(LED_DIODE_GPIO, LED_DIODE_GPIO_RUN); //拉低
#define LED_DIODE_RUN_OFF GPIO_SetBits(LED_DIODE_GPIO, LED_DIODE_GPIO_RUN); //拉高

#define LED_DIODE_TIMER_ON GPIO_ResetBits(LED_DIODE_GPIO, LED_DIODE_GPIO_TIMER); //拉低
#define LED_DIODE_TIMER_OFF GPIO_SetBits(LED_DIODE_GPIO, LED_DIODE_GPIO_TIMER); //拉高

#define LED_DIODE_POWER_ON GPIO_ResetBits(LED_DIODE_GPIO, LED_DIODE_GPIO_POWER); //拉低
#define LED_DIODE_POWER_OFF GPIO_SetBits(LED_DIODE_GPIO, LED_DIODE_GPIO_POWER); //拉高

#define LED_DIODE_DUST_ON GPIO_ResetBits(LED_DIODE_GPIO, LED_DIODE_GPIO_DUST); //拉低
#define LED_DIODE_DUST_OFF GPIO_SetBits(LED_DIODE_GPIO, LED_DIODE_GPIO_DUST); //拉高
//=================================End of LED灯显示=================================

void LED_NumInit(void);
void LED_Num_Disp(u8 num, u8 turnOn );

void LED_DiodeInit(void);
void LED_Diode_Disp(u8 runLed, u8 timerLed, u8 powerLed, u8 dustFullLed);

u16 LED_Diode_Disp_Run(u8 mode);
u16 LED_Diode_Disp_Timer(u8 mode);
u16 LED_Diode_Disp_Power(u8 mode);
u16 LED_Diode_Disp_Dust(u8 mode);


#endif


