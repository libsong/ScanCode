#include "stm32f10x.h"

#define COMM_OUTSYS_GPIO GPIOA
#define COMM_OUTSYS_TX_PIN GPIO_Pin_2
#define COMM_OUTSYS_RX_PIN GPIO_Pin_3
#define COMM_OUTSYS_RX_VALUE GPIO_ReadInputDataBit(COMM_OUTSYS_GPIO, COMM_OUTSYS_RX_PIN)

//// 与外机的通信
//typedef struct  // rebuild from COMM_FRAME_RX_8BIT, 16bits in used
//{
//  // The body of the frame
//  u8 sop1;
//  u8 sop2;
//  u8 len; // len of data field, each data is 8 bits
//  WLS433_Frame_Type_e type; // the type of the data
//  u8 addrLo;
//  u8 addrMd;
//  u8 addrHi;  
//  WLS433_Frame_Cmd_e cmd; // 8bits
//  u8 data[WLS433_FRAME_MAX_DATA_LEN] ;
//  u8 fcs;
//  u8 end;
//  // This is the control information used to rebuild the frame, not the frame data
//  WLS433_Frame_Ctrl_t ctrl;
//} Comm_OutSys_Frame_t;



