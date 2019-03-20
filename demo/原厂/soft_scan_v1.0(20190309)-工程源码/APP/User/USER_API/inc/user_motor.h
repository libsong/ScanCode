#ifndef __USER_MOTOR_H__
#define __USER_MOTOR_H__

#include "stm32f10x.h"
#include "user_conf.h"
/***************************************************************************************************
; PWMֱ�����
****************************************************************************************************/
#define BOARD_FREQ                      12  // MHz
#define MOTOR_PWM_FREQ           4000//4000,Hz
/***************************************************************************************************
; �������
****************************************************************************************************/
#define MOTOR_STEP_PLUSE_PER_CIRCLE             2048   // ÿȦ������������ȡ���ڵ������
#define MOTOR_STEP_SPEED_DEG_PER_SEC          8  // ÿ����ת�Ƕ�,4
#define MOTOR_STEP_PLUSE_PERIOD_MS              360000/(2048*MOTOR_STEP_SPEED_DEG_PER_SEC)

#define MOTOR_STEP_ANGLE_BACK_TO_ORIGIN   200 //��λ�õĽǶ�
#define MOTOR_STEP_ANGLE_START                        50// ɨ��ʱ�ĳ�ʼ�Ƕȣ���С�Ƕ�
#define MOTOR_STEP_ANGLE_END                            150// ɨ��ʱ����ֹ�Ƕȣ����Ƕ�
#define MOTOR_STEP_ANGLE_SET_FIX                    (MOTOR_STEP_ANGLE_START + MOTOR_STEP_ANGLE_END)/2  //��ɨ��ʱ�Ŀ����Ƕ�

/****************************************************************************************************
;------------------------------------------------------------------------------------------------
; ��������������źű���Ϊ�����źţ�ת�����ٶȺ������Ƶ�ʳ����ȡ�
; ���������������Ϊ7.5��(5.625��)��һȦ360�ȣ���Ҫ48(64)���������
;-----------------------------------------------------------------------------------------------
; A����Ȧ��ӦPA8
; B����Ȧ��ӦPA7
; C����Ȧ��ӦPA6
; D����Ȧ��ӦPA5
; ��ת����:AB��--BC��--CD��--DA��(��һ�����壬��ת7.5��)
;
****************************************************************************************************/
typedef enum
{
  MOTOR_STEP_PHASE_A = 0x01,
  MOTOR_STEP_PHASE_B = 0x02,
  MOTOR_STEP_PHASE_C = 0x04,
  MOTOR_STEP_PHASE_D = 0x08
}Motor_Step_Phase_e;
// ���������������
#define MOTOR_STEP_GPIO GPIOA

#define MOTOR_STEP_GPIO_A GPIO_Pin_8  //A��
#define MOTOR_STEP_GPIO_B GPIO_Pin_7  //B��
#define MOTOR_STEP_GPIO_C GPIO_Pin_6  //C��
#define MOTOR_STEP_GPIO_D GPIO_Pin_5  //D��

#define MOTOR_STEP_A_RESET GPIO_ResetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_A); //����
#define MOTOR_STEP_A_SET      GPIO_SetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_A); //����,��Ȧû�е���

#define MOTOR_STEP_B_RESET GPIO_ResetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_B); //����
#define MOTOR_STEP_B_SET      GPIO_SetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_B); //����,��Ȧû�е���

#define MOTOR_STEP_C_RESET GPIO_ResetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_C); //����
#define MOTOR_STEP_C_SET      GPIO_SetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_C); //����,��Ȧû�е���

#define MOTOR_STEP_D_RESET GPIO_ResetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_D); //����
#define MOTOR_STEP_D_SET      GPIO_SetBits(MOTOR_STEP_GPIO, MOTOR_STEP_GPIO_D); //����,��Ȧû�е���

typedef enum
{
  MOTOR_STEP_WORK_STATE_BACK_TO_ORIG_ANGLE = 0, //���ص���ʼλ��
  MOTOR_STEP_WORK_STATE_TO_FIXED_ANGLE,                 // �������̶���λ��
  MOTOR_STEP_WORK_STATE_RUN                                         //���ڹ�����ɨ���ɨ��
}Motor_Step_Work_Inner_State_e;

typedef enum
{
  MOTOR_STEP_WORK_CMD_IDLE = 0,
  MOTOR_STEP_WORK_CMD_START,
  MOTOR_STEP_WORK_CMD_STOP
}Motor_Step_Work_Cmd_e;

typedef enum
{
  MOTOR_STEP_WORK_MODEL_START_SCAN = 0, //����ɨ��
  MOTOR_STEP_WORK_MODEL_STOP_SCAN         //ֹͣɨ�磬ͣ�ڵ�ǰλ��
}Motor_Step_Work_Model_e;

typedef enum
{
  MOTOR_STEP_RUN_DIRECTION_FORWARD = 0,
  MOTOR_STEP_RUN_DIRECTION_REVERSE
}Motor_Step_Run_Direction_e;

typedef struct
{
  Motor_Step_Run_Direction_e direction;       //����
  u16 speed;        //ÿ������ת�Ķ���
  u32 startAngle; //ɨ�����ʼ�Ƕȣ��ýǶȲ�������С�Ƕȣ���С�Ƕ�Ϊȫ��
  u32 endAngle;   //ɨ�����ֹ�Ƕȣ��ýǶȲ��������Ƕȣ����Ƕ�Ϊȫ��
  u32 setAngle;  //���õĽǶȣ���ɨ��ʱ���ýǶȵ��ڵ�ǰ�Ƕȣ��ڹر�ʱ���ýǶȻᱻ���浽flash���棬ֻ���ڹ̶��Ƕ�ʱ������
  u32 curAngle;  //��ǰ�Ƕȣ��ȣ����ڼ�¼��ǰ�Ƕȣ�
  u32 resetAngle;  //��λɨ����Ƕ�
  Motor_Step_Work_Cmd_e cmd; // 0:start, 1:stop
  Motor_Step_Work_Model_e model;   //����ģʽ: 0 = ɨ��, 1 = �̶��Ƕȣ��ϴιػ�ʱʹ�õ�ģʽ
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

