#include "systac.h"
#include "DeviceSet.h"
#include "DeviceDef.h"
#include <stdio.h>
//定义全局变量
static DEVINFO       devdata;	
static DATA_HANDLER  func_read;
static void*         env_read;
static TAC_HANDLER   func_send;
static void*         env_send;

//输入回调函数
void data_register(DATA_HANDLER data_handler,void *env){
	func_read = data_handler;
	env_read = env;
	return;
}
//输出回调函数
void result_register(TAC_HANDLER tac_handler,void *env){
	func_send = tac_handler;
	env_send = env;
	return;
}
//初始化
void Initialize(DEVINFO* dev){
	//系统模拟量
	for (int i = 0; i < SYS_P_NUM; ++i){
		dev->Sys_P[i].fun_num = FUN_SYS_P[i];
		dev->Sys_P[i].inf_num = INF_SYS_P[i];
		dev->Sys_P[i].value = 0;
	}
	//负荷数据
	for (int i = 0; i < LOAD_P_NUM; ++i){
		dev->Load_P[i].fun_num = FUN_SYS_P[i];
		dev->Load_P[i].inf_num = INF_SYS_P[i];
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

	dev->P9591   = 0.0;
	dev->P9561   = 0.0;
	dev->P9592   = 0.0;
	dev->P9562   = 0.0;
	dev->P9572   = 0.0;
	dev->P_HJX_1 = 0.0;
	dev->P_HJX_2 = 0.0;
	dev->P_HSX   = 0.0;
	dev->P_HZX   = 0.0;

	dev->Conn_S1  = 0;
	dev->Conn_S2  = 0;
	dev->Conn_S1S2= 0;
	dev->HWJ9511  = 0;
	dev->HWJ9512  = 0;
	dev->HWJ9561  = 0;
	dev->HWJ9562  = 0;
	dev->HWJ9591  = 0;
	dev->HWJ9592  = 0;
	dev->HWJ9571  = 1;//默认9571为合着状态
	dev->HWJ9572  = 0;
	dev->HWJ9573  = 0;

	dev->p_qq_setting = 0.0;
	dev->p_all_kq = 0.0;
	dev->p_40_kq = 0.0;
	dev->p_all_kq_s1 = 0.0;
	dev->p_40_kq_s1 = 0.0;
	dev->p_all_kq_s2 = 0.0;
	dev->p_40_kq_s2 = 0.0;
	for (int i = 0; i < MAX_PRIOR; ++i){
		dev->p_prior_s1[i] = 0.0;
		dev->p_prior_s2[i] = 0.0;
		dev->p_prior_s1s2[i] = 0.0;
		dev->cutted_prior[i] = false;
	}

	return;
}
//读取装置信息
void ReadDevInfo(DEVINFO* dev){
	//读取系统模拟量信息
	//func_read(dev->Sys_P, SYS_P_NUM, env_read);
	//读取负荷信息
	//func_read(dev->Load_P, LOAD_P_NUM, env_read);
	//读取优先级定值
	//func_read(dev->Load_Prior, LOAD_P_NUM+1, env_read);
	//读取系统连接状态
	//func_read(dev->Load_Conn, LOAD_CONN_NUM, env_read);
	//读取系统开关运行状态
	//func_read(dev->Sys_Stat, SYS_STAT_NUM, env_read);

	//功率数据预处理
	dev->P9591 = dev->Sys_P[0].value;
	dev->P9561 = dev->Sys_P[1].value;
	dev->P9592 = dev->Sys_P[2].value;
	dev->P9562 = dev->Sys_P[3].value;
	dev->P_HJX_1 = dev->Sys_P[4].value;
	dev->P_HJX_2 = dev->Sys_P[5].value;
	dev->P_HSX = dev->Sys_P[6].value;
	dev->P_HZX = dev->Sys_P[7].value;
	//系统开入状态预处理
	dev->Conn_S1 = int(dev->Sys_Stat[0].value);
	dev->Conn_S2 = int(dev->Sys_Stat[1].value);
	dev->Conn_S1S2 = int(dev->Sys_Stat[2].value);
	dev->HWJ9511 = int(dev->Sys_Stat[3].value);
	dev->HWJ9512 = int(dev->Sys_Stat[4].value);
	dev->HWJ9561 = int(dev->Sys_Stat[5].value);
	dev->HWJ9562 = int(dev->Sys_Stat[6].value);
	dev->HWJ9591 = int(dev->Sys_Stat[7].value);
	dev->HWJ9592 = int(dev->Sys_Stat[8].value);
	dev->HWJ9571 = int(dev->Sys_Stat[9].value);
	dev->HWJ9572 = int(dev->Sys_Stat[10].value);

	//负荷数据处理
	dev->p_qq_setting = dev->Load_Prior[LOAD_P_NUM].value;//频稳欠切功率定值
	for (int i = 0; i < LOAD_P_NUM; ++i){
		dev->load[i].fun = dev->Load_P[i].fun_num;
		dev->load[i].inf = dev->Load_P[i].inf_num;
		dev->load[i].pload = dev->Load_P[i].value;
		dev->load[i].prior = int(dev->Load_Prior[i].value);
		dev->load[i].onWhichSys = 0;
		dev->load[i].beCutted = false;
		dev->load[i].pload < LOAD_ALIVE_P ? dev->load[i].alive = false : dev->load[i].alive = true;
	}

	return;
}
//处理负荷挂载系统状态
void HandleLoadSys(DEVINFO* dev){
	int32 temp; 
	int32 stat1, stat2;
	// 开关站系统1线路
	temp = int32(dev->Sys_Stat[0].value);
	for (int i = 0; i < LINE_NUM_KGZ; ++i){
		dev->load[i].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 1 :0;
	}
	//开关站系统线路2
	temp = int32(dev->Sys_Stat[1].value);
	for (int i = 0; i < LINE_NUM_KGZ; ++i){
		dev->load[i].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 2 :0;
	}
	//二空压系统1线路
	temp = int32(dev->Sys_Stat[2].value);
	for (int i = 0; i < LINE_NUM_EKY; ++i){
		dev->load[i+INDEX_EKY].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 1 :0;
	}
	//二空压系统2线路
	temp = int32(dev->Sys_Stat[3].value);
	for (int i = 0; i < LINE_NUM_EKY; ++i){
		dev->load[i+INDEX_EKY].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 2 :0;
	}
	//三催化系统1线路
	stat1 = int32(dev->Sys_Stat[4].value);
	stat2 = int32(dev->Sys_Stat[5].value);
	temp = (stat1 & 0xffff)|((stat2 & 0xffff)<<16);
	for (int i = 0; i < LINE_NUM_CH3; ++i){
		dev->load[i+INDEX_CH3].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 1 :0;
	}
	//三催化系统2线路
	stat1 = int32(dev->Sys_Stat[6].value);
	stat2 = int32(dev->Sys_Stat[7].value);
	temp = (stat1 & 0xffff)|((stat2 & 0xffff)<<16);
	for (int i = 0; i < LINE_NUM_CH3; ++i){
		dev->load[i+INDEX_CH3].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 2 :0;
	}
	//四催化系统1线路
	stat1 = int32(dev->Sys_Stat[8].value);
	stat2 = int32(dev->Sys_Stat[9].value);
	temp = (stat1 & 0xffff)|((stat2 & 0xffff)<<16);
	for (int i = 0; i < LINE_NUM_CH3; ++i){
		dev->load[i+INDEX_CH4].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 1 :0;
	}
	//四催化系统2线路
	stat1 = int32(dev->Sys_Stat[10].value);
	stat2 = int32(dev->Sys_Stat[11].value);
	temp = (stat1 & 0xffff)|((stat2 & 0xffff)<<16);
	for (int i = 0; i < LINE_NUM_CH3; ++i){
		dev->load[i+INDEX_CH4].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 2 :0;
	}
	return;
}
//根据优先级统计负荷功率
void CalLoadPByPrior(DEVINFO* dev){
	int prior;
	int uSys;
	bool  under40;
	float p;

	dev->p_all_kq = 0.0;
	dev->p_40_kq = 0.0;
	dev->p_all_kq_s1 = 0.0;
	dev->p_40_kq_s1 = 0.0;
	dev->p_all_kq_s2 = 0.0;
	dev->p_40_kq_s2 = 0.0;
	for (int i = 0; i < MAX_PRIOR; ++i){
		dev->p_prior_s1[i] = 0.0;
		dev->p_prior_s2[i] = 0.0;
		dev->p_prior_s1s2[i] = 0.0;
		dev->cutted_prior[i] = false;
	}

	//根据优先级统计负荷功率
	for (int i = 0; i < LOAD_P_NUM; ++i){
		p = dev->load[i].pload;
		prior = dev->load[i].prior;
		uSys = dev->load[i].onWhichSys;

		if(!dev->load[i].alive) continue;	//负荷未投运，则不统计

		if (prior > 0 && prior <= MAX_PRIOR){
			prior <= 40 ? under40 = true : under40 = false;
			//联网情况
			dev->p_all_kq += p;
			dev->p_prior_s1s2[prior-1] += p;
			under40 == true ? dev->p_40_kq += p: dev->p_40_kq += 0.0;

			//处于系统1
			if (uSys == 1){
				dev->p_all_kq_s1 += p;
				dev->p_prior_s1[prior-1] += p;
				under40 == true ? dev->p_40_kq_s1 += p: dev->p_40_kq_s1 += 0.0;
			}else if(uSys == 2){
				dev->p_all_kq_s2 += p;
				dev->p_prior_s2[prior-1] += p;
				under40 == true ? dev->p_40_kq_s2 += p: dev->p_40_kq_s2 += 0.0;
			}else{
				//挂载系统有问题

			}
		}
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
	//float p;
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
			if (p_syl > 0.0){
				cutted[i] = true;
			}else if (p_syl < 0.0){
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
void UpdateCuttedInfo(DEVINFO* dev, int no_sys){

	int prior;
	if (no_sys <= 0) return;
	for (int i = 0; i < LOAD_P_NUM; ++i){
		//负荷未投运不处理
		if (dev->load[i].alive == false) continue;
		//负荷在系统1或系统2中切除，且系统状态不符合则不处理
		if (no_sys < 3){
			if (dev->load[i].onWhichSys != no_sys) continue;
		}

		prior = dev->load[i].prior;
		if (dev->cutted_prior[prior - 1]){
			dev->load[i].beCutted = true;
		}
	}
	return;
}

//输出负荷切除信息
void ExportLoadOutput(DEVINFO* dev){
	for (int i = 0; i < LOAD_P_NUM; ++i){
		dev->LoadOutput[i].fun_num = dev->load[i].fun;
		dev->LoadOutput[i].inf_num = dev->load[i].inf;
		dev->LoadOutput[i].cutted = dev->load[i].beCutted;

		dev->load[i].beCutted = false;//输出负荷切除信息后，清空为下一次策略计算做准备
	}
//	dev->tac.data = dev->LoadOutput;
	dev->tac.data_num = LOAD_P_NUM;

	//输出切除信息
//	func_send(&(dev->tac), 1, env_send);

	return;
}

//策略1动作逻辑
int RUN_TAC_NO1(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql;
	xql = dev->P9591 - dev->P9572;
	stat_action_200ms = ((dev->HWJ9591 || dev->HWJ9592) ||
		((dev->HWJ9571 == 0) && (dev->HWJ9571 || dev->HWJ9572))) 
		&& dev->Conn_S2;
	if (stat_action_200ms && xql > 0.0){
		//更新策略输出部分参数
		dev->tac.tac_num = 1;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq_s1;
		//计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior_s1, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//更新负荷切除信息
		UpdateCuttedInfo(dev, 1);
		//输出策略结果
		ExportLoadOutput(dev);
	}

	return triggered;
}

//策略2动作逻辑
int RUN_TAC_NO2(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql;
	xql = dev->P9561 - dev->P9572;
	stat_action_200ms = (dev->HWJ9561 || dev->HWJ9572) && dev->Conn_S2;
	if (stat_action_200ms && xql > 0.0){
		//更新策略输出部分参数
		dev->tac.tac_num = 2;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq_s1;
		//计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior_s1, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//更新负荷切除信息
		UpdateCuttedInfo(dev, 1);
		//输出策略结果
		ExportLoadOutput(dev);
	}

	return triggered;
}

//策略3动作逻辑
int RUN_TAC_NO3(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql;
	xql = dev->P9592 + dev->P9572;
	stat_action_200ms = ((dev->HWJ9592 || dev->HWJ9572) || ((dev->HWJ9571 == 0) && (dev->HWJ9512 || dev->HWJ9572))) && dev->Conn_S1;
	if (stat_action_200ms && xql > 0.0){
		//更新策略输出部分参数
		dev->tac.tac_num = 3;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq_s2;
		//计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior_s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//更新负荷切除信息
		UpdateCuttedInfo(dev, 2);
		//输出策略结果
		ExportLoadOutput(dev);
	}

	return triggered;
}

//策略4动作逻辑
int RUN_TAC_NO4(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql;
	xql = dev->P9562 + dev->P9572;
	stat_action_200ms = (dev->HWJ9562 || dev->HWJ9572) && dev->Conn_S1;
	if (stat_action_200ms && xql > 0.0){
		//更新策略输出部分参数
		dev->tac.tac_num = 4;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq_s2;
		//计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior_s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//更新负荷切除信息
		UpdateCuttedInfo(dev, 2);
		//输出策略结果
		ExportLoadOutput(dev);
	}

	return triggered;
}

//策略5动作逻辑
int RUN_TAC_NO5(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action_200ms1 = false;
	float xql, xql1, xql2;
	stat_action_200ms = (dev->HWJ9511 || dev->HWJ9591) && (dev->HWJ9512 || dev->HWJ9592);
	stat_action_200ms1 = (dev->HWJ9511 && dev->HWJ9591) && (dev->HWJ9512 && dev->HWJ9592);
	if (stat_action_200ms1 && dev->HWJ9572 == 0){//9572停运
		xql1 = dev->P9591 - dev->P9572;
		xql2 = dev->P9592 + dev->P9572;
		//更新策略输出部分参数
		dev->tac.tac_num = 5;
		dev->tac.tac_yq = xql1 + xql2;
		dev->tac.tac_kq = dev->p_all_kq;
		//系统1计算负荷切除信息
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior_s1, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统1更新负荷切除信息
		UpdateCuttedInfo(dev, 1);

		//系统2计算负荷切除信息
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior_s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统2更新负荷切除信息
		UpdateCuttedInfo(dev, 2);

		//输出策略结果
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572运行
		xql = dev->P9591 + dev->P9592;
		//更新策略输出部分参数
		dev->tac.tac_num = 5;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq;
		//全网计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior_s1s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//全网更新负荷切除信息
		UpdateCuttedInfo(dev, 3);


		//输出策略结果
		ExportLoadOutput(dev);

	}

	return triggered;
}

//策略6动作逻辑
int RUN_TAC_NO6(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action_200ms1 = false;
	float xql, xql1, xql2;
	stat_action_200ms = ((dev->HWJ9591 || dev->HWJ9562) || ((dev->HWJ9571 == 0) && (dev->HWJ9511 || dev->HWJ9562))) && dev->HWJ9561;
	stat_action_200ms1 = ((dev->HWJ9591 && dev->HWJ9562) || ((dev->HWJ9571 == 0) && (dev->HWJ9511 && dev->HWJ9562))) && dev->HWJ9561;
	if (stat_action_200ms1 && dev->HWJ9572 == 0){//9572停运
		xql1 = dev->P9591 - dev->P9572;
		xql2 = dev->P9562 + dev->P9572;
		//更新策略输出部分参数
		dev->tac.tac_num = 6;
		dev->tac.tac_yq = xql1 + xql2;
		dev->tac.tac_kq = dev->p_all_kq;
		//系统1计算负荷切除信息
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior_s1, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统1更新负荷切除信息
		UpdateCuttedInfo(dev, 1);

		//系统2计算负荷切除信息
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior_s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统2更新负荷切除信息
		UpdateCuttedInfo(dev, 2);

		//输出策略结果
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572运行
		xql = dev->P9591 + dev->P9592;
		//更新策略输出部分参数
		dev->tac.tac_num = 6;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq;
		//全网计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior_s1s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//全网更新负荷切除信息
		UpdateCuttedInfo(dev, 3);


		//输出策略结果
		ExportLoadOutput(dev);

	}

	return triggered;
}

//策略7动作逻辑
int RUN_TAC_NO7(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action_200ms1 = false;
	float xql, xql1, xql2;
	stat_action_200ms = ((dev->HWJ9592 || dev->HWJ9561) || ((dev->HWJ9571 == 0) && (dev->HWJ9512 || dev->HWJ9561))) && dev->HWJ9562;
	stat_action_200ms1 = ((dev->HWJ9592 && dev->HWJ9561) || ((dev->HWJ9571 == 0) && (dev->HWJ9512 && dev->HWJ9561))) && dev->HWJ9562;
	if (stat_action_200ms1 && dev->HWJ9572 == 0){//9572停运
		xql1 = dev->P9561 - dev->P9572;
		xql2 = dev->P9592 + dev->P9572;
		//更新策略输出部分参数
		dev->tac.tac_num = 7;
		dev->tac.tac_yq = xql1 + xql2;
		dev->tac.tac_kq = dev->p_all_kq;
		//系统1计算负荷切除信息
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior_s1, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统1更新负荷切除信息
		UpdateCuttedInfo(dev, 1);

		//系统2计算负荷切除信息
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior_s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统2更新负荷切除信息
		UpdateCuttedInfo(dev, 2);

		//输出策略结果
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572运行
		xql = dev->P9592 + dev->P9561;
		//更新策略输出部分参数
		dev->tac.tac_num = 7;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq;
		//全网计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior_s1s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//全网更新负荷切除信息
		UpdateCuttedInfo(dev, 3);


		//输出策略结果
		ExportLoadOutput(dev);

	}

	return triggered;
}

//策略8动作逻辑
int RUN_TAC_NO8(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action_200ms1 = false;
	float xql, xql1, xql2;
	stat_action_200ms = (dev->HWJ9561 || dev->HWJ9562);
	stat_action_200ms1 = (dev->HWJ9561 && dev->HWJ9562);
	if (stat_action_200ms1 && (dev->HWJ9572 == 0)){//9572停运
		xql1 = dev->P9561 - dev->P9572;
		xql2 = dev->P9562 + dev->P9572;
		//更新策略输出部分参数
		dev->tac.tac_num = 8;
		dev->tac.tac_yq = xql1 + xql2;
		dev->tac.tac_kq = dev->p_all_kq;
		//系统1计算负荷切除信息
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior_s1, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统1更新负荷切除信息
		UpdateCuttedInfo(dev, 1);

		//系统2计算负荷切除信息
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior_s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统2更新负荷切除信息
		UpdateCuttedInfo(dev, 2);

		//输出策略结果
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572运行
		xql = dev->P9562 + dev->P9561;
		//更新策略输出部分参数
		dev->tac.tac_num = 8;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq;
		//全网计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior_s1s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//全网更新负荷切除信息
		UpdateCuttedInfo(dev, 3);


		//输出策略结果
		ExportLoadOutput(dev);

	}

	return triggered;
}


//动态库策略模拟函数
void run_tac_simulate(){

//	DEVINFO devdata;
	//1. 初始化
	Initialize(&devdata);
	//2. 读取数据
	ReadDevInfo(&devdata);
	//3. 处理负荷信息
	HandleLoadSys(&devdata);	
	CalLoadPByPrior(&devdata);

	//4. 策略计算
	RUN_TAC_NO1(&devdata);
	RUN_TAC_NO2(&devdata);
	RUN_TAC_NO3(&devdata);
	RUN_TAC_NO4(&devdata);
	RUN_TAC_NO5(&devdata);
	RUN_TAC_NO6(&devdata);
	RUN_TAC_NO7(&devdata);
	RUN_TAC_NO8(&devdata);
    unsigned char p = 34;
    printf("p = %d", p);
    for(int i = 0;i < SYS_P_NUM;i++){
        printf("fun = %d, inf = %d, value = %f\n", devdata.Sys_P[i].fun_num, devdata.Sys_P[i].inf_num, devdata.Sys_P[i].value);
    }

	return;
}


