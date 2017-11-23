#ifndef DEVLOGIC_H
#define DEVLOGIC_H

#include "DeviceSet.h"
#include "DeviceDef.h"


//��ʼ������
void Initialize(DEVINFO* dev, FAULTINFO* fault);

//��ȡװ����Ϣ
void ReadDevInfo(DEVINFO* dev, FAULTINFO* fault);

//�����ɹ���ϵͳ
void HandleLoadSys(DEVINFO* dev);

//�������ȼ�ͳ�Ƹ��ɹ���
void CalLoadStatics(DEVINFO* dev);

////����г���־
void ClearCuttedTag(DEVINFO* dev);

//����Ҫ���γɸ������ȼ���Ϣ
void CalLoadInfoByPrior(DEVINFO* dev, uint8 sys, uint8 vl);

//�����������������������ȼ��г���Ϣ
//	xql:������
//  p_all_kq:ȫϵͳ������
//  p_40_kq: ȫϵͳǰ40���ȼ�������
//  p_prior: �����ȼ����и���
//  cutted:  �����ȼ��г���־
//  size  :  ���ȼ�����
//  qql_set: �������Ƿ����
void LoadCuttedByPxql(float xql, float p_all_kq, float p_40_kq, float* p_prior, bool* cutted, int size, float qql_set);


//  ���¸����г���Ϣ
//	dev:װ�ýṹ���ַ
//  no_sys: 1-ϵͳ1  2-ϵͳ2   3-ȫ��
void UpdateCuttedInfo(DEVINFO* dev, uint8 no_sys, uint8 vl);

//��������г���Ϣ
void ExportLoadOutput(DEVINFO* dev);

//�����г�����˫�ߣ�����˫��
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


//��ʼ������
void InitializeFault(FAULTINFO* fault);
//���ù���
void SetFault(FAULTINFO* fault, uint32 ft);

//���ݹ���Ƶ���½�ͳ�ƿ��и�����Ϣ
void SetSysFault(DEVINFO* dev, FAULTINFO* fault);

//���ݹ���Ƶ�ʽ��ͼ�����й���
void CalPKqFault(DEVINFO*dev, FAULTINFO* fault, uint8 sys, uint8 vl);

#endif