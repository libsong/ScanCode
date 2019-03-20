#ifndef __USER_MOTOR_H__
#define __USER_MOTOR_H__

#include "stm32f10x.h"
#include "user_conf.h"
/***************************************************************************************************
; PWM直流风机
****************************************************************************************************/
#define BOARD_FREQ                      12  // MHz
#define MOTOR_PWM_FREQ           4000//4000,Hz
/***************************************************************************************************
; 步进电机
****************************************************************************************************/
#define MOTOR_STEP_PLUSE_PER_CIRCLE             2048   // 每圈多少脉冲数，取决于电机参数
#define MOTOR_STEP_SPEED_DEG_PER_SEC          8  // 每秒旋转角度,4
#define MOTOR_STEP_PLUSE_PERIOD_MS              360000/(2048*MOTOR_STEP_SPEED_DEG_PER_SEC)

#define MOTOR_STEP_ANGLE_BACK_TO_ORIGIN   200 //归位用的角度
#define MOTOR_STEP_ANGLE_START                        50// 扫风时的初始角度，最小角度
#define MOTOR_STEP_ANGLE_END                            150// 扫风时的终止角度，最大角度
#define MOTOR_STEP_ANGLE_SET_FIX                    (MOTOR_STEP_ANGLE_START + MOTOR_STEP_ANGLE_END)/2  //不扫风时的开启角度

/****************************************************************************************************
;------------------------------------------------------------------------------------------------
; 步进电机的驱动信号必须为脉冲信号，转动的速度和脉冲的频率成正比。
; 本步进电机步进角为7.5度(5.625度)，一圈360度，需要48(64)个脉冲完成
;-----------------------------------------------------------------------------------------------
; A组线圈对应PA8
; B组线圈对应PA7
; C组线圈对应PA6
; D组线圈对应PA5
; 正转次序:AB组--BC组--CD组--DA组(即一个脉冲，正转7.5度)
;
****************************************************************************************************/
typedef enum
{
  MOTOR_STEP_PHASE_A = 0x01,
  MOTOR_STEP_PHASE_B = 0x02,
  MOTOR_STEP_PHASE_C = 0x04,
  MOTOR_STEP_PHASE_D = 0x08
}Motor_Step_Phase_e;
// 步进电机驱动引脚
#define MOTOR_STEP_GPIO GPIOA

#define MOTOR_STEP_GPIO_A GPIO_Pin_8  //A相
#define MOTOR_STEP_GPIO_B GPIO_Pin_7  //B相
#define MOTOR_STEP_GPIO_C GPIO_Pin_6  //C相
#define MOTOR_STEP_GPIO_D GPIO_Pin_5  //D相

#define MOTOR_STEP_A_RESET GPIO_ResetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_A); //拉低
#define MOTOR_STEP_A_SET      GPIO_SetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_A); //拉高,线圈没有电流

#define MOTOR_STEP_B_RESET GPIO_ResetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_B); //拉低
#define MOTOR_STEP_B_SET      GPIO_SetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_B); //拉高,线圈没有电流

#define MOTOR_STEP_C_RESET GPIO_ResetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_C); //拉低
#define MOTOR_STEP_C_SET      GPIO_SetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_C); //拉高,线圈没有电流

#define MOTOR_STEP_D_RESET GPIO_ResetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_D); //拉低
#define MOTOR_STEP_D_SET      GPIO_SetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_D); //拉高,线圈没有电流

typedef enum
{
  MOTOR_STEP_WORK_STATE_BACK_TO_ORIG_ANGLE = 0, //返回到初始位置
  MOTOR_STEP_WORK_STATE_TO_FIXED_ANGLE,                 // 开启到固定的位置
  MOTOR_STEP_WORK_STATE_RUN                                         //正在工作，扫风或不扫风
}Motor_Step_Work_Inner_State_e;

typedef enum
{
  MOTOR_STEP_WORK_CMD_IDLE = 0,
  MOTOR_STEP_WORK_CMD_START,
  MOTOR_STEP_WORK_CMD_STOP
}Motor_Step_Work_Cmd_e;

typedef enum
{
  MOTOR_STEP_WORK_MODEL_START_SCAN = 0, //启动扫风
  MOTOR_STEP_WORK_MODEL_STOP_SCAN         //停止扫风，停在当前位置
}Motor_Step_Work_Model_e;

typedef enum
{
  MOTOR_STEP_RUN_DIRECTION_FORWARD = 0,
  MOTOR_STEP_RUN_DIRECTION_REVERSE
}Motor_Step_Run_Direction_e;

typedef struct
{
  Motor_Step_Run_Direction_e direction;       //方向
  u16 speed;        //每秒钟旋转的度数
  u32 startAngle; //扫风的起始角度，该角度并不是最小角度，最小角度为全闭
  u32 endAngle;   //扫风的终止角度，该角度并不是最大角度，最大角度为全开
  u32 setAngle;  //设置的角度，在扫风时，该角度等于当前角度，在关闭时，该角度会被保存到flash里面，只有在固定角度时才有用
  u32 curAngle;  //当前角度，度，用于记录当前角度，
  u32 resetAngle;  //复位扫风机角度
  Motor_Step_Work_Cmd_e cmd; // 0:start, 1:stop
  Motor_Step_Work_Model_e model;   //工作模式: 0 = 扫风, 1 = 固定角度，上次关机时使用的模式
}Motor_Step_t;

extern Motor_Step_t MotorStep;
extern u8 MotorPwmDuty;

void MOTOR_Pwm_Init(void);
void MOTOR_Pwm_SetDuty(u8 duty);
void MOTOR_Step_Init(void);
void MOTOR_Step_Run(Motor_Step_t *motor);
void MOTOR_Step_SetModel(Motor_Step_Work_Model_e model);
void MOTOR_Step_SetCmd(Motor_Step_Work_Cmd_e cmd);

void MOTOR_Step_RunDirection(Motor_Step_Run_Direction_e direction);
void MOTOR_Step_Stop(void);

#endif

