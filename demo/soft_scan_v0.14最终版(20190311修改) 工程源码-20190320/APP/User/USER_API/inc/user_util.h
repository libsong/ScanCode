/******************** ��ɳ��ʿ������ ********************
 * �ļ���  ��user_util.h
 * ����    ��       
 * ����ƽ̨��
 * ��汾  ��ST3.0.0  																										  
 * ��Ŀ���ƣ����ܹ����ն�
*********************************************************/
#ifndef __USER_UTIL_H
#define __USER_UTIL_H
#include "stm32f10x.h"

u8 UTIL_XorParity(u8 *p,u16 len);
u8 UTIL_AddParity(u8 *p,u16 len);

u8 Str_Cmp(u8* str1, u8*str2, u16 len);
u8 ChoiseSort(u32 *a, u16 n);

#endif


