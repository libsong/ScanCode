/******************** 长沙博士工作室 ********************
 * 文件名  ：user_print.h
 * 描述    ：       
 * 开发平台：
 * 库版本  ：ST3.0.0  																										  
 * 项目名称：智能供氧终端
*********************************************************/
#ifndef __USER_PRINT_H
#define __USER_PRINT_H
#include "stm32f10x.h"

void Print_u8_d(u8 *data, u16 len);
void Print_u8_x(u8 *data, u16 len);
void Print_u16_d(u16 *data, u16 len);
void Print_u16_x(u16 *data, u16 len);
void Print_u32_d(u32 *data, u16 len);
void Print_u32_x(u32 *data, u16 len);

#endif


