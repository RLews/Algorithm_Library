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
    QueData_t *Que_DataPtr;     /*!< 数据缓存指针 */
    QueSize_t Que_FrontIndex;   /*!< 队列前指针 */
    QueSize_t Que_RearIndex;    /*!< 队列后指针 */
    QueSize_t Que_UseSize;      /*!< 队列已使用大小 */
    QueSize_t Que_SingleSize;   /*!< 队列数据单个大小 */
    QueSize_t Que_MaxSize;      /*!< 队列最大空间 */
}Queue_t;

QueueOptRes_t Que_Init(Queue_t *pQue, QueSize_t maxSize, QueSize_t datSize, void *pDatBase);

QueueOptRes_t Que_Write(Queue_t *pQue, const void *pDat);

QueueOptRes_t Que_OverWrite(Queue_t *pQue, const void *pDat);

QueueOptRes_t Que_Read(Queue_t *pQue, void *pDat);

QueueOptRes_t Que_OnlyRead(Queue_t *pQue, void *pDat);


#endif // QUEUE_H
