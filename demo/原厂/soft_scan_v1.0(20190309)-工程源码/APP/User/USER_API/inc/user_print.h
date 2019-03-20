/******************** ��ɳ��ʿ������ ********************
 * �ļ���  ��user_print.h
 * ����    ��       
 * ����ƽ̨��
 * ��汾  ��ST3.0.0  																										  
 * ��Ŀ���ƣ����ܹ����ն�
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


