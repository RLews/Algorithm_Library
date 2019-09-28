
#include "queue.h"
#include <time.h>

typedef struct UDS_DTC_SNAPSHOT_T
{
    uint16_t Dtc_RecordYear;
    uint8_t Dtc_RecordMon;
    uint8_t Dtc_RecordDay;
    uint8_t Dtc_RecordHour;
    uint8_t Dtc_RecordMin;
    uint8_t Dtc_RecordSec;
    uint16_t Dtc_CurPowerVolt;
    uint32_t Dtc_CurVehSpeed;
    uint32_t Dtc_CurEngSpeed;
    uint32_t Dtc_CurVehMile;
}UdsDtcSnapshot_t;

UdsDtcSnapshot_t DtcSnapQue[5] = {0};

uint8_t ActDatBuf[8][8] = {0};

uint32_t ActDatArry[8] = {0};

Queue_t TestQue;

uint8_t QueTestArry1[8] = {1,2,3,4,5,6,7,8};
uint8_t QueTestArry3[8] = {13,23,33,43,53,63,73,83};
uint8_t QueTestArry4[8] = {11,21,31,41,51,61,71,81};

void PrintQueueInfo(Queue_t tQue)
{
    printf("--------------------- Queue Info -------------------------\n");
    printf("the queue front : %d\n", tQue.Que_FrontIndex);
    printf("the queue rear : %d\n", tQue.Que_RearIndex);
    printf("the queue used : %d\n", tQue.Que_UseSize);
    printf("the queue MaxSize : %d\n", tQue.Que_MaxSize);
    printf("the queue SingleSize : %d\n", tQue.Que_SingleSize);
    printf("----------------------------------------------------------\n");
}

void PrintArry(uint8_t dat[], uint32_t len)
{
    uint32_t i = 0;
    printf("Data Array Info\n");
    for (i = 0; i < len; i++)
    {
        printf("The %d Array is : %d\n", i, dat[i]);
    }
}

void PrintSnap(UdsDtcSnapshot_t tSnap[], uint32_t len)
{
    uint32_t i = 0;

    printf("DTC Snapshot Info\n");
    for (i = 0; i < len; i++)
    {
        printf("The %d DTC Snapshot Info\n", i);
        printf("Vehicle miles : %d\n", tSnap[i].Dtc_CurVehMile);
        printf("Vehicle Engine Speed : %d\n", tSnap[i].Dtc_CurEngSpeed);
        printf("Vehicle Power Voltage : %d\n", tSnap[i].Dtc_CurPowerVolt);
        printf("Vehicle Speed : %d\n", tSnap[i].Dtc_CurVehSpeed);
        printf("Vehicle time : %d %d %d %d %d %d \n",
               tSnap[i].Dtc_RecordYear,
               tSnap[i].Dtc_RecordMon,
               tSnap[i].Dtc_RecordDay,
               tSnap[i].Dtc_RecordHour,
               tSnap[i].Dtc_RecordMin,
               tSnap[i].Dtc_RecordSec);
    }



}

int main()
{
    uint32_t i = 0;
/*
    uint32_t readVal = 0;
    uint32_t onlyReadVal = 0;

    Que_Init(&TestQue, 8, sizeof(uint32_t), ActDatArry);

    for (i = 0; i < 10; i++)
    {
        (void)Que_Write(&TestQue, &i);
        PrintQueueInfo(TestQue);
    }

    for (i = 0; i < 20; i++)
    {
        (void)Que_OverWrite(&TestQue, &i);
        PrintQueueInfo(TestQue);
    }

    for (i = 0; i < 9; i++)
    {
        (void)Que_OnlyRead(&TestQue, &onlyReadVal);
        printf("only read value : %d\n", onlyReadVal);
        (void)Que_Read(&TestQue, &readVal);
        printf("read value : %d\n", readVal);
        PrintQueueInfo(TestQue);
    }

    Que_Init(&TestQue, 8, sizeof(uint8_t) * 8, ActDatBuf);
    for (i = 0; i < 10; i++)
    {
        (void)Que_Write(&TestQue, QueTestArry1);
        (void)Que_Write(&TestQue, QueTestArry3);
        (void)Que_Write(&TestQue, QueTestArry4);
        PrintQueueInfo(TestQue);
        PrintArry(ActDatBuf[0], 64);
    }

    for (i = 0; i < 20; i++)
    {
        (void)Que_OverWrite(&TestQue, QueTestArry3);
        PrintQueueInfo(TestQue);
        PrintArry(ActDatBuf[0], 64);
    }

    for (i = 0; i < 9; i++)
    {
        (void)Que_OnlyRead(&TestQue, QueTestArry3);
        (void)Que_Read(&TestQue, QueTestArry4);
        PrintArry(QueTestArry3, 8);
        PrintArry(QueTestArry4, 8);
        PrintQueueInfo(TestQue);
    }
*/
    UdsDtcSnapshot_t testSnap = {0};
    time_t tCurTimes;
    struct tm *pCurTimes;
    uint32_t temp = 0;

    Que_Init(&TestQue, 5, sizeof(UdsDtcSnapshot_t), DtcSnapQue);
    for (i = 0; i < 8; i++)
    {
        tCurTimes = time(NULL);
        pCurTimes = localtime(&tCurTimes);
        testSnap.Dtc_RecordYear = pCurTimes->tm_year;
        testSnap.Dtc_RecordMon = pCurTimes->tm_mon;
        testSnap.Dtc_RecordDay = pCurTimes->tm_mday;
        testSnap.Dtc_RecordHour = pCurTimes->tm_hour;
        testSnap.Dtc_RecordMin = pCurTimes->tm_min;
        testSnap.Dtc_RecordSec = pCurTimes->tm_sec;
        testSnap.Dtc_CurVehMile = i;
        testSnap.Dtc_CurVehSpeed = temp;
        temp++;
        (void)Que_Write(&TestQue, &testSnap);
        PrintQueueInfo(TestQue);
        PrintSnap(DtcSnapQue, 5);
    }

    for (i = 0; i < 13; i++)
    {
        tCurTimes = time(NULL);
        pCurTimes = localtime(&tCurTimes);
        testSnap.Dtc_RecordYear = pCurTimes->tm_year;
        testSnap.Dtc_RecordMon = pCurTimes->tm_mon;
        testSnap.Dtc_RecordDay = pCurTimes->tm_mday;
        testSnap.Dtc_RecordHour = pCurTimes->tm_hour;
        testSnap.Dtc_RecordMin = pCurTimes->tm_min;
        testSnap.Dtc_RecordSec = pCurTimes->tm_sec;
        testSnap.Dtc_CurVehMile = i;
        testSnap.Dtc_CurEngSpeed = temp;
        temp++;
        (void)Que_OverWrite(&TestQue, &testSnap);
        PrintQueueInfo(TestQue);

        PrintSnap(DtcSnapQue, 5);
    }

    for (i = 0; i < 7; i++)
    {
        (void)Que_OnlyRead(&TestQue, &testSnap);
        PrintSnap(&testSnap, 1);
        (void)Que_Read(&TestQue, &testSnap);
        PrintQueueInfo(TestQue);
        PrintSnap(&testSnap, 1);
        PrintSnap(DtcSnapQue, 5);
    }

    return 0;
}
