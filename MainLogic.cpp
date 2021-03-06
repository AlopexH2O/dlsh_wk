#include <string.h>
#include "systac.h"
//#include "DeviceSet.h"
//#include "DeviceDef.h"
#include "DevLogic.h"

#include <iostream>
#include <stdio.h>

#ifdef _DEBUG
#include "TestCase.h"
#include <fstream>
#endif

using namespace std;


//定义全局变量
static DEVINFO       devdata;	
static FAULTINFO	 faultdata;
static DATA_HANDLER  func_read;
static void*         env_read;
static TAC_HANDLER   func_send;
static void*         env_send;

//输入回调函数
void data_register(DATA_HANDLER data_handler,void *env){
	func_read = data_handler;
	env_read = env;
#ifdef _LOG
	printf("Log[func data_register]: data_handle = %x, env = %x\n", func_read, env_read);
#endif
	return;
}
//输出回调函数
void result_register(TAC_HANDLER tac_handler,void *env){
	func_send = tac_handler;
	env_send = env;
#ifdef _LOG
	printf("Log[func result_register]: tac_handle = %x, env = %x\n", func_send, env_send);
#endif
	return;
}

void LogFuncReadInfo(InputItem *input,uint8 data_num){
	cout << "Log[func LogFuncReadInfo]:" << endl;
	for (int i = 0;i < data_num;i++){
		cout << "fun_num = " << int(input[i].fun_num)  << " inf_num = " << int(input[i].inf_num) << " value = " << input[i].value << endl;
	}
	return;
}
void LogFuncSendInfo(TacOutput *output){
	cout << "Log[func LogFuncSendInfo]:" << endl;
	cout << "tac_num = " << output->tac_num << endl
	     << "tac_yq  = " << output->tac_yq << endl
	     << "tac_kq  = " << output->tac_kq << endl
		 << "tac_sq  = " << output->tac_sq << endl;
	for (int j = 0;j < output->data_num;j++){
		cout << "fun_num = " << int(output->data[j].fun_num) <<  " inf_num = " << int(output->data[j].inf_num) << "\t cutted = " << int(output->data[j].cutted) << endl;
	}
	return;
}
void LogFuncSysdata(DEVINFO* dev){
	printf("Log[Func LogFuncSysdata]:\n");
	printf("Sys_P:\n");
	LogFuncReadInfo(dev->Sys_P, SYS_P_NUM);
	
	printf("Load_P:\n");
	LogFuncReadInfo(dev->Load_P, LOAD_P_NUM);
	
	printf("Load_Prior:\n");
	LogFuncReadInfo(dev->Load_Prior, LOAD_P_NUM+1);

	printf("Load_Conn:\n");
	LogFuncReadInfo(dev->Load_Conn, LOAD_CONN_NUM);

	printf("Sys_Stat:\n");
	LogFuncReadInfo(dev->Sys_Stat, SYS_STAT_NUM);

	printf("Load_Conn_KGZ:\n");
	LogFuncReadInfo(dev->Load_Conn_KGZ, LINE_NUM_KGZ);

	printf("Load_Conn_EKY:\n");
	LogFuncReadInfo(dev->Load_Conn_EKY, LINE_NUM_EKY);

	printf("Load_Conn_CH3:\n");
	LogFuncReadInfo(dev->Load_Conn_CH3, LINE_NUM_CH3);

	printf("Load_Conn_CH4:\n");
	LogFuncReadInfo(dev->Load_Conn_CH4, LINE_NUM_CH4);

	printf("Load_Conn_SHZ:\n");
	LogFuncReadInfo(dev->Load_Conn_SHZ, LINE_NUM_SHZ);

	printf("负荷信息:\n");
	for (int i = 0;i < LOAD_P_NUM+4;i++){
		printf("no = %d, fun = %d,inf = %d, pload = %f, prior = %d, sys = %d, alive = %d, vl = %d\n",
			   i, dev->load[i].fun, dev->load[i].inf, dev->load[i].pload, dev->load[i].prior, dev->load[i].onWhichSys,
			   dev->load[i].alive, dev->load[i].voltagelevel);
	}
	printf("频率欠切控制定值 = %f\n", dev->p_qq_setting);

	return;
}

//初始化
void Initialize(DEVINFO* dev, FAULTINFO* fault){
	//系统模拟量
	for (int i = 0; i < SYS_P_NUM; ++i){
		dev->Sys_P[i].fun_num = FUN_SYS_P[i];
		dev->Sys_P[i].inf_num = INF_SYS_P[i];
		dev->Sys_P[i].value = 0;
	}
	//负荷数据
	for (int i = 0; i < LOAD_P_NUM; ++i){
		dev->Load_P[i].fun_num = FUN_LOAD_P[i];
		dev->Load_P[i].inf_num = INF_LOAD_P[i];
		dev->Load_Prior[i].fun_num = FUN_LOAD_PRIOR[i];
		dev->Load_Prior[i].inf_num = INF_LOAD_PRIOR[i];
		dev->Load_P[i].value = 0;
		dev->Load_Prior[i].value = 0;
	}
	dev->Load_Prior[LOAD_P_NUM].fun_num = FUN_LOAD_PRIOR[LOAD_P_NUM];
	dev->Load_Prior[LOAD_P_NUM].inf_num = INF_LOAD_PRIOR[LOAD_P_NUM];
	dev->Load_Prior[LOAD_P_NUM].value = 0;

	//系统连接状态字
	for (int i = 0; i < LOAD_CONN_NUM; ++i){
		dev->Load_Conn[i].fun_num = FUN_LOAD_CONN[i];
		dev->Load_Conn[i].inf_num = INF_LOAD_CONN[i];
		dev->Load_Conn[i].value = 0;
	}
	//系统开入状态
	for (int i = 0; i < SYS_STAT_NUM; ++i){
		dev->Sys_Stat[i].fun_num = FUN_SYS_STAT[i];
		dev->Sys_Stat[i].inf_num = INF_SYS_STAT[i];
		dev->Sys_Stat[i].value = 0;
	}

	//开关站信息
	for (int i = 0;i < LINE_NUM_KGZ;++i){
		dev->Load_Conn_KGZ[i].fun_num = FUN_KGZ_LOAD[i];
		dev->Load_Conn_KGZ[i].inf_num = INF_KGZ_LOAD[i];
		dev->Load_Conn_KGZ[i].value = 0;
	}

	//二空压信息
	for (int i = 0;i < LINE_NUM_EKY;++i){
		dev->Load_Conn_EKY[i].fun_num = FUN_EKY_LOAD[i];
		dev->Load_Conn_EKY[i].inf_num = INF_EKY_LOAD[i];
		dev->Load_Conn_EKY[i].value = 0;
	}

	//三催化信息
	for (int i = 0;i < LINE_NUM_CH3;++i){
		dev->Load_Conn_CH3[i].fun_num = FUN_CH3_LOAD[i];
		dev->Load_Conn_CH3[i].inf_num = INF_CH3_LOAD[i];
		dev->Load_Conn_CH3[i].value = 0;
	}
	//四催化信息
	for (int i = 0;i < LINE_NUM_CH4;++i){
		dev->Load_Conn_CH4[i].fun_num = FUN_CH4_LOAD[i];
		dev->Load_Conn_CH4[i].inf_num = INF_CH4_LOAD[i];
		dev->Load_Conn_CH4[i].value = 0;
	}

	//石化子站信息
	for (int i = 0;i < LINE_NUM_SHZ;++i){
		dev->Load_Conn_SHZ[i].fun_num = FUN_SHZ_LOAD[i];
		dev->Load_Conn_SHZ[i].inf_num = INF_SHZ_LOAD[i];
		dev->Load_Conn_SHZ[i].value = 0;
	}

	dev->P9591   = 0.0;
	dev->P9561   = 0.0;
	dev->P9592   = 0.0;
	dev->P9562   = 0.0;
	dev->P9572   = 0.0;
	dev->P_HJX_1 = 0.0;
	dev->P_HJX_2 = 0.0;
	dev->P_HZX_1   = 0.0;
	dev->P_HZX_2   = 0.0;

	dev->Conn_S1  = 0;
	dev->Conn_S2  = 0;
	dev->Conn_S1S2= 0;
	dev->HWJ9511  = 0;
	dev->HWJ9512  = 0;
	dev->HWJ9561  = 0;
	dev->HWJ9562  = 0;
	dev->HWJ9591  = 0;
	dev->HWJ9592  = 0;
	dev->HWJ9571  = 0;
	dev->HWJ9572  = 0;
	dev->HWJ9573  = 0;
	dev->S1_35kV_B1 = 0;
	dev->S2_35kV_B1 = 0;
	dev->S1_35kV_B2 = 0;
	dev->S2_35kV_B2 = 0;

	dev->p_qq_setting = 0.0;
	dev->p_all_kq = 0.0;
	dev->p_40_kq = 0.0;
	dev->p_all_kq_s1 = 0.0;
	dev->p_40_kq_s1 = 0.0;
	dev->p_all_kq_s2 = 0.0;
	dev->p_40_kq_s2 = 0.0;
	dev->p_kq_s1_66 = 0.0;
	dev->p_40_kq_s1_66 = 0.0;
	dev->p_kq_s2_66 = 0.0;
	dev->p_40_kq_s2_66 = 0.0;
	for (int i = 0; i < MAX_PRIOR; ++i){
		dev->p_prior[i] = 0.0;
		dev->cutted_prior[i] = false;
	}
	for (int i = 0;i < LOAD_P_NUM;++i){
		dev->load[i].fun = 0;
		dev->load[i].inf = 0;
		dev->load[i].pload = 0.0;
		dev->load[i].prior = 0;
		dev->load[i].onWhichSys = 0;
		dev->load[i].voltagelevel = 0;
		dev->load[i].alive = false;
		dev->load[i].beCutted = false;
	}

	//初始化故障信息
	InitializeFault(fault);
	//初始化策略输出结果
	//InitializeTacOutput(dev);
	return;
}
//读取装置信息
void ReadDevInfo(DEVINFO* dev, FAULTINFO* fault){

#ifndef _DEBUG
	//读取系统模拟量信息
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Sys_p stcode = %s, InputItem = %x, data_num = %d\n", SHZZ, dev->Sys_P, SYS_P_NUM);
	LogFuncReadInfo(dev->Sys_P, SYS_P_NUM);
#endif
	func_read(SHZZ,dev->Sys_P, SYS_P_NUM, env_read);

	//读取负荷信息
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_P stcode = %s, InputItem = %x, data_num = %d\n", SHZZ, dev->Load_P, LOAD_P_NUM);
	LogFuncReadInfo(dev->Load_P, LOAD_P_NUM);
#endif
	func_read(SHZZ,dev->Load_P, LOAD_P_NUM, env_read);


	//读取优先级定值
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_Prior stcode = %s, InputItem = %x, data_num = %d\n", SHZZ, dev->Load_Prior, LOAD_P_NUM+1);
	LogFuncReadInfo(dev->Load_Prior, LOAD_P_NUM+1);
#endif
	func_read(SHZZ,dev->Load_Prior, LOAD_P_NUM+1, env_read);


	//读取系统连接状态
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_Conn stcode = %s, InputItem = %x, data_num = %d\n", SHZZ, dev->Load_Conn, LOAD_CONN_NUM);
	LogFuncReadInfo(dev->Load_Conn, LOAD_CONN_NUM);
#endif
	func_read(SHZZ,dev->Load_Conn, LOAD_CONN_NUM, env_read);

	//读取系统开关运行状态
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Sys_Stat before stcode = %s, InputItem = %x, data_num = %d\n", SHZZ, dev->Sys_Stat, SYS_STAT_NUM);
	LogFuncReadInfo(dev->Sys_Stat, SYS_STAT_NUM);
#endif
	func_read(SHZZ,dev->Sys_Stat, SYS_STAT_NUM, env_read);
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Sys_Stat after stcode = %s, InputItem = %x, data_num = %d\n", SHZZ, dev->Sys_Stat, SYS_STAT_NUM);
	LogFuncReadInfo(dev->Sys_Stat, SYS_STAT_NUM);
#endif



	//开关站读取信息
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_Conn_KGZ stcode = %s, InputItem = %x, data_num = %d\n", KGZ, dev->Load_Conn_KGZ, LINE_NUM_KGZ);
	LogFuncReadInfo(dev->Load_Conn_KGZ, LINE_NUM_KGZ);
#endif
	func_read(KGZ,dev->Load_Conn_KGZ, LINE_NUM_KGZ, env_read);


	//二空压读取信息
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_Conn_EKY stcode = %s, InputItem = %x, data_num = %d\n", EKY, dev->Load_Conn_EKY, LINE_NUM_EKY);
	LogFuncReadInfo(dev->Load_Conn_EKY, LINE_NUM_EKY);
#endif
	func_read(EKY,dev->Load_Conn_EKY, LINE_NUM_EKY, env_read);

	//三催化读取信息
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_Conn_CH3 stcode = %s, InputItem = %x, data_num = %d\n", CH3, dev->Load_Conn_CH3, LINE_NUM_CH3);
	LogFuncReadInfo(dev->Load_Conn_CH3, LINE_NUM_CH3);
#endif
	func_read(CH3,dev->Load_Conn_CH3, LINE_NUM_CH3, env_read);

	//四催化读取信息
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_Conn_CH4 stcode = %s, InputItem = %x, data_num = %d\n", CH4, dev->Load_Conn_CH4, LINE_NUM_CH4);
	LogFuncReadInfo(dev->Load_Conn_CH4, LINE_NUM_CH4);
#endif
	func_read(CH4,dev->Load_Conn_CH4, LINE_NUM_CH4, env_read);

	//石化子读取信息
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_Conn_SHZ stcode = %s, InputItem = %x, data_num = %d\n", SHZ, dev->Load_Conn_SHZ, LINE_NUM_SHZ);
	LogFuncReadInfo(dev->Load_Conn_SHZ, LINE_NUM_SHZ);
#endif
	func_read(SHZ,dev->Load_Conn_SHZ, LINE_NUM_SHZ, env_read);

	//故障信息接口备用

#else
	//从文件中读取系统状态
//	bool res = ReadTestCaseFile(std::string("C:\\Users\\zhengh.NR-RD\\Desktop\\大连石化项目\\XDC.sta"), std::string("C:\\Users\\zhengh.NR-RD\\Desktop\\大连石化项目\\XDC.set"), dev, fault);
	bool res = ReadTestCaseFile(std::string("./tmp/XDC.sta"), std::string("./tmp/XDC.set"), dev, fault);
	if (!res){
		std::cout << "Error: Failed to ReadTestCaseFile!" << endl;
		exit(0);
	}
#endif

	//功率数据预处理
	dev->P9591 = dev->Sys_P[0].value;
	dev->P9561 = dev->Sys_P[1].value;
	dev->P9592 = dev->Sys_P[2].value;
	dev->P9562 = dev->Sys_P[3].value;
	dev->P9572 = dev->Sys_P[4].value;
	dev->P_HJX_1 = dev->Sys_P[5].value;
	dev->P_HJX_2 = dev->Sys_P[6].value;
	dev->P_HZX_1 = dev->Sys_P[8].value;
	dev->P_HZX_2 = dev->Sys_P[7].value;
	//系统开入状态预处理
	dev->Conn_S1 = uint8(dev->Sys_Stat[0].value);
	dev->Conn_S2 = uint8(dev->Sys_Stat[1].value);
	dev->Conn_S1S2 = uint8(dev->Sys_Stat[2].value);
	dev->HWJ9511 = uint8(dev->Sys_Stat[3].value);
	dev->HWJ9512 = uint8(dev->Sys_Stat[4].value);
	dev->HWJ9561 = uint8(dev->Sys_Stat[5].value);
	dev->HWJ9562 = uint8(dev->Sys_Stat[6].value);
	dev->HWJ9591 = uint8(dev->Sys_Stat[7].value);
	dev->HWJ9592 = uint8(dev->Sys_Stat[8].value);
	dev->HWJ9572 = uint8(dev->Sys_Stat[9].value);
	dev->HWJ9573 = uint8(dev->Sys_Stat[10].value);
	dev->S1_35kV_B1 = uint8(dev->Sys_Stat[11].value);
	dev->S2_35kV_B1 = uint8(dev->Sys_Stat[12].value);
	dev->S1_35kV_B2 = uint8(dev->Sys_Stat[13].value);
	dev->S2_35kV_B2 = uint8(dev->Sys_Stat[14].value);

	//9571开关信息
	dev->HWJ9571 = uint8(dev->Load_Conn_SHZ[0].value);

	//负荷数据处理
	dev->p_qq_setting = dev->Load_Prior[LOAD_P_NUM].value;//频稳欠切功率定值
	//负荷信息
	for (int i = 0; i < LOAD_P_NUM; ++i){
		dev->load[i].fun = dev->Load_P[i].fun_num;
		dev->load[i].inf = dev->Load_P[i].inf_num;
		dev->load[i].pload = dev->Load_P[i].value;
		dev->load[i].prior = uint8(dev->Load_Prior[i].value);
		dev->load[i].onWhichSys = 0;
		dev->load[i].voltagelevel = 0;
		dev->load[i].beCutted = false;
		dev->load[i].pload < LOAD_ALIVE_P ? dev->load[i].alive = false : dev->load[i].alive = true;
	}
	//化机一线
	dev->load[LOAD_P_NUM + 0].fun = dev->Sys_P[5].fun_num;
	dev->load[LOAD_P_NUM + 0].inf = dev->Sys_P[5].inf_num;
	dev->load[LOAD_P_NUM + 0].pload = dev->Sys_P[5].value;
	dev->load[LOAD_P_NUM + 0].prior = 0;
	dev->load[LOAD_P_NUM + 0].onWhichSys = 1;
	dev->load[LOAD_P_NUM + 0].voltagelevel = 2;
	dev->load[LOAD_P_NUM + 0].beCutted = false;
	dev->load[LOAD_P_NUM + 0].pload < LOAD_ALIVE_P ? dev->load[LOAD_P_NUM + 0].alive = false : dev->load[LOAD_P_NUM + 0].alive = true;
	//化机二线
	dev->load[LOAD_P_NUM + 1].fun = dev->Sys_P[6].fun_num;
	dev->load[LOAD_P_NUM + 1].inf = dev->Sys_P[6].inf_num;
	dev->load[LOAD_P_NUM + 1].pload = dev->Sys_P[6].value;
	dev->load[LOAD_P_NUM + 1].prior = 0;
	dev->load[LOAD_P_NUM + 1].onWhichSys = 2;
	dev->load[LOAD_P_NUM + 1].voltagelevel = 2;
	dev->load[LOAD_P_NUM + 1].beCutted = false;
	dev->load[LOAD_P_NUM + 1].pload < LOAD_ALIVE_P ? dev->load[LOAD_P_NUM + 1].alive = false : dev->load[LOAD_P_NUM + 1].alive = true;

	//化总一线
	dev->load[LOAD_P_NUM + 2].fun = dev->Sys_P[7].fun_num;
	dev->load[LOAD_P_NUM + 2].inf = dev->Sys_P[7].inf_num;
	dev->load[LOAD_P_NUM + 2].pload = dev->Sys_P[7].value;
	dev->load[LOAD_P_NUM + 2].prior = 0;
	dev->load[LOAD_P_NUM + 2].onWhichSys = 1;
	dev->load[LOAD_P_NUM + 2].voltagelevel = 2;
	dev->load[LOAD_P_NUM + 2].beCutted = false;
	dev->load[LOAD_P_NUM + 2].pload < LOAD_ALIVE_P ? dev->load[LOAD_P_NUM + 2].alive = false : dev->load[LOAD_P_NUM + 2].alive = true;

	//化总二线
	dev->load[LOAD_P_NUM + 3].fun = dev->Sys_P[8].fun_num;
	dev->load[LOAD_P_NUM + 3].inf = dev->Sys_P[8].inf_num;
	dev->load[LOAD_P_NUM + 3].pload = dev->Sys_P[8].value;
	dev->load[LOAD_P_NUM + 3].prior = 0;
	dev->load[LOAD_P_NUM + 3].onWhichSys = 2;
	dev->load[LOAD_P_NUM + 3].voltagelevel = 2;
	dev->load[LOAD_P_NUM + 3].beCutted = false;
	dev->load[LOAD_P_NUM + 3].pload < LOAD_ALIVE_P ? dev->load[LOAD_P_NUM + 3].alive = false : dev->load[LOAD_P_NUM + 3].alive = true;


	return;
}
//处理负荷挂载系统状态
void HandleLoadSys(DEVINFO* dev){
#ifdef _LOG
	cout << "Log[func HandleLoadSys]: running HandleLoadSys" << endl;
#endif
	uint8 temp, index;
	uint8 stat1, stat2;

	//开关站负荷信息
	for (int i = 0;i < LINE_NUM_KGZ;++i){
		temp = uint8(dev->Load_Conn_KGZ[i].value);
		stat1 = temp & 0x1;
		stat2 = temp & 0x2;
		dev->load[i].onWhichSys = stat1 + stat2;
		dev->load[i].voltagelevel = 2;
	}
	//二空压负荷信息
	for (int i = 0;i < LINE_NUM_EKY;++i){
		temp = uint8(dev->Load_Conn_EKY[i].value);
		stat1 = ((temp & 0x1) & dev->S1_35kV_B1)|(((temp & 0x2)>>1) & dev->S1_35kV_B2);
		stat2 = ((temp & 0x1) & dev->S2_35kV_B1)|(((temp & 0x2)>>1) & dev->S2_35kV_B2);
		dev->load[i + INDEX_EKY].onWhichSys = stat1 + stat2 * 2;
		dev->load[i + INDEX_EKY].voltagelevel = 1;
	}
	//三催化负荷信息
	for (int i = 0;i < LINE_NUM_CH3;++i){
		temp = uint8(dev->Load_Conn_CH3[i].value);
		stat1 = ((temp & 0x1) & dev->S1_35kV_B1)|(((temp & 0x2)>>1) & dev->S1_35kV_B2);
		stat2 = ((temp & 0x1) & dev->S2_35kV_B1)|(((temp & 0x2)>>1) & dev->S2_35kV_B2);
		dev->load[i + INDEX_CH3].onWhichSys = stat1 + stat2 * 2;
		dev->load[i + INDEX_CH3].voltagelevel = 1;
	}
	//四催化负荷信息
	for (int i = 0;i < LINE_NUM_CH4;++i){
		temp = uint8(dev->Load_Conn_CH4[i].value);
		stat1 = ((temp & 0x1) & dev->S1_35kV_B1)|(((temp & 0x2)>>1) & dev->S1_35kV_B2);
		stat2 = ((temp & 0x1) & dev->S2_35kV_B1)|(((temp & 0x2)>>1) & dev->S2_35kV_B2);
 		dev->load[i + INDEX_CH4].onWhichSys = stat1 + stat2 * 2;
		dev->load[i + INDEX_CH4].voltagelevel = 1;
	}


	return;
}
//根据优先级统计负荷功率
void CalLoadStatics(DEVINFO* dev){
	uint8 prior;
	uint8 uSys, vl;
	bool  under40;
	float p;

	dev->p_all_kq = 0.0;
	dev->p_40_kq = 0.0;
	dev->p_all_kq_s1 = 0.0;
	dev->p_40_kq_s1 = 0.0;
	dev->p_all_kq_s2 = 0.0;
	dev->p_40_kq_s2 = 0.0;
	dev->p_kq_s1_66 = 0.0;
	dev->p_40_kq_s1_66 = 0.0;
	dev->p_kq_s2_66 = 0.0;
	dev->p_40_kq_s2_66 = 0.0;

	//根据优先级统计负荷功率
	for (int i = 0; i < LOAD_P_NUM; ++i){
		p = dev->load[i].pload;
		prior = dev->load[i].prior;
		uSys = dev->load[i].onWhichSys;
		vl = dev->load[i].voltagelevel;

		if(!dev->load[i].alive) continue;	//负荷未投运，则不统计

		if (prior > 0 && prior <= MAX_PRIOR){
			prior <= 40 ? under40 = true : under40 = false;
			
			//联网情况
			dev->p_all_kq += p;
			under40 == true ? dev->p_40_kq += p: dev->p_40_kq += 0.0;

			//统计各个系统下面的负荷情况，需要考虑的问题是：系统1跳入孤网，需不需要切与系统12均相连的负荷。
			//目前按照只切完全孤网的系统负荷

			//处于系统1下 -- 默认统计只要跟系统1联网的所有负荷，即onWhichSys = 1 | 3
			if ((uSys & 0x1) != 0x0){
				dev->p_all_kq_s1 += p;
				under40 == true ? dev->p_40_kq_s1 += p: dev->p_40_kq_s1 += 0.0;
				//统计系统1下66kV负荷
				if (vl == 2){
					dev->p_kq_s1_66 += p;
					under40 == true ? dev->p_40_kq_s1_66 += p: dev->p_40_kq_s1_66 += 0.0;
				}
			}
			//处于系统2下
			if((uSys & 0x2) != 0x0){
				dev->p_all_kq_s2 += p;
				under40 == true ? dev->p_40_kq_s2 += p: dev->p_40_kq_s2 += 0.0;
				if (vl == 2){
					dev->p_kq_s2_66 += p;
					under40 == true ? dev->p_40_kq_s2_66 += p: dev->p_40_kq_s2_66 += 0.0;
				}
			}
		}
	}

	return;	
}

//清除切除标志
void ClearCuttedTag(DEVINFO* dev){
	for (int i = 0;i < LOAD_P_NUM + 4;++i){
		dev->load[i].beCutted = false;
	}
}

bool TWJ(uint8 tz, uint8 hwj){
	return ((tz!=0x0) || (hwj == 0x0));
}
bool HWJ(uint8 tz, uint8 hwj){
	return ((tz==0x0) && (hwj != 0x0));
}

//根据要求形成负荷优先级信息
void CalLoadInfoByPrior(DEVINFO* dev, uint8 sys, uint8 vl){
	float p;
	uint8 prior;
	//初始化储存数组
	for (int i = 0;i < MAX_PRIOR;i++){
		dev->p_prior[i] = 0.0;
		dev->cutted_prior[i] = false;
	}
	//清楚负荷切除信息
	//ClearCuttedTag(dev);
	//统计负荷信息
	for (int i = 0;i < LOAD_P_NUM;++i){
		//负荷量为0，优先级为0， 均不切
		if (!dev->load[i].alive || (dev->load[i].prior <= 0)){
			continue;
		}
		if ((dev->load[i].voltagelevel & vl) == 0x0){//电压等级不匹配,不纳入优先级统计
			continue;
		}
		//系统信息有关联则纳入优先级统计
		if (((dev->load[i].onWhichSys & sys) == 0x0) || (dev->load[i].onWhichSys <= 0) || (dev->load[i].onWhichSys > 3)){
			continue;
		}
		p = dev->load[i].pload;
		prior = dev->load[i].prior;
		dev->p_prior[prior - 1] += p;		
	}
	return;
}

//根据需切量负荷量计算优先级切除信息
//	xql:需切量
//  p_all_kq:全系统可切量
//  p_40_kq: 全系统前40优先级可切量
//  p_prior: 各优先级可切负荷
//  cutted:  各优先级切除标志
//  size  :  优先级个数
//  qql_set: 允许最大欠切量
void LoadCuttedByPxql(float xql, float p_all_kq, float p_40_kq, float* p_prior, bool* cutted, int size, float qql_set){
	float p_syl;// 剩余需切负荷量
	float p;
	//清空优先级切除信息
	for (int i = 0; i < size; ++i){
		cutted[i] = false;
	}
	//需切量小于0， 退出
	if (xql <= 0.0) return;

	//首先跟全网可切量计算
	if (xql >= p_all_kq){
		//全网不够切
		for (int i = 0; i < size; ++i){
			if (p_prior[i] > LOAD_ALIVE_P){
				cutted[i] = true;
			}else{
				cutted[i] = false;
			}
		}
		return;
	}else if (xql >= p_40_kq){
		//前优先级40负荷不够切
		for (int i = 0; i < 40; ++i){
			if (p_prior[i] > LOAD_ALIVE_P){
				cutted[i] = true;
			}else{
				cutted[i] = false;
			}
		}
		p_syl = xql - p_40_kq;
		for (int i = 40; i < size; ++i){
			//该优先级负荷信息判断
			if (p_prior[i] < LOAD_ALIVE_P){
				cutted[i] = false;
				continue;
			} 
			p_syl -= p_prior[i];
			if (p_syl < 0.0){//存在需切量,则将当优先级置为切除，否则跳出循环
				break;
			}else{
				cutted[i] = true;
			}
			
		}
		return;
	}else{
		//只在前40优先级中切负荷的情况
		p_syl = xql;//需切量即为剩余需切量
		for (int i = 0; i < 40; ++i){
			//该优先级负荷信息判断
			if (p_prior[i] < LOAD_ALIVE_P){
				cutted[i] = false;
				continue;
			} 
			p_syl -= p_prior[i];
			cutted[i] = true;

			if ((p_syl >= 0.0) && (p_syl <= qql_set)){//欠切量满足最小欠切门槛，则停止搜索
				break;
			}else if (p_syl < 0.0){//过切了，则取消切除
				p_syl += p_prior[i];
				cutted[i] = false;
			}
		}
		return;

	}
	return;
}

//  更新负荷切除信息
//	dev:装置结构体地址
//  no_sys: 1-系统1  2-系统2   3-全网
void UpdateCuttedInfo(DEVINFO* dev, uint8 no_sys, uint8 vl){

	uint8 prior;
//	float pcutted = 0.0;//统计切除量
//	uint8 ncutted = 0;
	for (int i = 0; i < LOAD_P_NUM; ++i){
		//负荷未投运不处理
		if (dev->load[i].alive == false) continue;
		//负荷在系统1或系统2中切除，且系统状态不符合则不处理
		if ((dev->load[i].voltagelevel & vl) == 0x0){
			continue;
		}
		if ((dev->load[i].onWhichSys & no_sys) == 0x0){//系统无关联则不更新
			continue;
		}
		prior = dev->load[i].prior;
		if (dev->cutted_prior[prior - 1]){
			dev->load[i].beCutted = true;
		}
	}
	return;
}


//输出负荷切除信息
void ExportLoadOutput(DEVINFO* dev, int tac_index, char* tac_num, float yq, float kq){
	float pcutted = 0.0;//负荷切除量
	uint8 ncutted = 0;//负荷切除个数

	strcpy(dev->tac[tac_index].tac_num, tac_num);
	dev->tac[tac_index].tac_yq = yq;
	dev->tac[tac_index].tac_kq = kq;

	for (int i = 0; i < LOAD_P_NUM + 4; ++i){
		//dev->LoadOutput[tac_index][i].fun_num = dev->load[i].fun;
		//dev->LoadOutput[tac_index][i].inf_num = dev->load[i].inf;
		dev->LoadOutput[tac_index][i].cutted = dev->load[i].beCutted;
		if (dev->LoadOutput[tac_index][i].cutted){
			pcutted += dev->load[i].pload;
			ncutted++;
		}
	}
	//dev->tac[tac_index].data = dev->LoadOutput[tac_index];
	//dev->tac.data_num = LOAD_P_NUM + 4;
	dev->tac[tac_index].tac_sq = pcutted;
	//dev->tac.tac_pcutted = pcutted;
	//dev->tac.tac_ncutted = ncutted;

#ifdef _LOG
	//输出策略输出信息
	//LogFuncSendInfo(&(dev->tac[tac_index]));
	LogFuncSendInfo(dev->tac + tac_index);
#endif

#ifndef _DEBUG
	//输出切除信息
	//func_send(SHZZ,&(dev->tac), 1, env_send);
#else
//	bool res = SendTacFile(std::string(".\\tacoutfile.txt"), dev);
	bool res = SendTacFile(std::string("./tmp/tacoutfile.txt"), dev);
	if (!res){
		std::cout<< "Error: Failed to SendTacFile!" << endl;
	}
#endif

	return;
}
//首先切除化机双线，华总双线
float CutHJZXFirst(DEVINFO* dev, uint8 sys){
#ifdef _LOG
	cout << "Log[func CutHJZXFirst]: running CutHJZXFirst" << endl;
#endif
	float res = 0;
	for (int i = 0;i < 4;++i){
		if (dev->load[LOAD_P_NUM + i].alive && ((dev->load[LOAD_P_NUM + i].onWhichSys & sys)!= 0x0) ){
			res += dev->load[LOAD_P_NUM + i].pload;
			dev->load[LOAD_P_NUM + i].beCutted = true;
		}
	}
	return res;
}

//策略1动作逻辑
int RUN_TAC_NO1_FAULT(DEVINFO* dev, FAULTINFO* fault){
#ifdef _LOG
	cout << "Log[func RUN_TAC_NO1_FAULT]: running RUN_TAC_NO1_FAULT" << endl;
#endif
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action = false;
	float xql, hjz;
	xql = dev->P9591 - dev->P9572;

	//故障前状态满足
	stat_action_200ms = ((dev->HWJ9591 || dev->HWJ9592) || ((dev->HWJ9571 == 0) && (dev->HWJ9511 || dev->HWJ9572))) && dev->Conn_S2;
	//故障状态满足
	stat_action = (((fault->T9591 || (dev->HWJ9591 == 0x0)) && (fault->T9572 || (dev->HWJ9572 == 0x0))) ||
				  ((dev->HWJ9571 == 0x0) && (fault->T9511 || (dev->HWJ9511 == 0x0)) && (fault->T9572 || (dev->HWJ9572 == 0x0)))) && dev->Conn_S2;
#ifdef _LOG
	cout << "Log[func RUN_TAC_NO1_FAULT]: stat_action_200ms = " << int(stat_action_200ms) << endl
		 << "                             stat_action       = " << int(stat_action) << endl
		 << "                             xql               = " << xql << endl;
#endif
	if (stat_action_200ms && stat_action && xql > 0.0){
		triggered = 1;//置动作标志
		//更新策略输出部分参数
		//		dev->tac.tac_num = 1;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 1);
		CalPKqFault(dev, fault, 1, 3);//在系统1中35-66中切除

		//strcpy(dev->tac.tac_num, "1-1");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;

		xql -= hjz;
		//计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//更新负荷切除信息
		UpdateCuttedInfo(dev, 1, 3);
		//输出策略结果
		ExportLoadOutput(dev, INDEX_TAC1, "1-1", xql + hjz, dev->p_all_kq + hjz);
	}

	return triggered;
}


//策略2动作逻辑
int RUN_TAC_NO2_FAULT(DEVINFO* dev, FAULTINFO* fault){
#ifdef _LOG
	cout << "Log[func RUN_TAC_NO2_FAULT]: running RUN_TAC_NO2_FAULT" << endl;
#endif
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action = false;
	float xql, hjz;
	xql = dev->P9561 - dev->P9572;

	stat_action_200ms = (dev->HWJ9561 || dev->HWJ9572) && dev->Conn_S2;
	stat_action = (fault->T9561 || (dev->HWJ9561 == 0x0)) && (fault->T9572 || (dev->HWJ9572 == 0x0)) && dev->Conn_S2;
#ifdef _LOG
	cout << "Log[func RUN_TAC_NO2_FAULT]: stat_action_200ms = " << int(stat_action_200ms) << endl
		 << "                             stat_action       = " << int(stat_action) << endl
		 << "                             xql               = " << xql << endl;
#endif
	if (stat_action_200ms && stat_action && xql > 0.0){
		triggered = 1;
		//更新策略输出部分参数
		//		dev->tac.tac_num = 2;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev,1);
		CalPKqFault(dev, fault, 1, 2);

		//strcpy(dev->tac.tac_num, "2-1");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;

		xql -= hjz;
		//计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//更新负荷切除信息
		UpdateCuttedInfo(dev, 1, 2);
		//输出策略结果
		ExportLoadOutput(dev, INDEX_TAC2, "2-1", xql + hjz, dev->p_all_kq + hjz);
	}

	return triggered;
}

//策略3动作逻辑
int RUN_TAC_NO3_FAULT(DEVINFO* dev, FAULTINFO* fault){
#ifdef _LOG
	cout << "Log[func RUN_TAC_NO3_FAULT]: running RUN_TAC_NO3_FAULT" << endl;
#endif
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action = false;
	float xql, hjz;
	xql = dev->P9592 + dev->P9572;

	stat_action_200ms = ((dev->HWJ9592 || dev->HWJ9572) || ((dev->HWJ9571 == 0) && (dev->HWJ9512 || dev->HWJ9572))) && dev->Conn_S1;
	stat_action = (((fault->T9592 || (dev->HWJ9592 == 0x0)) && (fault->T9572 || (dev->HWJ9572 == 0x0))) ||
				  ((dev->HWJ9571 == 0x0) && (fault->T9512 || (dev->HWJ9512 == 0x0)) && (fault->T9572 || (dev->HWJ9572 == 0x0)))) && dev->Conn_S1;
#ifdef _LOG
	cout << "Log[func RUN_TAC_NO3_FAULT]: stat_action_200ms = " << int(stat_action_200ms) << endl
		 << "                             stat_action       = " << int(stat_action) << endl
		 << "                             xql               = " << xql << endl;
#endif
	if (stat_action_200ms && stat_action && xql > 0.0){
		triggered++;
		//更新策略输出部分参数
		ClearCuttedTag(dev);
		//		dev->tac.tac_num = 3;
		hjz = CutHJZXFirst(dev,  2);
		CalPKqFault(dev, fault, 2, 3);

		//strcpy(dev->tac.tac_num, "3-1");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;

		xql -= hjz;
		//计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//更新负荷切除信息
		UpdateCuttedInfo(dev, 2, 3);
		//输出策略结果
		ExportLoadOutput(dev, INDEX_TAC3, "3-1", xql + hjz, dev->p_all_kq + hjz);
	}

	return triggered;

}

//策略4动作逻辑
int RUN_TAC_NO4_FAULT(DEVINFO* dev, FAULTINFO* fault){
#ifdef _LOG
	cout << "Log[func RUN_TAC_NO4_FAULT]: running RUN_TAC_NO4_FAULT" << endl;
#endif
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action = false;
	float xql, hjz;
	xql = dev->P9562 + dev->P9572;

	stat_action_200ms = (dev->HWJ9562 || dev->HWJ9572) && dev->Conn_S1;
	stat_action = (fault->T9562 || (dev->HWJ9562 == 0x0)) && (fault->T9572 || (dev->HWJ9572 == 0x0)) && dev->Conn_S1;
#ifdef _LOG
	cout << "Log[func RUN_TAC_NO4_FAULT]: stat_action_200ms = " << int(stat_action_200ms) << endl
		 << "                             stat_action       = " << int(stat_action) << endl
		 << "                             xql               = " << xql << endl;
#endif
	if (stat_action_200ms && stat_action && xql > 0.0){
		triggered++;
		//更新策略输出部分参数
		//		dev->tac.tac_num = 4;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 2);
		CalPKqFault(dev, fault, 2, 2);

		//strcpy(dev->tac.tac_num, "4-1");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;

		xql -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 2, 2);
		//计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//更新负荷切除信息
		UpdateCuttedInfo(dev, 2, 2);
		//输出策略结果
		ExportLoadOutput(dev, INDEX_TAC4, "4-1", xql + hjz, dev->p_all_kq + hjz);
	}

	return triggered;

}

//策略5动作逻辑
int RUN_TAC_NO5_FAULT(DEVINFO* dev, FAULTINFO* fault){
#ifdef _LOG
	cout << "Log[func RUN_TAC_NO5_FAULT]: running RUN_TAC_NO5_FAULT" << endl;
#endif
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action = false;
	float xql, xql1, xql2, hjz;

	stat_action_200ms = ((dev->HWJ9511 || dev->HWJ9512) || (dev->HWJ9591 || dev->HWJ9512)
		||(((dev->HWJ9511 || dev->HWJ9592) || (dev->HWJ9512 || dev->HWJ9591))&&(dev->HWJ9571 == 0)))
		&& dev->HWJ9561 && dev->HWJ9562;
	stat_action = ((TWJ(fault->T9511, dev->HWJ9511) && TWJ(fault->T9512, dev->HWJ9512))||
		          (TWJ(fault->T9591, dev->HWJ9591) && TWJ(fault->T9592, dev->HWJ9592))||
				  (((TWJ(fault->T9511, dev->HWJ9511) && TWJ(fault->T9592, dev->HWJ9592))||
				  (TWJ(fault->T9512, dev->HWJ9512) && TWJ(fault->T9591, dev->HWJ9591))) && (dev->HWJ9571 == 0x0))) &&
				  dev->HWJ9561 && dev->HWJ9562;

#ifdef _LOG
	cout << "Log[func RUN_TAC_NO5_FAULT]: stat_action_200ms = " << int(stat_action_200ms) << endl
		 << "                             stat_action       = " << int(stat_action) << endl
		 << "                             HWJ9572           = " << int(dev->HWJ9572) << endl;
#endif

	if (stat_action_200ms && stat_action && (dev->HWJ9572 == 0)){//9572停运
		triggered++;
		xql1 = dev->P9591 - dev->P9572;
		xql2 = dev->P9592 + dev->P9572;
		//更新策略输出部分参数
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 1);
		CalPKqFault(dev,fault,1,3);
		//		dev->tac.tac_num = 5;
		//strcpy(dev->tac.tac_num, "5-1");
		//dev->tac.tac_yq = xql1;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql1 -= hjz;
		//系统1计算负荷切除信息
		LoadCuttedByPxql(xql1, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统1更新负荷切除信息
		UpdateCuttedInfo(dev, 1, 3);
		//输出系统1切负荷信息 
		ExportLoadOutput(dev, INDEX_TAC5, "5-1", xql1 + hjz, dev->p_all_kq + hjz);

		//系统2故障
		ClearCuttedTag(dev);
		hjz = CutHJZXFirst(dev, 2);
		CalPKqFault(dev, fault, 2, 3);
		//strcpy(dev->tac.tac_num, "5-2");
		//dev->tac.tac_yq = xql2;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql2 -= hjz;
		//系统2计算负荷切除信息
		LoadCuttedByPxql(xql2, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统2更新负荷切除信息
		UpdateCuttedInfo(dev, 2, 3);
		//输出策略结果
		ExportLoadOutput(dev, INDEX_TAC5+1, "5-2", xql2 + hjz, dev->p_all_kq + hjz);

	}else if (stat_action_200ms && stat_action && dev->HWJ9572){//9572运行
		triggered++;
		xql = dev->P9591 + dev->P9592;
		//更新策略输出部分参数
		//		dev->tac.tac_num = 5;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 3);
		CalPKqFault(dev, fault, 3, 3);

		//strcpy(dev->tac.tac_num, "5-3");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql -= hjz;
		//全网计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//全网更新负荷切除信息
		UpdateCuttedInfo(dev, 3, 3);
		//输出策略结果
		ExportLoadOutput(dev, INDEX_TAC5+2, "5-3", xql + hjz, dev->p_all_kq + hjz);

	}

	return triggered;

}

//策略6动作逻辑
int RUN_TAC_NO6_FAULT(DEVINFO* dev, FAULTINFO* fault){
#ifdef _LOG
	cout << "Log[func RUN_TAC_NO6_FAULT]: running RUN_TAC_NO6_FAULT" << endl;
#endif
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action = false;
	float xql, xql1, xql2, hjz;

	stat_action_200ms = ((dev->HWJ9591 || dev->HWJ9562) || ((dev->HWJ9571 == 0) && (dev->HWJ9511 || dev->HWJ9562))) && dev->HWJ9561;
	stat_action = ((TWJ(fault->T9591, dev->HWJ9591) && TWJ(fault->T9562, dev->HWJ9562))||
			      (TWJ(fault->T9511, dev->HWJ9511) && TWJ(fault->T9562, dev->HWJ9562) && (dev->HWJ9571 == 0x0))) && dev->HWJ9561;

#ifdef _LOG
	cout << "Log[func RUN_TAC_NO6_FAULT]: stat_action_200ms = " << int(stat_action_200ms) << endl
		 << "                             stat_action       = " << int(stat_action) << endl
		 << "                             HWJ9572           = " << int(dev->HWJ9572) << endl;
#endif

	if (stat_action_200ms && stat_action && dev->HWJ9572 == 0){//9572停运
		triggered++;
		xql1 = dev->P9591 - dev->P9572;
		xql2 = dev->P9562 + dev->P9572;
		//更新策略输出部分参数
		//		dev->tac.tac_num = 6;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 1);
		CalPKqFault(dev,fault, 1, 3);
		//strcpy(dev->tac.tac_num, "6-1");
		//dev->tac.tac_yq = xql1;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql1 -= hjz;
		//系统1计算负荷切除信息
		LoadCuttedByPxql(xql1, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统1更新负荷切除信息
		UpdateCuttedInfo(dev, 1, 3);
		//输出策略结果
		ExportLoadOutput(dev, INDEX_TAC6, "6-1", xql1 + hjz, dev->p_all_kq + hjz);

		//系统2故障
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 2);
		CalPKqFault(dev, fault, 2, 2);

		//strcpy(dev->tac.tac_num, "6-2");
		//dev->tac.tac_yq = xql2;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql2 -= hjz;
		//系统2计算负荷切除信息
		LoadCuttedByPxql(xql2, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统2更新负荷切除信息
		UpdateCuttedInfo(dev, 2, 2);
		//输出策略结果
		ExportLoadOutput(dev, INDEX_TAC6+1, "6-2", xql2 + hjz, dev->p_all_kq + hjz);
	}else if (stat_action_200ms && stat_action && dev->HWJ9572){//9572运行
		triggered++;
		xql = dev->P9591 + dev->P9592;
		//更新策略输出部分参数
		//		dev->tac.tac_num = 6;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 3);
		CalPKqFault(dev, fault, 3, 3);
		//strcpy(dev->tac.tac_num, "6-3");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql -= hjz;
		//全网计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//全网更新负荷切除信息
		UpdateCuttedInfo(dev, 3, 3);
		//输出策略结果
		ExportLoadOutput(dev, INDEX_TAC6+2, "6-3", xql + hjz, dev->p_all_kq + hjz);

	}

	return triggered;
}

//策略7动作逻辑
int RUN_TAC_NO7_FAULT(DEVINFO* dev, FAULTINFO* fault){
#ifdef _LOG
	cout << "Log[func RUN_TAC_NO7_FAULT]: running RUN_TAC_NO7_FAULT" << endl;
#endif
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action = false;
	float xql, xql1, xql2, hjz;

	stat_action_200ms = ((dev->HWJ9592 || dev->HWJ9561) || ((dev->HWJ9571 == 0) && (dev->HWJ9512 || dev->HWJ9561))) && dev->HWJ9562;
	stat_action = ((TWJ(fault->T9592, dev->HWJ9592) && TWJ(fault->T9561, dev->HWJ9561))||
				  (TWJ(fault->T9512, dev->HWJ9512) && TWJ(fault->T9561, dev->HWJ9561) && (dev->HWJ9571 == 0x0))) && dev->HWJ9562;
#ifdef _LOG
	cout << "Log[func RUN_TAC_NO7_FAULT]: stat_action_200ms = " << int(stat_action_200ms) << endl
		 << "                             stat_action       = " << int(stat_action) << endl
		 << "                             HWJ9572           = " << int(dev->HWJ9572) << endl;
#endif

	if (stat_action_200ms && stat_action && dev->HWJ9572 == 0){//9572停运
		triggered++;
		xql1 = dev->P9561 - dev->P9572;
		xql2 = dev->P9592 + dev->P9572;
		//更新策略输出部分参数
		//		dev->tac.tac_num = 7;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 2);
		CalPKqFault(dev, fault, 2, 3);
		//strcpy(dev->tac.tac_num, "7-1");
		//dev->tac.tac_yq = xql1;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql1 -= hjz;
		//系统1计算负荷切除信息
		LoadCuttedByPxql(xql1, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统1更新负荷切除信息
		UpdateCuttedInfo(dev, 2, 3);
		//输出策略结果
		ExportLoadOutput(dev, INDEX_TAC7, "7-1", xql1 + hjz, dev->p_all_kq + hjz);

		//系统2故障
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 1);
		CalPKqFault(dev, fault, 1, 2);
		//strcpy(dev->tac.tac_num, "7-2");
		//dev->tac.tac_yq = xql2;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql2 -= hjz;
		//系统2计算负荷切除信息
		LoadCuttedByPxql(xql2, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统2更新负荷切除信息
		UpdateCuttedInfo(dev, 1, 2);
		//输出策略结果
		ExportLoadOutput(dev, INDEX_TAC7+1, "7-2", xql2 + hjz, dev->p_all_kq + hjz);
	}else if (stat_action_200ms && stat_action && dev->HWJ9572){//9572运行
		triggered++;
		xql = dev->P9592 + dev->P9561;
		//更新策略输出部分参数
		//		dev->tac.tac_num = 7;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 3);
		CalPKqFault(dev, fault, 3, 3);
		//strcpy(dev->tac.tac_num, "7-3");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql -= hjz;
		//全网计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//全网更新负荷切除信息
		UpdateCuttedInfo(dev, 3, 3);


		//输出策略结果
		ExportLoadOutput(dev, INDEX_TAC7+2, "7-3", xql + hjz, dev->p_all_kq + hjz);

	}

	return triggered;

}

//策略8动作逻辑
int RUN_TAC_NO8_FAULT(DEVINFO* dev, FAULTINFO* fault){
#ifdef _LOG
	cout << "Log[func RUN_TAC_NO8_FAULT]: running RUN_TAC_NO8_FAULT" << endl;
#endif
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action = false;
	float xql, xql1, xql2, hjz;

	stat_action_200ms = (dev->HWJ9561 || dev->HWJ9562);
	stat_action = TWJ(fault->T9561, dev->HWJ9561) && TWJ(fault->T9562, dev->HWJ9562);

#ifdef _LOG
	cout << "Log[func RUN_TAC_NO8_FAULT]: stat_action_200ms = " << int(stat_action_200ms) << endl
		 << "                             stat_action       = " << int(stat_action) << endl
		 << "                             HWJ9572           = " << int(dev->HWJ9572) << endl;
#endif

	if (stat_action_200ms && stat_action && (dev->HWJ9572 == 0)){//9572停运
		xql1 = dev->P9561 - dev->P9572;
		xql2 = dev->P9562 + dev->P9572;
		//更新策略输出部分参数
		//		dev->tac.tac_num = 8;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 1);
		CalPKqFault(dev, fault, 1, 2);
		//strcpy(dev->tac.tac_num, "8-1");
		//dev->tac.tac_yq = xql1;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql1 -= hjz;
		//系统1计算负荷切除信息
		LoadCuttedByPxql(xql1, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统1更新负荷切除信息
		UpdateCuttedInfo(dev, 1, 2);
		//输出策略结果
		ExportLoadOutput(dev, INDEX_TAC8, "8-1", xql1 + hjz, dev->p_all_kq + hjz);

		//系统2故障
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 2);
		CalPKqFault(dev, fault, 2, 2);
		//strcpy(dev->tac.tac_num, "8-2");
		//dev->tac.tac_yq = xql2;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql2 -= hjz;
		//系统2计算负荷切除信息
		LoadCuttedByPxql(xql2, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统2更新负荷切除信息
		UpdateCuttedInfo(dev, 2, 2);
		
		ExportLoadOutput(dev, INDEX_TAC8+1, "8-2", xql2 + hjz, dev->p_all_kq + hjz);

	}else if (stat_action_200ms && stat_action && dev->HWJ9572){//9572运行
		triggered++;
		xql = dev->P9562 + dev->P9561;
		//更新策略输出部分参数
		//		dev->tac.tac_num = 8;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 3);
		CalPKqFault(dev, fault, 3, 2);
		//strcpy(dev->tac.tac_num, "8-3");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql -= hjz;
		//全网计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//全网更新负荷切除信息
		UpdateCuttedInfo(dev, 3, 2);
		//输出策略结果
		ExportLoadOutput(dev, INDEX_TAC8+2, "8-3", xql + hjz, dev->p_all_kq + hjz);

	}

	return triggered;

}

//初始化故障控制
void InitializeFault(FAULTINFO* fault){
	fault->T9511 = 0;
	fault->T9512 = 0;
	fault->T9591 = 0;
	fault->T9592 = 0;
	fault->T9561 = 0;
	fault->T9572 = 0;

	fault->FT_KGZ_S1 = 0;
	fault->FT_KGZ_S2 = 0;
	fault->FT_EKY_S1 = 0;
	fault->FT_EKY_S2 = 0;
	fault->FT_CH3_S1 = 0;
	fault->FT_CH4_S1 = 0;
	fault->FT_CH3_S2 = 0;
	fault->FT_CH4_S2 = 0;
}

//初始化策略输出结果
void InitializeTacOutput(DEVINFO* dev){
	//策略编号
	strcpy(dev->tac[0].tac_num, "1-1");
	strcpy(dev->tac[1].tac_num, "2-1");
	strcpy(dev->tac[2].tac_num, "3-1");
	strcpy(dev->tac[3].tac_num, "4-1");
	strcpy(dev->tac[4].tac_num, "5-1");
	strcpy(dev->tac[5].tac_num, "5-2");
	strcpy(dev->tac[6].tac_num, "5-3");
	strcpy(dev->tac[7].tac_num, "6-1");
	strcpy(dev->tac[8].tac_num, "6-2");
	strcpy(dev->tac[9].tac_num, "6-3");
	strcpy(dev->tac[10].tac_num, "7-1");
	strcpy(dev->tac[11].tac_num, "7-2");
	strcpy(dev->tac[12].tac_num, "7-3");
	strcpy(dev->tac[13].tac_num, "8-1");
	strcpy(dev->tac[14].tac_num, "8-2");
	strcpy(dev->tac[15].tac_num, "8-3");
	for (int i = 0;i < TACOUT_NUM;i++){
			//strcpy(dev->tac[i].tac_num,"");
			dev->tac[i].tac_kq = 0.0;
			dev->tac[i].tac_yq = 0.0;
			dev->tac[i].tac_sq = 0.0;
			dev->tac[i].data_num = LOAD_P_NUM + 4;
			dev->tac[i].data = dev->LoadOutput[i];
		for (int j = 0;j < LOAD_P_NUM+4;j++){
			dev->LoadOutput[i][j].fun_num = dev->load[j].fun;
			dev->LoadOutput[i][j].inf_num = dev->load[j].inf;
			dev->LoadOutput[i][j].cutted = false;
		}
	}
	return;
}


void SetFault(FAULTINFO* fault, uint32 ft){
	fault->T9511 = uint8(ft & 0x1);
	fault->T9512 = uint8((ft>>1) & 0x1);
	fault->T9591 = uint8((ft>>2) & 0x1);
	fault->T9592 = uint8((ft>>3) & 0x1);
	fault->T9561 = uint8((ft>>4) & 0x1);
	fault->T9562 = uint8((ft>>5) & 0x1);
	fault->T9572 = uint8((ft>>6) & 0x1);

	fault->FT_KGZ_S1 = uint8((ft>> 8) & 0x1);
	fault->FT_KGZ_S2 = uint8((ft>> 9) & 0x1);
	fault->FT_EKY_S1 = uint8((ft>>10) & 0x1);
	fault->FT_EKY_S2 = uint8((ft>>11) & 0x1);
	fault->FT_CH3_S1 = uint8((ft>>12) & 0x1);
	fault->FT_CH3_S2 = uint8((ft>>13) & 0x1);
	fault->FT_CH4_S1 = uint8((ft>>14) & 0x1);
	fault->FT_CH4_S2 = uint8((ft>>15) & 0x1);
	return;
}

//设置全策略检索
void SetAllFault(FAULTINFO* fault){
	fault->T9511 = 0x1;
	fault->T9512 = 0x1;
	fault->T9591 = 0x1;
	fault->T9561 = 0x1;
	fault->T9562 = 0x1;
	fault->T9572 = 0x1;
	fault->FT_CH3_S1 = 0x1;
	fault->FT_CH3_S2 = 0x1;
	fault->FT_CH4_S1 = 0x1;
	fault->FT_CH4_S2 = 0x1;
	fault->FT_KGZ_S1 = 0x1;
	fault->FT_KGZ_S2 = 0x1;
	fault->FT_EKY_S1 = 0x1;
	fault->FT_EKY_S2 = 0x1;

	return;
}

//根据系统故障及开关位置运行情况推测系统互联情况
void CheckSysConn(DEVINFO* dev, FAULTINFO* fault){
	bool s1, s2;
	s1 = (HWJ(fault->T9511, dev->HWJ9511) || (HWJ(fault->T9512, dev->HWJ9512) && dev->HWJ9571))
		&& HWJ(fault->T9591, dev->HWJ9591) && HWJ(fault->T9561, dev->HWJ9561);
	s2 = (HWJ(fault->T9512, dev->HWJ9512) || (HWJ(fault->T9511, dev->HWJ9511) && dev->HWJ9571))
		&& HWJ(fault->T9592, dev->HWJ9592) && HWJ(fault->T9562, dev->HWJ9562);
	dev->Conn_S1 = uint8(s1 && TWJ(fault->T9572, dev->HWJ9572));
	dev->Conn_S2 = uint8(s2 && TWJ(fault->T9572, dev->HWJ9572));
	dev->Conn_S1S2 = uint8((s1 && HWJ(fault->T9572, dev->HWJ9572)) || (s2 && HWJ(fault->T9572, dev->HWJ9572)));
	return;
}


//根据故障频率降低计算可切功率
void CalPKqFault(DEVINFO*dev, FAULTINFO* fault, uint8 sys, uint8 vl){
	uint8 prior;
	uint8 uSys, uVl, FT_SYS;
	bool  under40;
	float p;

	dev->p_all_kq = 0.0;
	dev->p_40_kq = 0.0;
	//初始化优先级储存数组
	for (int i = 0;i < MAX_PRIOR;i++){
		dev->p_prior[i] = 0.0;
		dev->cutted_prior[i] = false;
	}

	//根据优先级统计负荷功率
	for (int i = 0; i < LOAD_P_NUM; ++i){
		p = dev->load[i].pload;
		prior = dev->load[i].prior;
		uSys = dev->load[i].onWhichSys;
		uVl = dev->load[i].voltagelevel;

		if(!dev->load[i].alive) continue;	//负荷未投运，则不统计
		if(prior <=0 || prior > MAX_PRIOR) continue;//优先级不对，不统计

		prior <= 40 ? under40 = true : under40 = false;
		
		if (i < INDEX_EKY){//开关站负荷
			FT_SYS = (fault->FT_KGZ_S1 & 0x1) | ((fault->FT_KGZ_S2 & 0x1)<<1);
			if (((uSys & sys) == 0x0) || ((uVl & vl) == 0x0) || ((uSys & FT_SYS) == 0x0)){
				continue;
			}
		}else if (i < INDEX_CH3){//二空压
			FT_SYS = (fault->FT_EKY_S1 & 0x1) | ((fault->FT_EKY_S2 & 0x1)<<1);
			if (((uSys & sys) == 0x0) || ((uVl & vl) == 0x0) || ((uSys & FT_SYS) == 0x0)){
				continue;
			}
		}else if (i < INDEX_CH4){//三催化
			FT_SYS = (fault->FT_CH3_S1 & 0x1) | ((fault->FT_CH3_S2 & 0x1)<<1);
			if (((uSys & sys) == 0x0) || ((uVl & vl) == 0x0) || ((uSys & FT_SYS) == 0x0)){
				continue;
			}
		}else{//四催化
			FT_SYS = (fault->FT_CH4_S1 & 0x1) | ((fault->FT_CH4_S2 & 0x1)<<1);
			if (((uSys & sys) == 0x0) || ((uVl & vl) == 0x0) || ((uSys & FT_SYS) == 0x0)){
				continue;
			}
		}

		//开始办正事了，说明这个负荷是可以切的。
		dev->p_all_kq += p;
		under40 ? dev->p_40_kq += p : dev->p_40_kq += 0.0;
		dev->p_prior[prior - 1] += p;//该优先级负荷累加
#ifdef _DEBUG
		cout << i << " - " << int(prior) << " - " << p << endl;
#endif
	}
	return;
}

//动态库策略模拟函数
void run_tac_simulate(){

	//1. 初始化
	Initialize(&devdata, &faultdata);
	//2. 读取数据
	ReadDevInfo(&devdata, &faultdata);
	//3. 处理负荷信息
	HandleLoadSys(&devdata);	
	//4. 计算故障后系统互联
	CheckSysConn(&devdata, &faultdata);

	SetAllFault(&faultdata);
	devdata.Conn_S1 = 1;
	devdata.Conn_S2 = 1;
	devdata.Conn_S1S2 = 0;

	if(devdata.Conn_S1S2) return;//系统12互联且联网，则不计算相应策略

	InitializeTacOutput(&devdata);
	//CalLoadStatics(&devdata);
#ifdef _LOG
	//输出系统状态数据
	LogFuncSysdata(&devdata);
	cout << "开关运行" << endl;
	cout <<"9511:" << int(devdata.HWJ9511) << int(faultdata.T9511)<< endl;
	cout <<"9512:" << int(devdata.HWJ9512) << int(faultdata.T9512)<< endl
		 <<"9591:" << int(devdata.HWJ9591) << int(faultdata.T9591)<< endl
		 <<"9592:" << int(devdata.HWJ9592) << int(faultdata.T9592)<< endl
		 <<"9561:" << int(devdata.HWJ9561) << int(faultdata.T9561)<< endl
		 <<"9562:" << int(devdata.HWJ9562) << int(faultdata.T9562)<< endl
		 <<"9572:" << int(devdata.HWJ9572) << int(faultdata.T9572)<< endl
		 <<"9571:" << int(devdata.HWJ9571) << endl;
	cout << "频率下降模拟：" << endl;
	cout << "开关站系统1：" << int(faultdata.FT_KGZ_S1) << endl
		 << "开关站系统2：" << int(faultdata.FT_KGZ_S2) << endl
		 << "二空压系统1：" << int(faultdata.FT_EKY_S1) << endl
		 << "二空压系统2：" << int(faultdata.FT_EKY_S2) << endl
		 << "三催化系统1：" << int(faultdata.FT_CH3_S1) << endl
		 << "三催化系统2：" << int(faultdata.FT_CH3_S2) << endl
		 << "四催化系统1：" << int(faultdata.FT_CH4_S1) << endl
		 << "四催化系统2：" << int(faultdata.FT_CH4_S2) << endl;
#endif

	//4. 策略计算
	int trigg = 0;
	trigg = RUN_TAC_NO1_FAULT(&devdata,&faultdata);
	trigg = RUN_TAC_NO2_FAULT(&devdata,&faultdata);
	trigg = RUN_TAC_NO3_FAULT(&devdata,&faultdata);
	trigg = RUN_TAC_NO4_FAULT(&devdata,&faultdata);
	trigg = RUN_TAC_NO5_FAULT(&devdata,&faultdata);
	trigg = RUN_TAC_NO6_FAULT(&devdata,&faultdata);
	trigg = RUN_TAC_NO7_FAULT(&devdata,&faultdata);
	trigg = RUN_TAC_NO8_FAULT(&devdata,&faultdata);

#ifndef _DEBUG
	func_send(SHZZ,devdata.tac, TACOUT_NUM, env_send);
#endif

	return;
}


