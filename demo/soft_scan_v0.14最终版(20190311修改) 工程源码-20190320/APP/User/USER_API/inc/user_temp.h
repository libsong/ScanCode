#ifndef __USER_TEMP_H__
#define __USER_TEMP_H__

#include "stm32f10x.h"
#include "user_conf.h"

extern __IO uint32_t TempADCConvertedValue[1];

void TEMP_PinInit(void);

#endif


