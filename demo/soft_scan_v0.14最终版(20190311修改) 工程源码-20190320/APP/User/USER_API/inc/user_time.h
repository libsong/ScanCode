#ifndef __TIME_H__
#define	__TIME_H__

#include "stm32f10x.h"
#include "user_conf.h"

void HAL_IncTick(void);
uint32_t SysTick_GetCurrent(void);
uint32_t SysTick_GetLapse(uint32_t u32PreTick);

#endif

