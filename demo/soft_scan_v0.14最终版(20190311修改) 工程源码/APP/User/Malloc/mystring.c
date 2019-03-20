#include "sys.h"
int mystrcmp(const char *left, const char *right)
{
  const char *p=left;
  const char *q=right;
  while(*p!='\0'&&*q!='\0'&&*p==*q)
  {
		p++;q++;
  }
  if(*p=='\0'&&*q=='\0')
  return 0;
  return *p-*q;
}
char *mystrcat(char *dest,const char *src)
{
  const char *p=src;
  char *q=dest;
  while(*q!='\0')
  q++;
  while(*p!='\0')
  *q++=*p++;
  *q='\0';
  return dest;
}
char *mystrcpy(char *dest,const char *src)
{
  const char *p=src;
  char *q=dest;
  while(*p!='\0')
  {
		*q++=*p++;
  }
  *q='\0';
  return dest;
}
int mystrlen(char *p)
{
    int a = 0;
    while ((*p++ )!='\0')
    {
        a++;
    }
    return a;
}
char * mystrstr( const char* s1, const char* s2)
{
	char *p1,*p2;
//	p1= s1;
//	p2 = s2;
	while(*s1 != '\0' && *s2 != '\0')
	{
		if(*s1++ != *s2++)//?????,s1?s2??,??,?p1???????
		{
			s2 = p2;//s2?????
			s1 = ++p1;//??????????s2
		}
	}
	if(*s2 == '\0')
	{
		return p1;
	}
	return 0;
}

char *mystrrstr(const char *s1, const char *s2)
{
	char *last = 0;//?????????????
	char *cur = mystrstr(s1,s2);//??????s2
	while(cur != 0)
	{
		last = cur;//????????????s2
		cur = mystrstr(cur+1,s2);//??????????
	}
	return last;//??????,?????????NULL
}
char *mystrncpy( char *dst, const char *src, int num )  
{  
    char    *adress = dst;  
  
    while ( num-- != 0 )  
    {  
        while ( ( *dst++ = *src++ ) != '\0' )  
            ;  
    }  
  
    return  adress;  
} 