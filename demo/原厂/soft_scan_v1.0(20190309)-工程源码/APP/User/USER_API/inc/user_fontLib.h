
#ifndef __FONTLIB_H__
#define __FONTLIB_H__


extern const unsigned char DotumChe[][16];

static void GTW_Read_nByte(unsigned char *BUFF, unsigned long addr, unsigned int n);
static void GTY_Read_nByte(unsigned char *BUFF, unsigned long addr, unsigned int n);
static unsigned char GT_Readbyte(unsigned long addr)  ;
static unsigned long  GB2312_Addr(const unsigned char *ss, unsigned char type);

void FontLibInit(void);
void GetFont(const unsigned char *str, unsigned char lens,void *buf);
void GetBmpFont(const unsigned char id, void *Dest);

#endif



