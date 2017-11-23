#ifndef DEVLOGIC_H
#define DEVLOGIC_H

#include "DeviceSet.h"
#include "DeviceDef.h"


//初始化函数
void Initialize(DEVINFO* dev, FAULTINFO* fault);

//读取装置信息
void ReadDevInfo(DEVINFO* dev, FAULTINFO* fault);

//处理负荷挂载系统
void HandleLoadSys(DEVINFO* dev);

//根据优先级统计负荷功率
void CalLoadStatics(DEVINFO* dev);

////清除切除标志
void ClearCuttedTag(DEVINFO* dev);

//根据要求形成负荷优先级信息
void CalLoadInfoByPrior(DEVINFO* dev, uint8 sys, uint8 vl);

//根据需切量负荷量计算优先级切除信息
//	xql:需切量
//  p_all_kq:全系统可切量
//  p_40_kq: 全系统前40优先级可切量
//  p_prior: 各优先级可切负荷
//  cutted:  各优先级切除标志
//  size  :  优先级个数
//  qql_set: 允许最大欠切量
void LoadCuttedByPxql(float xql, float p_all_kq, float p_40_kq, float* p_prior, bool* cutted, int size, float qql_set);


//  更新负荷切除信息
//	dev:装置结构体地址
//  no_sys: 1-系统1  2-系统2   3-全网
void UpdateCuttedInfo(DEVINFO* dev, uint8 no_sys, uint8 vl);

//输出负荷切除信息
void ExportLoadOutput(DEVINFO* dev);

//首先切除化机双线，华总双线
float CutHJZXFirst(DEVINFO* dev, uint8 sys);

//tac_no 1
int RUN_TAC_NO1(DEVINFO* dev);
int RUN_TAC_NO1_FAULT(DEVINFO* dev, FAULTINFO* fault);

//tac_no 2
int RUN_TAC_NO2(DEVINFO* dev);
int RUN_TAC_NO2_FAULT(DEVINFO* dev, FAULTINFO* fault);

//tac_no 3
int RUN_TAC_NO3(DEVINFO* dev);
int RUN_TAC_NO3_FAULT(DEVINFO* dev, FAULTINFO* fault);

//tac_no 4
int RUN_TAC_NO4(DEVINFO* dev);
int RUN_TAC_NO4_FAULT(DEVINFO* dev, FAULTINFO* fault);

//tac_no 5
int RUN_TAC_NO5(DEVINFO* dev);
int RUN_TAC_NO5_FAULT(DEVINFO* dev, FAULTINFO* fault);

//tac_no 6
int RUN_TAC_NO6(DEVINFO* dev);
int RUN_TAC_NO6_FAULT(DEVINFO* dev, FAULTINFO* fault);

//tac_no 7
int RUN_TAC_NO7(DEVINFO* dev);
int RUN_TAC_NO7_FAULT(DEVINFO* dev, FAULTINFO* fault);

//tac_no 8
int RUN_TAC_NO8(DEVINFO* dev);
int RUN_TAC_NO8_FAULT(DEVINFO* dev, FAULTINFO* fault);


//初始化故障
void InitializeFault(FAULTINFO* fault);
//设置故障
void SetFault(FAULTINFO* fault, uint32 ft);

//根据故障频率下降统计可切负荷信息
void SetSysFault(DEVINFO* dev, FAULTINFO* fault);

//根据故障频率降低计算可切功率
void CalPKqFault(DEVINFO*dev, FAULTINFO* fault, uint8 sys, uint8 vl);

#endif