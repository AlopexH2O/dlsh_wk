#ifndef DEVICE_DEF_H
#define DEVICE_DEF_H 

//outside common header file
#include "simulator_define.h"
#include "systac.h"
#include "DeviceSet.h"

typedef unsigned int  int32;


//loadinfo struct
typedef struct {
	uint8 fun;
	uint8 inf;
	float pload;//load p info
	uint8 prior;//load prior setting 
	uint8 onWhichSys;//load sys connection
	bool  beCutted;//load whether be cutted--result
	bool  alive;
}LOADINFO;

//deviceinfo
typedef struct {

	//in
	InputItem Sys_P[SYS_P_NUM];
	InputItem Load_P[LOAD_P_NUM];
	InputItem Load_Prior[LOAD_P_NUM + 1];
	InputItem Load_Conn[LOAD_CONN_NUM];
	InputItem Sys_Stat[SYS_STAT_NUM];

	//out
	OutputItem LoadOutput[LOAD_P_NUM];
	TacOutput  tac;
	//sys
	LOADINFO load[LOAD_P_NUM];//load element 
	float p_qq_setting;//Ƶ��Ƿ�п��ƶ�ֵ
	float p_all_kq;//���и��ɿ��й���
	float p_40_kq;//���ȼ�1-40���й���
	float p_all_kq_s1;//ϵͳ1���и��ɿ��й���
	float p_40_kq_s1;//ϵͳ1���ȼ�1-40���й���
	float p_all_kq_s2;//ϵͳ2���и��ɿ��й���
	float p_40_kq_s2;//ϵͳ2���ȼ�1-40���й���

	float p_prior_s1[MAX_PRIOR];
	float p_prior_s2[MAX_PRIOR];
	float p_prior_s1s2[MAX_PRIOR];
	bool  cutted_prior[MAX_PRIOR];

	//line power
	float P9591;
	float P9561;
	float P9592;
	float P9562;
	float P9572;
	float P_HJX_1;
	float P_HJX_2;
	float P_HSX;
	float P_HZX;

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

}DEVINFO;



#endif
