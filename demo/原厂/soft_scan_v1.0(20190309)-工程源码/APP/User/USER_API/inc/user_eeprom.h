#ifndef EEPROMAPP__H
#define EEPROMAPP__H

//#include "usrApp.h"

#define EE_KEY_SCREEN 	1  
#define EE_KEY_DISPLAY_AREA 2

#define EE_KEY_TEST 	0x0f


void WriteDisplayAreaInfo(void);
void ReadDisplayAreaInfo(void);
void WriteScreenInfo(void);
void ReadScreenInfo(void);
unsigned char FeepromAppReset(void);
void FeepromAppInit(void);

void FeepromPostMutex(void);
int FeepromPendMutex (void);
int FeepromCreateMutex(void);
long feepromFunc_store(int argc,char **argv);

#endif

