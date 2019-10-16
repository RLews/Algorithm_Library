
#include "queue.h"



/*!
************************************************************************************************************************
* @brief ���г�ʼ��
* @param[in] Queue_t *pQue���������ݽṹָ��
* @param[in] QueSize_t maxSize���������ݻ����С
* @param[in] QueSize_t datSize�����е������ݴ�С
* @param[in] void *pDatBase���������ݻ���ָ��
* @param[out] void
* @returns QueueOptRes_t�����г�ʼ�����
* @pre ��
* @note ��
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
* @brief ����д��
* @param[in] Queue_t *pQue���������ݽṹָ��
* @param[in] const void *pDat������ָ��
* @param[out] void
* @returns QueueOptRes_t������д����
* @pre ���нṹ����Que_Init��ʼ��
* @note ��
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
* @brief ���и���д��
* @param[in] Queue_t *pQue���������ݽṹָ��
* @param[in] const void *pDat������ָ��
* @param[out] void
* @returns QueueOptRes_t������д����
* @pre ���нṹ����Que_Init��ʼ��
* @note ��
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
* @brief ���ж�ȡ����
* @param[in] Queue_t *pQue���������ݽṹָ��
* @param[in] void *pDat������ָ��
* @param[out] void
* @returns QueueOptRes_t�����в������
* @pre ���нṹ����Que_Init��ʼ��
* @note ��
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
* @brief ���ж�ȡ��������
* @param[in] Queue_t *pQue���������ݽṹָ��
* @param[in] void *pDat������ָ��
* @param[out] void
* @returns QueueOptRes_t�����в������
* @pre ���нṹ����Que_Init��ʼ��
* @note ��
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

