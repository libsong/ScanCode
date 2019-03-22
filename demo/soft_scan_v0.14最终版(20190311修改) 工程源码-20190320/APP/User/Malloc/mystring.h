#ifndef __MYSTRING_H
#define __MYSTRING_H

extern int mystrcmp(const char *left,const char *right);
extern char *mystrcat(char *dest,const char *src);
extern char *mystrcpy(char *dest,const char *src);
extern int mystrlen(char *p);
extern char * mystrstr(char const * s1,char const *s2);
extern char *mystrrstr(char const *s1,char const *s2);
extern char *mystrncpy( char *dst, const char *src, int num );

#endif