/****************************************
 * 文件名  ：main.c
 * 描述    ：
 * 修改时间: 2015-06-06       
 * 开发平台：
 * 库版本  ：ST3.0.0  																										  
 * 项目名称：
*********************************************************/ 
#include "user_conf.h"
#include "user_wwdg.h"
#include "user_screen.h"

//lbs
extern void heartBeat (void);
extern u8 g_usart2Pack;

extern UART_RCV_T  UART2_RCV_S;
extern SCREEN Screen;
 
static void GpioPreInit(void);
static void MCU_Init(void);

int main(void)
{    
 	MCU_Init();
  while (1)
  {		
		IWatchDogClear();
		scanCamera();
		displayTask();
//		ScreenTask();//跟上位机通信任务，自带的通信协议
		
		heartBeat();
		if (g_usart2Pack == 1) {
			g_usart2Pack = 0;
		}
  }
}
static void MCU_Init(void)
{
  SystemInit();	//配置系统时钟为 72M 
  mem_init();	
//IAP_DataInit();
  USART1_Config(); //USART1 config for debug
	USART2_Config(uart2BaudRate); //
	USART3_Config();
	USART4_Config();
	USART5_Config();
	WatchDogInit();
	GpioPreInit();
	FeepromAppInit();
	FontLibInit();
	ScreenInit();
	mymemset(Screen.screenbuff,0,Screen.size);
	LedDisplayInit();
}

static void GpioPreInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
}

 


