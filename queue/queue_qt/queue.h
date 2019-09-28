#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>



typedef uint16_t QueSize_t;
typedef uint8_t QueData_t;



typedef enum QUEUE_OPT_RESULT_T
{
    QUEUE_OPT_SUCCESS = 0x00U,
    QUEUE_OPT_IS_FULL,
    QUEUE_OPT_IS_EMPTY,
    QUEUE_OPT_PARAM_ERR,
    QUEUE_OPT_ALL_RES
}QueueOptRes_t;

typedef struct QUEUE_T
{
    QueData_t *Que_DataPtr;     /*!< ���ݻ���ָ�� */
    QueSize_t Que_FrontIndex;   /*!< ����ǰָ�� */
    QueSize_t Que_RearIndex;    /*!< ���к�ָ�� */
    QueSize_t Que_UseSize;      /*!< ������ʹ�ô�С */
    QueSize_t Que_SingleSize;   /*!< �������ݵ�����С */
    QueSize_t Que_MaxSize;      /*!< �������ռ� */
}Queue_t;

QueueOptRes_t Que_Init(Queue_t *pQue, QueSize_t maxSize, QueSize_t datSize, void *pDatBase);

QueueOptRes_t Que_Write(Queue_t *pQue, const void *pDat);

QueueOptRes_t Que_OverWrite(Queue_t *pQue, const void *pDat);

QueueOptRes_t Que_Read(Queue_t *pQue, void *pDat);

QueueOptRes_t Que_OnlyRead(Queue_t *pQue, void *pDat);


#endif // QUEUE_H
