
#include "queue.h"



/*!
************************************************************************************************************************
* @brief 队列初始化
* @param[in] Queue_t *pQue：队列数据结构指针
* @param[in] QueSize_t maxSize：队列数据缓存大小
* @param[in] QueSize_t datSize：队列单个数据大小
* @param[in] void *pDatBase：队列数据缓存指针
* @param[out] void
* @returns QueueOptRes_t：队列初始化结果
* @pre 无
* @note 无
* @author Lews Hammond
* @date 2019-9-28
************************************************************************************************************************
*/
QueueOptRes_t Que_Init(Queue_t *pQue, QueSize_t maxSize, QueSize_t datSize, void *pDatBase)
{
    if (pQue == NULL)
    {
        return QUEUE_OPT_PARAM_ERR;
    }
     
    if (pDatBase == NULL)
    {
	return QUEUE_OPT_PARAM_ERR;
    }
    
    if (maxSize == 0U)
    {
	return QUEUE_OPT_PARAM_ERR;
    }

    pQue->Que_DataPtr = pDatBase;
    pQue->Que_FrontIndex = 0U;
    pQue->Que_RearIndex = 0U;
    pQue->Que_UseSize = 0U;
    pQue->Que_SingleSize = datSize;
    pQue->Que_MaxSize = maxSize;

    return QUEUE_OPT_SUCCESS;
}

/*!
************************************************************************************************************************
* @brief 队列写入
* @param[in] Queue_t *pQue：队列数据结构指针
* @param[in] const void *pDat：数据指针
* @param[out] void
* @returns QueueOptRes_t：队列写入结果
* @pre 队列结构经过Que_Init初始化
* @note 无
* @author Lews Hammond
* @date 2019-9-28
************************************************************************************************************************
*/
QueueOptRes_t Que_Write(Queue_t *pQue, const void *pDat)
{
    if ((pQue == NULL)
     || (pDat == NULL))
    {
        return QUEUE_OPT_PARAM_ERR;
    }

    if (pQue->Que_UseSize >= pQue->Que_MaxSize)
    {
        return QUEUE_OPT_IS_FULL;
    }

    (void)memcpy((void *)&pQue->Que_DataPtr[pQue->Que_RearIndex * pQue->Que_SingleSize], pDat, pQue->Que_SingleSize);
    pQue->Que_RearIndex++;
    pQue->Que_UseSize++;
    if (pQue->Que_RearIndex >= pQue->Que_MaxSize)
    {
        pQue->Que_RearIndex = 0U;
    }

    return QUEUE_OPT_SUCCESS;
}

/*!
************************************************************************************************************************
* @brief 队列覆盖写入
* @param[in] Queue_t *pQue：队列数据结构指针
* @param[in] const void *pDat：数据指针
* @param[out] void
* @returns QueueOptRes_t：队列写入结果
* @pre 队列结构经过Que_Init初始化
* @note 无
* @author Lews Hammond
* @date 2019-9-28
************************************************************************************************************************
*/
QueueOptRes_t Que_OverWrite(Queue_t *pQue, const void *pDat)
{
    if ((pQue == NULL)
     || (pDat == NULL))
    {
        return QUEUE_OPT_PARAM_ERR;
    }

    (void)memcpy((void *)&pQue->Que_DataPtr[pQue->Que_RearIndex * pQue->Que_SingleSize], pDat, pQue->Que_SingleSize);
    pQue->Que_RearIndex++;

    if (pQue->Que_RearIndex >= pQue->Que_MaxSize)
    {
        pQue->Que_RearIndex = 0U;
    }

    if (pQue->Que_UseSize < pQue->Que_MaxSize)
    {
        pQue->Que_UseSize++;
    }
    else
    { //Queue is full
        pQue->Que_FrontIndex = pQue->Que_RearIndex;
    }

    return QUEUE_OPT_SUCCESS;
}

/*!
************************************************************************************************************************
* @brief 队列读取出队
* @param[in] Queue_t *pQue：队列数据结构指针
* @param[in] void *pDat：数据指针
* @param[out] void
* @returns QueueOptRes_t：队列操作结果
* @pre 队列结构经过Que_Init初始化
* @note 无
* @author Lews Hammond
* @date 2019-9-28
************************************************************************************************************************
*/
QueueOptRes_t Que_Read(Queue_t *pQue, void *pDat)
{
    if ((pQue == NULL)
     || (pDat == NULL))
    {
        return QUEUE_OPT_PARAM_ERR;
    }

    if (pQue->Que_UseSize == 0U)
    {
        return QUEUE_OPT_IS_EMPTY;
    }

    (void)memcpy(pDat, (void *)&pQue->Que_DataPtr[pQue->Que_FrontIndex * pQue->Que_SingleSize], pQue->Que_SingleSize);
    pQue->Que_FrontIndex++;
    pQue->Que_UseSize--;
    if (pQue->Que_FrontIndex >= pQue->Que_MaxSize)
    {
        pQue->Que_FrontIndex = 0U;
    }

    return QUEUE_OPT_SUCCESS;
}

/*!
************************************************************************************************************************
* @brief 队列读取，不出队
* @param[in] Queue_t *pQue：队列数据结构指针
* @param[in] void *pDat：数据指针
* @param[out] void
* @returns QueueOptRes_t：队列操作结果
* @pre 队列结构经过Que_Init初始化
* @note 无
* @author Lews Hammond
* @date 2019-9-28
************************************************************************************************************************
*/
QueueOptRes_t Que_OnlyRead(Queue_t *pQue, void *pDat)
{
    if ((pQue == NULL)
     || (pDat == NULL))
    {
        return QUEUE_OPT_PARAM_ERR;
    }

    if (pQue->Que_UseSize == 0U)
    {
        return QUEUE_OPT_IS_EMPTY;
    }

    (void)memcpy(pDat, (void *)&pQue->Que_DataPtr[pQue->Que_FrontIndex * pQue->Que_SingleSize], pQue->Que_SingleSize);

    return QUEUE_OPT_SUCCESS;
}

