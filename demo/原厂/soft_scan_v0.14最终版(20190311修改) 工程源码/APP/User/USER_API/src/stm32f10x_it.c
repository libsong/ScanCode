/**
  ******************************************************************************
  * @file    Project/Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.0.0
  * @date    04/06/2009
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "user_usart1.h"
#include "user_usart2.h"
#include "user_usart3.h"
#include "user_time.h"
#include "user_cmd_queue.h"
#include "user_display.h"
#include "user_screen.h"
#include "user_uart4.h"
extern UART_RCV_T  UART2_RCV_S;

volatile unsigned long sysIntCnt = 0;

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval : None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
void SysTick_Handler(void)//定时1ms
{
  static uint8_t time=0;
//  usart2_rec_timeout();
//	if(time++ >=10)
//	{
		time=0;
		HAL_IncTick();
		usart1_rec_timeout();
		usart2_rec_timeout(); 
		usart4_rec_timeout(); 
		usart5_rec_timeout();  
//	}
	disTiming();
	
	//add lbs
	sysIntCnt++;
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval : None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 
// 调试串口，也用于跟串口转以太网模块相连
void USART1_IRQHandler( void )
{
  static u8 rcv;//__IO
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {		
    	/* Read one byte from the receive data register */
		USART_ClearFlag(USART1,USART_FLAG_RXNE);  
	  USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    rcv = USART_ReceiveData(USART1);	
		if(UART1_RCV_S.FlagStatus==0)
		{
			UART1_RCV_S.FlagStatus = 1;
			UART1_RCV_S.tick = USART_RCV_TIME;
			UART1_RCV_S.cnt=0;
			memset((char *)&UART1_RCV_S.buff[0],0,USART_RCV_LEN);
		}
		if(UART1_RCV_S.cnt<USART_RCV_LEN)
		{
			UART1_RCV_S.buff[UART1_RCV_S.cnt++]=rcv;	
		}
		else
		{
			UART1_RCV_S.cnt=0;
		}
  }
	else  if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)//注意！不能使用if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)来判断
	{
		USART_ReceiveData(USART1);
		USART_ClearFlag(USART1, USART_FLAG_ORE);
	}  
}

//// for SIM900A, the function of receive GPRS and GSM data
//void USART2_IRQHandler( void )
//{
//  __IO u8 rcv;
//  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//  {
////		if(UART2_RCV_S.FlagStatus==0)
////		{
//			UART2_RCV_S.FlagStatus = 1;
//			UART2_RCV_S.tick = USART2_RCV_TIME;
////			UART2_RCV_S.cnt=0;
////		}
//		/* Read one byte from the receive data register */
//    rcv = USART_ReceiveData(USART2);
//		queue_push(rcv);//
//  }
//	else  if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)//注意！不能使用if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)来判断
//	{
//		USART_ReceiveData(USART2);
//		USART_ClearFlag(USART2, USART_FLAG_ORE);
//	}
////	if(USART_GetITStatus(USART2, USART_IT_PE | USART_IT_FE | USART_IT_NE) != RESET)//出错
////	{
////		USART_ClearITPendingBit(USART2, USART_IT_PE | USART_IT_FE | USART_IT_NE);
////	}
////  
////  	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
//}
//485通信中断， 
void USART3_IRQHandler( void )
{
  static u8 rcv;//__IO
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {		
    	/* Read one byte from the receive data register */
    rcv = USART_ReceiveData(USART3);
    //RS485_BuildIncomeFrame(1, (u8*)&rcv, &Rs485Buf, &Rs485Frame);
//    WLS433_BuildIncomeFrame(1, (u8*)&rcv, &WLS433RcvBuf, &WLS433RcvFrame);
  }
}

//  
void UART4_IRQHandler( void )
{
  static u8 rcv;//__IO
  if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
  {		
    	/* Read one byte from the receive data register */
	  USART_ClearITPendingBit(UART4,USART_IT_RXNE);
    rcv = USART_ReceiveData(UART4);	
		if(UART4_RCV_S.FlagStatus==0)
		{
			UART4_RCV_S.FlagStatus = 1;
			UART4_RCV_S.tick = USART_RCV_TIME;
			UART4_RCV_S.cnt=0;
			memset((char *)&UART4_RCV_S.buff,0,USART_RCV_LEN);
		}
		if(UART4_RCV_S.cnt<USART_RCV_LEN)
		{
			UART4_RCV_S.buff[UART4_RCV_S.cnt++]=rcv;
		}
		else
		{
			UART4_RCV_S.cnt = 0;
		}
  }
	else  if (USART_GetFlagStatus(UART4, USART_FLAG_ORE) != RESET)//注意！不能使用if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)来判断
	{
		USART_ReceiveData(UART4);
		USART_ClearFlag(UART4, USART_FLAG_ORE);
	}	
}
//  
void UART5_IRQHandler( void )
{
  static u8 rcv;//__IO
  if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
  {		
    	/* Read one byte from the receive data register */
	  USART_ClearITPendingBit(UART5,USART_IT_RXNE);
    rcv = USART_ReceiveData(UART5);	
		if(UART5_RCV_S.FlagStatus==0)
		{
			UART5_RCV_S.FlagStatus = 1;
			UART5_RCV_S.tick = USART_RCV_TIME;
			UART5_RCV_S.cnt=0;
			memset((char *)&UART5_RCV_S.buff[0],0,USART_RCV_LEN);
		}
		if(UART5_RCV_S.cnt<USART_RCV_LEN)
		{
			UART5_RCV_S.buff[UART5_RCV_S.cnt++]=rcv;	
		}
		else
		{
			UART5_RCV_S.cnt=0;
		}
  }
	else  if (USART_GetFlagStatus(UART5, USART_FLAG_ORE) != RESET)//注意！不能使用if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)来判断
	{
		USART_ReceiveData(UART5);
		USART_ClearFlag(UART5, USART_FLAG_ORE);
	}	
	
}
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
