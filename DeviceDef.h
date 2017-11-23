#ifndef DEVICE_DEF_H
#define DEVICE_DEF_H 

//outside common header file
#include "simulator_define.h"
#include "systac.h"
#include "DeviceSet.h"

typedef unsigned int  uint32;

//loadinfo struct
typedef struct {
	uint8 fun;
	uint8 inf;
	float pload;//load p info
	uint8 prior;//load prior setting 
	uint8 onWhichSys;//load sys connection
	bool  beCutted;//load whether be cutted--result
	bool  alive;
	uint8 voltagelevel;//��ѹ�ȼ���0-������1-35kV��2-66kV
}LOADINFO;

//deviceinfo
typedef struct {

	//in
	InputItem Sys_P[SYS_P_NUM];
	InputItem Load_P[LOAD_P_NUM];
	InputItem Load_Prior[LOAD_P_NUM + 1];
	InputItem Load_Conn[LOAD_CONN_NUM];
	InputItem Sys_Stat[SYS_STAT_NUM];
	
	//������վ�ĸ���������Ϣ -- ������Ҫ�Ӹ���վ��ȡ����Ϣ
	InputItem Load_Conn_KGZ[LINE_NUM_KGZ];
	InputItem Load_Conn_EKY[LINE_NUM_EKY];
	InputItem Load_Conn_CH3[LINE_NUM_CH3];
	InputItem Load_Conn_CH4[LINE_NUM_CH4];
	InputItem Load_Conn_SHZ[LINE_NUM_SHZ];

	//out
	OutputItem LoadOutput[LOAD_P_NUM + 4];//�����������˫�ߡ�����˫�ߵ��г����
	TacOutput  tac;
	//sys
	LOADINFO load[LOAD_P_NUM+4];//load element,���ӻ���˫�ߺͻ���˫�ߵĸ������ 
	float p_qq_setting;//Ƶ��Ƿ�п��ƶ�ֵ

	float p_all_kq;//���и��ɿ��й���
	float p_40_kq;//���ȼ�1-40���й���
	float p_all_kq_s1;//ϵͳ1���и��ɿ��й���
	float p_40_kq_s1;//ϵͳ1���ȼ�1-40���й���
	float p_all_kq_s2;//ϵͳ2���и��ɿ��й���
	float p_40_kq_s2;//ϵͳ2���ȼ�1-40���й���
	float p_kq_s1_66;//ϵͳ1��66kV���и��ɹ���
	float p_40_kq_s1_66;//ϵͳ1�����ȼ�1-40�Ŀ���66kV����
	float p_kq_s2_66;//ϵͳ2��66kV���и��ɹ���
	float p_40_kq_s2_66;//ϵͳ2�����ȼ�1-40�Ŀ���66kV����


	float p_prior[MAX_PRIOR];
	bool  cutted_prior[MAX_PRIOR];

	//line power
	float P9591;
	float P9561;
	float P9592;
	float P9562;
	float P9572;
	float P_HJX_1;
	float P_HJX_2;
	float P_HZX_1;
	float P_HZX_2;

	//KR state
	uint8 Conn_S1;
	uint8 Conn_S2;
	uint8 Conn_S1S2;
	uint8 HWJ9511;
	uint8 HWJ9512;
	uint8 HWJ9561;
	uint8 HWJ9562;
	uint8 HWJ9591;
	uint8 HWJ9592;
	uint8 HWJ9571;
	uint8 HWJ9572;
	uint8 HWJ9573;
	uint8 S1_35kV_B1;
	uint8 S2_35kV_B1;
	uint8 S1_35kV_B2;
	uint8 S2_35kV_B2;
}DEVINFO;

//faultinfo

typedef struct {
	//�¹���բ
	uint8 T9511;//1#�����բ
	uint8 T9512;//2#�����բ
	uint8 T9561;//1#�����բ
	uint8 T9562;//2#�����բ
	uint8 T9572;//66kVĸ����բ
	uint8 T9591;//����1��բ
	uint8 T9592;//����2��բ

	//Ƶ�ʽ��Ϳ���
	uint8 FT_KGZ_S1;//����վϵͳ1Ƶ���½�
	uint8 FT_KGZ_S2;//����վϵͳ2Ƶ���½�
	uint8 FT_EKY_S1;//����ѹϵͳ1Ƶ���½�
	uint8 FT_EKY_S2;//����ѹϵͳ2Ƶ���½�
	uint8 FT_CH3_S1;//���߻�ϵͳ1Ƶ���½�
	uint8 FT_CH3_S2;//���߻�ϵͳ2Ƶ���½�
	uint8 FT_CH4_S1;//�Ĵ߻�ϵͳ1Ƶ���½�
	uint8 FT_CH4_S2;//�Ĵ߻�ϵͳ2Ƶ���½�
}FAULTINFO;

#endif
