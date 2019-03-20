#ifndef __USER_CMD_QUEUE_H__
#define __USER_CMD_QUEUE_H__

/*! 
 *  \file cmd_queue.h
 *  \brief ����ָ�����
 *  \version 1.0
 *  \date 2012-2015
 *  \copyright  
 */

//#include "hmi_driver.h
#define CMD_MAX_SIZE 100    //����ָ���С��������Ҫ����
#define QUEUE_MAX_SIZE 1000  //ָ����ܻ����������Ը�����Ҫ����

typedef unsigned char qdata;
typedef unsigned short qsize;

/*! 
 *  \brief  ���ָ������
 */
extern void queue_reset(void);

/*! 
 * \brief  ���ָ������
 * \detial ���ڽ��յ����ݣ�ͨ���˺�������ָ����� 
 *  \param  _data ָ������
 */
extern void queue_push(qdata _data);

/*! 
 *  \brief  ��ָ�������ȡ��һ��������ָ��
 *  \param  cmd ָ����ջ�����
 *  \param  buf_len ָ����ջ�������С
 *  \return  ָ��ȣ�0��ʾ������������ָ��
 */
extern qsize queue_find_cmd(qdata *cmd,qsize buf_len);

#endif
