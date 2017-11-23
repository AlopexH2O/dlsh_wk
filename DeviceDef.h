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
	uint8 voltagelevel;//电压等级，0-不处理，1-35kV，2-66kV
}LOADINFO;

//deviceinfo
typedef struct {

	//in
	InputItem Sys_P[SYS_P_NUM];
	InputItem Load_P[LOAD_P_NUM];
	InputItem Load_Prior[LOAD_P_NUM + 1];
	InputItem Load_Conn[LOAD_CONN_NUM];
	InputItem Sys_Stat[SYS_STAT_NUM];
	
	//各个厂站的负荷拓扑信息 -- 单独需要从各个站获取的信息
	InputItem Load_Conn_KGZ[LINE_NUM_KGZ];
	InputItem Load_Conn_EKY[LINE_NUM_EKY];
	InputItem Load_Conn_CH3[LINE_NUM_CH3];
	InputItem Load_Conn_CH4[LINE_NUM_CH4];
	InputItem Load_Conn_SHZ[LINE_NUM_SHZ];

	//out
	OutputItem LoadOutput[LOAD_P_NUM + 4];//增加输出化机双线、化总双线的切除情况
	TacOutput  tac;
	//sys
	LOADINFO load[LOAD_P_NUM+4];//load element,增加化机双线和华总双线的负荷情况 
	float p_qq_setting;//频率欠切控制定值

	float p_all_kq;//所有负荷可切功率
	float p_40_kq;//优先级1-40可切功率
	float p_all_kq_s1;//系统1所有负荷可切功率
	float p_40_kq_s1;//系统1优先级1-40可切功率
	float p_all_kq_s2;//系统2所有负荷可切功率
	float p_40_kq_s2;//系统2优先级1-40可切功率
	float p_kq_s1_66;//系统1中66kV可切负荷功率
	float p_40_kq_s1_66;//系统1中优先级1-40的可切66kV负荷
	float p_kq_s2_66;//系统2中66kV可切负荷功率
	float p_40_kq_s2_66;//系统2中优先级1-40的可切66kV负荷


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
	//事故跳闸
	uint8 T9511;//1#变高跳闸
	uint8 T9512;//2#变高跳闸
	uint8 T9561;//1#变低跳闸
	uint8 T9562;//2#变低跳闸
	uint8 T9572;//66kV母联跳闸
	uint8 T9591;//出线1跳闸
	uint8 T9592;//出线2跳闸

	//频率降低控制
	uint8 FT_KGZ_S1;//开关站系统1频率下降
	uint8 FT_KGZ_S2;//开关站系统2频率下降
	uint8 FT_EKY_S1;//二空压系统1频率下降
	uint8 FT_EKY_S2;//二空压系统2频率下降
	uint8 FT_CH3_S1;//三催化系统1频率下降
	uint8 FT_CH3_S2;//三催化系统2频率下降
	uint8 FT_CH4_S1;//四催化系统1频率下降
	uint8 FT_CH4_S2;//四催化系统2频率下降
}FAULTINFO;

#endif
