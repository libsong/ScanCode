#ifndef USRAPP_H
#define USRAPP_H


typedef struct _REVPRO_MSG
{
	unsigned char  dat[100];//100
}REVPRO_MSG;


void usrTask(void const * argument);
void RevProSend(REVPRO_MSG *pRevProMsg);
int RevProCreateQueue(void);
int RevProPendQueue (REVPRO_MSG *pRevProMsg);

#endif
