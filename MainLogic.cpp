#include <string.h>
#include "systac.h"
#include "DeviceSet.h"
#include "DeviceDef.h"

#ifdef _DEBUG
#include "TestCase.h"
#include <fstream>
#include <iostream>
using namespace std;
#endif

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
	return;
}
//读取装置信息
void ReadDevInfo(DEVINFO* dev){

#ifndef _DEBUG
	//读取系统模拟量信息
	func_read(SHZZ,dev->Sys_P, SYS_P_NUM, env_read);
	//读取负荷信息
	func_read(SHZZ,dev->Load_P, LOAD_P_NUM, env_read);
	//读取优先级定值
	func_read(SHZZ,dev->Load_Prior, LOAD_P_NUM+1, env_read);
	//读取系统连接状态
	func_read(SHZZ,dev->Load_Conn, LOAD_CONN_NUM, env_read);
	//读取系统开关运行状态
	func_read(SHZZ,dev->Sys_Stat, SYS_STAT_NUM, env_read);

	//开关站读取信息
	func_read(KGZ,dev->Load_Conn_KGZ, LINE_NUM_KGZ, env_read);
	//二空压读取信息
	func_read(EKY,dev->Load_Conn_EKY, LINE_NUM_EKY, env_read);
	//三催化读取信息
	func_read(CH3,dev->Load_Conn_CH3, LINE_NUM_CH3, env_read);
	//四催化读取信息
	func_read(CH4,dev->Load_Conn_CH4, LINE_NUM_CH4, env_read);
	//石化子读取信息
	func_read(SHZ,dev->Load_Conn_SHZ, LINE_NUM_SHZ, env_read);


#else
	//从文件中读取系统状态
	bool res = ReadTestCaseFile(std::string("C:\\Users\\zhengh.NR-RD\\Desktop\\大连石化项目\\XDC.sta"), std::string("C:\\Users\\zhengh.NR-RD\\Desktop\\大连石化项目\\XDC.set"), dev);
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
	dev->P_HZX_1 = dev->Sys_P[7].value;
	dev->P_HZX_2 = dev->Sys_P[8].value;
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
	dev->HWJ9571 = uint8(dev->Load_Conn_SHZ[0].value) == 0 ? 1 : 0;

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
#ifdef _DEBUG
				cout << "load_no: " << i + 1 << " " << p << " " << int(uSys) << " " << int(prior) << " " << int(vl) << endl;
#endif

			//处于系统1下
			if (uSys == 0x1){
				dev->p_all_kq_s1 += p;
				under40 == true ? dev->p_40_kq_s1 += p: dev->p_40_kq_s1 += 0.0;
				//统计系统1下66kV负荷
				if (vl == 2){
					dev->p_kq_s1_66 += p;
					under40 == true ? dev->p_40_kq_s1_66 += p: dev->p_40_kq_s1_66 += 0.0;
				}
			}
			//处于系统2下
			if(uSys == 0x2){
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
		if ((dev->load[i].onWhichSys != sys) || ((dev->load[i].voltagelevel & vl) == 0x0)){
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
		if ((no_sys == dev->load[i].onWhichSys) && ((vl & dev->load[i].voltagelevel)!= 0x0)){
			prior = dev->load[i].prior;
			if (dev->cutted_prior[prior - 1]){
				dev->load[i].beCutted = true;
			}
		}
	}
	return;
}


//输出负荷切除信息
void ExportLoadOutput(DEVINFO* dev){
	float pcutted = 0.0;//负荷切除量
	uint8 ncutted = 0;//负荷切除个数
	for (int i = 0; i < LOAD_P_NUM + 4; ++i){
		dev->LoadOutput[i].fun_num = dev->load[i].fun;
		dev->LoadOutput[i].inf_num = dev->load[i].inf;
		dev->LoadOutput[i].cutted = dev->load[i].beCutted;
		if (dev->LoadOutput[i].cutted){
			pcutted += dev->load[i].pload;
			ncutted++;
		}
	}
	dev->tac.data = dev->LoadOutput;
	dev->tac.data_num = LOAD_P_NUM + 4;
	dev->tac.tac_pcutted = pcutted;
	dev->tac.tac_ncutted = ncutted;

#ifndef _DEBUG
	//输出切除信息
	func_send(SHZZ,&(dev->tac), 1, env_send);
#else
	bool res = SendTacFile(std::string(".\\tacoutfile.txt"), dev);
	if (!res){
		std::cout<< "Error: Failed to SendTacFile!" << endl;
	}
#endif

	return;
}
//首先切除化机双线，华总双线
float CutHJZXFirst(DEVINFO* dev, uint8 sys){
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
int RUN_TAC_NO1(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql, hjz;
	xql = dev->P9591 - dev->P9572;
	stat_action_200ms = ((dev->HWJ9591 || dev->HWJ9592) ||
		((dev->HWJ9571 == 0) && (dev->HWJ9511 || dev->HWJ9572))) 
		&& dev->Conn_S2;
	if (stat_action_200ms && xql > 0.0){
		//更新策略输出部分参数
//		dev->tac.tac_num = 1;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 1);

		strcpy(dev->tac.tac_num, "1-1");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq_s1 + hjz;
		
		xql -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 1, 3);
		//计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//更新负荷切除信息
		UpdateCuttedInfo(dev, 1, 3);
		//输出策略结果
		ExportLoadOutput(dev);
	}

	return triggered;
}

//策略2动作逻辑
int RUN_TAC_NO2(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql, hjz;
	xql = dev->P9561 - dev->P9572;

	stat_action_200ms = (dev->HWJ9561 || dev->HWJ9572) && dev->Conn_S2;
	if (stat_action_200ms && xql > 0.0){
		//更新策略输出部分参数
//		dev->tac.tac_num = 2;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev,1);

		strcpy(dev->tac.tac_num, "2-1");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_kq_s1_66 + hjz;

		xql -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 1, 2);
		//计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_kq_s1_66, dev->p_40_kq_s1_66, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//更新负荷切除信息
		UpdateCuttedInfo(dev, 1, 2);
		//输出策略结果
		ExportLoadOutput(dev);
	}

	return triggered;
}

//策略3动作逻辑
int RUN_TAC_NO3(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql, hjz;
	xql = dev->P9592 + dev->P9572;

	stat_action_200ms = ((dev->HWJ9592 || dev->HWJ9572) || ((dev->HWJ9571 == 0) && (dev->HWJ9512 || dev->HWJ9572))) && dev->Conn_S1;
	if (stat_action_200ms && xql > 0.0){
		//更新策略输出部分参数
		ClearCuttedTag(dev);
//		dev->tac.tac_num = 3;
		hjz = CutHJZXFirst(dev,  2);

		strcpy(dev->tac.tac_num, "3-1");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq_s2 + hjz;

		xql -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 2, 3);
		//计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//更新负荷切除信息
		UpdateCuttedInfo(dev, 2, 3);
		//输出策略结果
		ExportLoadOutput(dev);
	}

	return triggered;
}

//策略4动作逻辑
int RUN_TAC_NO4(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql, hjz;
	xql = dev->P9562 + dev->P9572;

	stat_action_200ms = (dev->HWJ9562 || dev->HWJ9572) && dev->Conn_S1;
	if (stat_action_200ms && xql > 0.0){
		//更新策略输出部分参数
//		dev->tac.tac_num = 4;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 2);

		strcpy(dev->tac.tac_num, "4-1");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_kq_s2_66 + hjz;

		xql -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 2, 2);
		//计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//更新负荷切除信息
		UpdateCuttedInfo(dev, 2, 2);
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
	float xql, xql1, xql2, hjz;
	stat_action_200ms = (dev->HWJ9511 || dev->HWJ9591) && (dev->HWJ9512 || dev->HWJ9592);
	stat_action_200ms1 = (dev->HWJ9511 && dev->HWJ9591) && (dev->HWJ9512 && dev->HWJ9592);
	if (stat_action_200ms1 && dev->HWJ9572 == 0){//9572停运
		xql1 = dev->P9591 - dev->P9572;
		xql2 = dev->P9592 + dev->P9572;
		//更新策略输出部分参数
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 1);
//		dev->tac.tac_num = 5;
		strcpy(dev->tac.tac_num, "5-1");
		dev->tac.tac_yq = xql1;
		dev->tac.tac_kq = dev->p_all_kq_s1 + hjz;

		xql1 -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 1, 3);
		//系统1计算负荷切除信息
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统1更新负荷切除信息
		UpdateCuttedInfo(dev, 1, 3);
		//输出系统1切负荷信息 
		ExportLoadOutput(dev);

		//系统2故障
		ClearCuttedTag(dev);
		hjz = CutHJZXFirst(dev, 2);
		strcpy(dev->tac.tac_num, "5-2");
		dev->tac.tac_yq = xql2;
		dev->tac.tac_kq = dev->p_all_kq_s2 + hjz;

		xql2 -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 2, 3);
		//系统2计算负荷切除信息
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统2更新负荷切除信息
		UpdateCuttedInfo(dev, 2, 3);
		//输出策略结果
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572运行
		xql = dev->P9591 + dev->P9592;
		//更新策略输出部分参数
//		dev->tac.tac_num = 5;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 3);

		strcpy(dev->tac.tac_num, "5-3");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq + hjz;

		xql -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 3, 3);
		//全网计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//全网更新负荷切除信息
		UpdateCuttedInfo(dev, 3, 3);
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
	float xql, xql1, xql2, hjz;
	stat_action_200ms = ((dev->HWJ9591 || dev->HWJ9562) || ((dev->HWJ9571 == 0) && (dev->HWJ9511 || dev->HWJ9562))) && dev->HWJ9561;
	stat_action_200ms1 = ((dev->HWJ9591 && dev->HWJ9562) || ((dev->HWJ9571 == 0) && (dev->HWJ9511 && dev->HWJ9562))) && dev->HWJ9561;
	if (stat_action_200ms1 && dev->HWJ9572 == 0){//9572停运
		xql1 = dev->P9591 - dev->P9572;
		xql2 = dev->P9562 + dev->P9572;
		//更新策略输出部分参数
//		dev->tac.tac_num = 6;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 1);
		strcpy(dev->tac.tac_num, "6-1");
		dev->tac.tac_yq = xql1;
		dev->tac.tac_kq = dev->p_all_kq_s1 + hjz;

		xql1 -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 1, 3);
		//系统1计算负荷切除信息
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统1更新负荷切除信息
		UpdateCuttedInfo(dev, 1, 3);
		//输出策略结果
		ExportLoadOutput(dev);
		
		//系统2故障
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 2);
		strcpy(dev->tac.tac_num, "6-2");
		dev->tac.tac_yq = xql2;
		dev->tac.tac_kq = dev->p_all_kq_s2 + hjz;
		xql2 -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 2, 2);
		//系统2计算负荷切除信息
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统2更新负荷切除信息
		UpdateCuttedInfo(dev, 2, 2);
		//输出策略结果
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572运行
		xql = dev->P9591 + dev->P9592;
		//更新策略输出部分参数
//		dev->tac.tac_num = 6;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 3);
		strcpy(dev->tac.tac_num, "6-3");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 3, 3);
		//全网计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//全网更新负荷切除信息
		UpdateCuttedInfo(dev, 3, 3);


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
	float xql, xql1, xql2, hjz;
	stat_action_200ms = ((dev->HWJ9592 || dev->HWJ9561) || ((dev->HWJ9571 == 0) && (dev->HWJ9512 || dev->HWJ9561))) && dev->HWJ9562;
	stat_action_200ms1 = ((dev->HWJ9592 && dev->HWJ9561) || ((dev->HWJ9571 == 0) && (dev->HWJ9512 && dev->HWJ9561))) && dev->HWJ9562;
	if (stat_action_200ms1 && dev->HWJ9572 == 0){//9572停运
		xql1 = dev->P9561 - dev->P9572;
		xql2 = dev->P9592 + dev->P9572;
		//更新策略输出部分参数
//		dev->tac.tac_num = 7;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 1);
		strcpy(dev->tac.tac_num, "7-1");
		dev->tac.tac_yq = xql1;
		dev->tac.tac_kq = dev->p_all_kq_s1 + hjz;
		xql1 -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 2, 3);
		//系统1计算负荷切除信息
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统1更新负荷切除信息
		UpdateCuttedInfo(dev, 1, 3);
		//输出策略结果
		ExportLoadOutput(dev);

		//系统2故障
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 2);
		strcpy(dev->tac.tac_num, "7-2");
		dev->tac.tac_yq = xql2;
		dev->tac.tac_kq = dev->p_all_kq_s2 + hjz;
		xql2 -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 1, 2);
		//系统2计算负荷切除信息
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统2更新负荷切除信息
		UpdateCuttedInfo(dev, 2, 2);
		//输出策略结果
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572运行
		xql = dev->P9592 + dev->P9561;
		//更新策略输出部分参数
//		dev->tac.tac_num = 7;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 1);
		strcpy(dev->tac.tac_num, "7-3");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 3, 3);
		//全网计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//全网更新负荷切除信息
		UpdateCuttedInfo(dev, 3, 3);


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
	float xql, xql1, xql2, hjz;
	stat_action_200ms = (dev->HWJ9561 || dev->HWJ9562);
	stat_action_200ms1 = (dev->HWJ9561 && dev->HWJ9562);
	if (stat_action_200ms1 && (dev->HWJ9572 == 0)){//9572停运
		xql1 = dev->P9561 - dev->P9572;
		xql2 = dev->P9562 + dev->P9572;
		//更新策略输出部分参数
//		dev->tac.tac_num = 8;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 1);
		strcpy(dev->tac.tac_num, "8-1");
		dev->tac.tac_yq = xql1;
		dev->tac.tac_kq = dev->p_all_kq_s1 + hjz;
		xql1 -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 1, 2);
		//系统1计算负荷切除信息
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统1更新负荷切除信息
		UpdateCuttedInfo(dev, 1, 2);
		//输出策略结果
		ExportLoadOutput(dev);

		//系统2故障
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 1);
		strcpy(dev->tac.tac_num, "8-2");
		dev->tac.tac_yq = xql2;
		dev->tac.tac_kq = dev->p_all_kq_s2 + hjz;
		xql2 -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 2, 2);
		//系统2计算负荷切除信息
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//系统2更新负荷切除信息
		UpdateCuttedInfo(dev, 2, 2);

		//输出策略结果
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572运行
		xql = dev->P9562 + dev->P9561;
		//更新策略输出部分参数
//		dev->tac.tac_num = 8;
		ClearCuttedTag(dev);
		//先切除化机双线、华总双线
		hjz = CutHJZXFirst(dev, 1);
		strcpy(dev->tac.tac_num, "8-3");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql -= hjz;
		//形成优先级负荷信息
		CalLoadInfoByPrior(dev, 3, 2);
		//全网计算负荷切除信息
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//全网更新负荷切除信息
		UpdateCuttedInfo(dev, 3, 2);
		//输出策略结果
		ExportLoadOutput(dev);

	}

	return triggered;
}


//动态库策略模拟函数
void run_tac_simulate(){

	//1. 初始化
	Initialize(&devdata);
	//2. 读取数据
	ReadDevInfo(&devdata);
	//3. 处理负荷信息
	HandleLoadSys(&devdata);	
	CalLoadStatics(&devdata);

	//4. 策略计算
	//RUN_TAC_NO1(&devdata);
	//RUN_TAC_NO2(&devdata);
	//RUN_TAC_NO3(&devdata);
	RUN_TAC_NO4(&devdata);
	
	exit(0);
	RUN_TAC_NO5(&devdata);
	RUN_TAC_NO6(&devdata);
	RUN_TAC_NO7(&devdata);
	RUN_TAC_NO8(&devdata);

	return;
}


