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


//����ȫ�ֱ���
static DEVINFO       devdata;	
static FAULTINFO	 faultdata;
static DATA_HANDLER  func_read;
static void*         env_read;
static TAC_HANDLER   func_send;
static void*         env_send;

//����ص�����
void data_register(DATA_HANDLER data_handler,void *env){
	func_read = data_handler;
	env_read = env;
#ifdef _LOG
	printf("Log[func data_register]: data_handle = %x, env = %x\n", func_read, env_read);
#endif
	return;
}
//����ص�����
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

	printf("������Ϣ:\n");
	for (int i = 0;i < LOAD_P_NUM+4;i++){
		printf("no = %d, fun = %d,inf = %d, pload = %f, prior = %d, sys = %d, alive = %d, vl = %d\n",
			   i, dev->load[i].fun, dev->load[i].inf, dev->load[i].pload, dev->load[i].prior, dev->load[i].onWhichSys,
			   dev->load[i].alive, dev->load[i].voltagelevel);
	}
	printf("Ƶ��Ƿ�п��ƶ�ֵ = %f\n", dev->p_qq_setting);

	return;
}

//��ʼ��
void Initialize(DEVINFO* dev, FAULTINFO* fault){
	//ϵͳģ����
	for (int i = 0; i < SYS_P_NUM; ++i){
		dev->Sys_P[i].fun_num = FUN_SYS_P[i];
		dev->Sys_P[i].inf_num = INF_SYS_P[i];
		dev->Sys_P[i].value = 0;
	}
	//��������
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

	//ϵͳ����״̬��
	for (int i = 0; i < LOAD_CONN_NUM; ++i){
		dev->Load_Conn[i].fun_num = FUN_LOAD_CONN[i];
		dev->Load_Conn[i].inf_num = INF_LOAD_CONN[i];
		dev->Load_Conn[i].value = 0;
	}
	//ϵͳ����״̬
	for (int i = 0; i < SYS_STAT_NUM; ++i){
		dev->Sys_Stat[i].fun_num = FUN_SYS_STAT[i];
		dev->Sys_Stat[i].inf_num = INF_SYS_STAT[i];
		dev->Sys_Stat[i].value = 0;
	}

	//����վ��Ϣ
	for (int i = 0;i < LINE_NUM_KGZ;++i){
		dev->Load_Conn_KGZ[i].fun_num = FUN_KGZ_LOAD[i];
		dev->Load_Conn_KGZ[i].inf_num = INF_KGZ_LOAD[i];
		dev->Load_Conn_KGZ[i].value = 0;
	}

	//����ѹ��Ϣ
	for (int i = 0;i < LINE_NUM_EKY;++i){
		dev->Load_Conn_EKY[i].fun_num = FUN_EKY_LOAD[i];
		dev->Load_Conn_EKY[i].inf_num = INF_EKY_LOAD[i];
		dev->Load_Conn_EKY[i].value = 0;
	}

	//���߻���Ϣ
	for (int i = 0;i < LINE_NUM_CH3;++i){
		dev->Load_Conn_CH3[i].fun_num = FUN_CH3_LOAD[i];
		dev->Load_Conn_CH3[i].inf_num = INF_CH3_LOAD[i];
		dev->Load_Conn_CH3[i].value = 0;
	}
	//�Ĵ߻���Ϣ
	for (int i = 0;i < LINE_NUM_CH4;++i){
		dev->Load_Conn_CH4[i].fun_num = FUN_CH4_LOAD[i];
		dev->Load_Conn_CH4[i].inf_num = INF_CH4_LOAD[i];
		dev->Load_Conn_CH4[i].value = 0;
	}

	//ʯ����վ��Ϣ
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

	//��ʼ��������Ϣ
	InitializeFault(fault);
	//��ʼ������������
	//InitializeTacOutput(dev);
	return;
}
//��ȡװ����Ϣ
void ReadDevInfo(DEVINFO* dev, FAULTINFO* fault){

#ifndef _DEBUG
	//��ȡϵͳģ������Ϣ
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Sys_p stcode = %s, InputItem = %x, data_num = %d\n", SHZZ, dev->Sys_P, SYS_P_NUM);
	LogFuncReadInfo(dev->Sys_P, SYS_P_NUM);
#endif
	func_read(SHZZ,dev->Sys_P, SYS_P_NUM, env_read);

	//��ȡ������Ϣ
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_P stcode = %s, InputItem = %x, data_num = %d\n", SHZZ, dev->Load_P, LOAD_P_NUM);
	LogFuncReadInfo(dev->Load_P, LOAD_P_NUM);
#endif
	func_read(SHZZ,dev->Load_P, LOAD_P_NUM, env_read);


	//��ȡ���ȼ���ֵ
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_Prior stcode = %s, InputItem = %x, data_num = %d\n", SHZZ, dev->Load_Prior, LOAD_P_NUM+1);
	LogFuncReadInfo(dev->Load_Prior, LOAD_P_NUM+1);
#endif
	func_read(SHZZ,dev->Load_Prior, LOAD_P_NUM+1, env_read);


	//��ȡϵͳ����״̬
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_Conn stcode = %s, InputItem = %x, data_num = %d\n", SHZZ, dev->Load_Conn, LOAD_CONN_NUM);
	LogFuncReadInfo(dev->Load_Conn, LOAD_CONN_NUM);
#endif
	func_read(SHZZ,dev->Load_Conn, LOAD_CONN_NUM, env_read);

	//��ȡϵͳ��������״̬
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Sys_Stat before stcode = %s, InputItem = %x, data_num = %d\n", SHZZ, dev->Sys_Stat, SYS_STAT_NUM);
	LogFuncReadInfo(dev->Sys_Stat, SYS_STAT_NUM);
#endif
	func_read(SHZZ,dev->Sys_Stat, SYS_STAT_NUM, env_read);
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Sys_Stat after stcode = %s, InputItem = %x, data_num = %d\n", SHZZ, dev->Sys_Stat, SYS_STAT_NUM);
	LogFuncReadInfo(dev->Sys_Stat, SYS_STAT_NUM);
#endif



	//����վ��ȡ��Ϣ
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_Conn_KGZ stcode = %s, InputItem = %x, data_num = %d\n", KGZ, dev->Load_Conn_KGZ, LINE_NUM_KGZ);
	LogFuncReadInfo(dev->Load_Conn_KGZ, LINE_NUM_KGZ);
#endif
	func_read(KGZ,dev->Load_Conn_KGZ, LINE_NUM_KGZ, env_read);


	//����ѹ��ȡ��Ϣ
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_Conn_EKY stcode = %s, InputItem = %x, data_num = %d\n", EKY, dev->Load_Conn_EKY, LINE_NUM_EKY);
	LogFuncReadInfo(dev->Load_Conn_EKY, LINE_NUM_EKY);
#endif
	func_read(EKY,dev->Load_Conn_EKY, LINE_NUM_EKY, env_read);

	//���߻���ȡ��Ϣ
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_Conn_CH3 stcode = %s, InputItem = %x, data_num = %d\n", CH3, dev->Load_Conn_CH3, LINE_NUM_CH3);
	LogFuncReadInfo(dev->Load_Conn_CH3, LINE_NUM_CH3);
#endif
	func_read(CH3,dev->Load_Conn_CH3, LINE_NUM_CH3, env_read);

	//�Ĵ߻���ȡ��Ϣ
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_Conn_CH4 stcode = %s, InputItem = %x, data_num = %d\n", CH4, dev->Load_Conn_CH4, LINE_NUM_CH4);
	LogFuncReadInfo(dev->Load_Conn_CH4, LINE_NUM_CH4);
#endif
	func_read(CH4,dev->Load_Conn_CH4, LINE_NUM_CH4, env_read);

	//ʯ���Ӷ�ȡ��Ϣ
#ifdef _LOG
	printf("Log[func ReadDevInfo]: Load_Conn_SHZ stcode = %s, InputItem = %x, data_num = %d\n", SHZ, dev->Load_Conn_SHZ, LINE_NUM_SHZ);
	LogFuncReadInfo(dev->Load_Conn_SHZ, LINE_NUM_SHZ);
#endif
	func_read(SHZ,dev->Load_Conn_SHZ, LINE_NUM_SHZ, env_read);

	//������Ϣ�ӿڱ���

#else
	//���ļ��ж�ȡϵͳ״̬
//	bool res = ReadTestCaseFile(std::string("C:\\Users\\zhengh.NR-RD\\Desktop\\����ʯ����Ŀ\\XDC.sta"), std::string("C:\\Users\\zhengh.NR-RD\\Desktop\\����ʯ����Ŀ\\XDC.set"), dev, fault);
	bool res = ReadTestCaseFile(std::string("./tmp/XDC.sta"), std::string("./tmp/XDC.set"), dev, fault);
	if (!res){
		std::cout << "Error: Failed to ReadTestCaseFile!" << endl;
		exit(0);
	}
#endif

	//��������Ԥ����
	dev->P9591 = dev->Sys_P[0].value;
	dev->P9561 = dev->Sys_P[1].value;
	dev->P9592 = dev->Sys_P[2].value;
	dev->P9562 = dev->Sys_P[3].value;
	dev->P9572 = dev->Sys_P[4].value;
	dev->P_HJX_1 = dev->Sys_P[5].value;
	dev->P_HJX_2 = dev->Sys_P[6].value;
	dev->P_HZX_1 = dev->Sys_P[8].value;
	dev->P_HZX_2 = dev->Sys_P[7].value;
	//ϵͳ����״̬Ԥ����
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

	//9571������Ϣ
	dev->HWJ9571 = uint8(dev->Load_Conn_SHZ[0].value);

	//�������ݴ���
	dev->p_qq_setting = dev->Load_Prior[LOAD_P_NUM].value;//Ƶ��Ƿ�й��ʶ�ֵ
	//������Ϣ
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
	//����һ��
	dev->load[LOAD_P_NUM + 0].fun = dev->Sys_P[5].fun_num;
	dev->load[LOAD_P_NUM + 0].inf = dev->Sys_P[5].inf_num;
	dev->load[LOAD_P_NUM + 0].pload = dev->Sys_P[5].value;
	dev->load[LOAD_P_NUM + 0].prior = 0;
	dev->load[LOAD_P_NUM + 0].onWhichSys = 1;
	dev->load[LOAD_P_NUM + 0].voltagelevel = 2;
	dev->load[LOAD_P_NUM + 0].beCutted = false;
	dev->load[LOAD_P_NUM + 0].pload < LOAD_ALIVE_P ? dev->load[LOAD_P_NUM + 0].alive = false : dev->load[LOAD_P_NUM + 0].alive = true;
	//��������
	dev->load[LOAD_P_NUM + 1].fun = dev->Sys_P[6].fun_num;
	dev->load[LOAD_P_NUM + 1].inf = dev->Sys_P[6].inf_num;
	dev->load[LOAD_P_NUM + 1].pload = dev->Sys_P[6].value;
	dev->load[LOAD_P_NUM + 1].prior = 0;
	dev->load[LOAD_P_NUM + 1].onWhichSys = 2;
	dev->load[LOAD_P_NUM + 1].voltagelevel = 2;
	dev->load[LOAD_P_NUM + 1].beCutted = false;
	dev->load[LOAD_P_NUM + 1].pload < LOAD_ALIVE_P ? dev->load[LOAD_P_NUM + 1].alive = false : dev->load[LOAD_P_NUM + 1].alive = true;

	//����һ��
	dev->load[LOAD_P_NUM + 2].fun = dev->Sys_P[7].fun_num;
	dev->load[LOAD_P_NUM + 2].inf = dev->Sys_P[7].inf_num;
	dev->load[LOAD_P_NUM + 2].pload = dev->Sys_P[7].value;
	dev->load[LOAD_P_NUM + 2].prior = 0;
	dev->load[LOAD_P_NUM + 2].onWhichSys = 1;
	dev->load[LOAD_P_NUM + 2].voltagelevel = 2;
	dev->load[LOAD_P_NUM + 2].beCutted = false;
	dev->load[LOAD_P_NUM + 2].pload < LOAD_ALIVE_P ? dev->load[LOAD_P_NUM + 2].alive = false : dev->load[LOAD_P_NUM + 2].alive = true;

	//���ܶ���
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
//�����ɹ���ϵͳ״̬
void HandleLoadSys(DEVINFO* dev){
#ifdef _LOG
	cout << "Log[func HandleLoadSys]: running HandleLoadSys" << endl;
#endif
	uint8 temp, index;
	uint8 stat1, stat2;

	//����վ������Ϣ
	for (int i = 0;i < LINE_NUM_KGZ;++i){
		temp = uint8(dev->Load_Conn_KGZ[i].value);
		stat1 = temp & 0x1;
		stat2 = temp & 0x2;
		dev->load[i].onWhichSys = stat1 + stat2;
		dev->load[i].voltagelevel = 2;
	}
	//����ѹ������Ϣ
	for (int i = 0;i < LINE_NUM_EKY;++i){
		temp = uint8(dev->Load_Conn_EKY[i].value);
		stat1 = ((temp & 0x1) & dev->S1_35kV_B1)|(((temp & 0x2)>>1) & dev->S1_35kV_B2);
		stat2 = ((temp & 0x1) & dev->S2_35kV_B1)|(((temp & 0x2)>>1) & dev->S2_35kV_B2);
		dev->load[i + INDEX_EKY].onWhichSys = stat1 + stat2 * 2;
		dev->load[i + INDEX_EKY].voltagelevel = 1;
	}
	//���߻�������Ϣ
	for (int i = 0;i < LINE_NUM_CH3;++i){
		temp = uint8(dev->Load_Conn_CH3[i].value);
		stat1 = ((temp & 0x1) & dev->S1_35kV_B1)|(((temp & 0x2)>>1) & dev->S1_35kV_B2);
		stat2 = ((temp & 0x1) & dev->S2_35kV_B1)|(((temp & 0x2)>>1) & dev->S2_35kV_B2);
		dev->load[i + INDEX_CH3].onWhichSys = stat1 + stat2 * 2;
		dev->load[i + INDEX_CH3].voltagelevel = 1;
	}
	//�Ĵ߻�������Ϣ
	for (int i = 0;i < LINE_NUM_CH4;++i){
		temp = uint8(dev->Load_Conn_CH4[i].value);
		stat1 = ((temp & 0x1) & dev->S1_35kV_B1)|(((temp & 0x2)>>1) & dev->S1_35kV_B2);
		stat2 = ((temp & 0x1) & dev->S2_35kV_B1)|(((temp & 0x2)>>1) & dev->S2_35kV_B2);
 		dev->load[i + INDEX_CH4].onWhichSys = stat1 + stat2 * 2;
		dev->load[i + INDEX_CH4].voltagelevel = 1;
	}


	return;
}
//�������ȼ�ͳ�Ƹ��ɹ���
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

	//�������ȼ�ͳ�Ƹ��ɹ���
	for (int i = 0; i < LOAD_P_NUM; ++i){
		p = dev->load[i].pload;
		prior = dev->load[i].prior;
		uSys = dev->load[i].onWhichSys;
		vl = dev->load[i].voltagelevel;

		if(!dev->load[i].alive) continue;	//����δͶ�ˣ���ͳ��

		if (prior > 0 && prior <= MAX_PRIOR){
			prior <= 40 ? under40 = true : under40 = false;
			
			//�������
			dev->p_all_kq += p;
			under40 == true ? dev->p_40_kq += p: dev->p_40_kq += 0.0;

			//ͳ�Ƹ���ϵͳ����ĸ����������Ҫ���ǵ������ǣ�ϵͳ1����������費��Ҫ����ϵͳ12�������ĸ��ɡ�
			//Ŀǰ����ֻ����ȫ������ϵͳ����

			//����ϵͳ1�� -- Ĭ��ͳ��ֻҪ��ϵͳ1���������и��ɣ���onWhichSys = 1 | 3
			if ((uSys & 0x1) != 0x0){
				dev->p_all_kq_s1 += p;
				under40 == true ? dev->p_40_kq_s1 += p: dev->p_40_kq_s1 += 0.0;
				//ͳ��ϵͳ1��66kV����
				if (vl == 2){
					dev->p_kq_s1_66 += p;
					under40 == true ? dev->p_40_kq_s1_66 += p: dev->p_40_kq_s1_66 += 0.0;
				}
			}
			//����ϵͳ2��
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

//����г���־
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

//����Ҫ���γɸ������ȼ���Ϣ
void CalLoadInfoByPrior(DEVINFO* dev, uint8 sys, uint8 vl){
	float p;
	uint8 prior;
	//��ʼ����������
	for (int i = 0;i < MAX_PRIOR;i++){
		dev->p_prior[i] = 0.0;
		dev->cutted_prior[i] = false;
	}
	//��������г���Ϣ
	//ClearCuttedTag(dev);
	//ͳ�Ƹ�����Ϣ
	for (int i = 0;i < LOAD_P_NUM;++i){
		//������Ϊ0�����ȼ�Ϊ0�� ������
		if (!dev->load[i].alive || (dev->load[i].prior <= 0)){
			continue;
		}
		if ((dev->load[i].voltagelevel & vl) == 0x0){//��ѹ�ȼ���ƥ��,���������ȼ�ͳ��
			continue;
		}
		//ϵͳ��Ϣ�й������������ȼ�ͳ��
		if (((dev->load[i].onWhichSys & sys) == 0x0) || (dev->load[i].onWhichSys <= 0) || (dev->load[i].onWhichSys > 3)){
			continue;
		}
		p = dev->load[i].pload;
		prior = dev->load[i].prior;
		dev->p_prior[prior - 1] += p;		
	}
	return;
}

//�����������������������ȼ��г���Ϣ
//	xql:������
//  p_all_kq:ȫϵͳ������
//  p_40_kq: ȫϵͳǰ40���ȼ�������
//  p_prior: �����ȼ����и���
//  cutted:  �����ȼ��г���־
//  size  :  ���ȼ�����
//  qql_set: �������Ƿ����
void LoadCuttedByPxql(float xql, float p_all_kq, float p_40_kq, float* p_prior, bool* cutted, int size, float qql_set){
	float p_syl;// ʣ�����и�����
	float p;
	//������ȼ��г���Ϣ
	for (int i = 0; i < size; ++i){
		cutted[i] = false;
	}
	//������С��0�� �˳�
	if (xql <= 0.0) return;

	//���ȸ�ȫ������������
	if (xql >= p_all_kq){
		//ȫ��������
		for (int i = 0; i < size; ++i){
			if (p_prior[i] > LOAD_ALIVE_P){
				cutted[i] = true;
			}else{
				cutted[i] = false;
			}
		}
		return;
	}else if (xql >= p_40_kq){
		//ǰ���ȼ�40���ɲ�����
		for (int i = 0; i < 40; ++i){
			if (p_prior[i] > LOAD_ALIVE_P){
				cutted[i] = true;
			}else{
				cutted[i] = false;
			}
		}
		p_syl = xql - p_40_kq;
		for (int i = 40; i < size; ++i){
			//�����ȼ�������Ϣ�ж�
			if (p_prior[i] < LOAD_ALIVE_P){
				cutted[i] = false;
				continue;
			} 
			p_syl -= p_prior[i];
			if (p_syl < 0.0){//����������,�򽫵����ȼ���Ϊ�г�����������ѭ��
				break;
			}else{
				cutted[i] = true;
			}
			
		}
		return;
	}else{
		//ֻ��ǰ40���ȼ����и��ɵ����
		p_syl = xql;//��������Ϊʣ��������
		for (int i = 0; i < 40; ++i){
			//�����ȼ�������Ϣ�ж�
			if (p_prior[i] < LOAD_ALIVE_P){
				cutted[i] = false;
				continue;
			} 
			p_syl -= p_prior[i];
			cutted[i] = true;

			if ((p_syl >= 0.0) && (p_syl <= qql_set)){//Ƿ����������СǷ���ż�����ֹͣ����
				break;
			}else if (p_syl < 0.0){//�����ˣ���ȡ���г�
				p_syl += p_prior[i];
				cutted[i] = false;
			}
		}
		return;

	}
	return;
}

//  ���¸����г���Ϣ
//	dev:װ�ýṹ���ַ
//  no_sys: 1-ϵͳ1  2-ϵͳ2   3-ȫ��
void UpdateCuttedInfo(DEVINFO* dev, uint8 no_sys, uint8 vl){

	uint8 prior;
//	float pcutted = 0.0;//ͳ���г���
//	uint8 ncutted = 0;
	for (int i = 0; i < LOAD_P_NUM; ++i){
		//����δͶ�˲�����
		if (dev->load[i].alive == false) continue;
		//������ϵͳ1��ϵͳ2���г�����ϵͳ״̬�������򲻴���
		if ((dev->load[i].voltagelevel & vl) == 0x0){
			continue;
		}
		if ((dev->load[i].onWhichSys & no_sys) == 0x0){//ϵͳ�޹����򲻸���
			continue;
		}
		prior = dev->load[i].prior;
		if (dev->cutted_prior[prior - 1]){
			dev->load[i].beCutted = true;
		}
	}
	return;
}


//��������г���Ϣ
void ExportLoadOutput(DEVINFO* dev, int tac_index, char* tac_num, float yq, float kq){
	float pcutted = 0.0;//�����г���
	uint8 ncutted = 0;//�����г�����

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
	//������������Ϣ
	//LogFuncSendInfo(&(dev->tac[tac_index]));
	LogFuncSendInfo(dev->tac + tac_index);
#endif

#ifndef _DEBUG
	//����г���Ϣ
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
//�����г�����˫�ߣ�����˫��
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

//����1�����߼�
int RUN_TAC_NO1_FAULT(DEVINFO* dev, FAULTINFO* fault){
#ifdef _LOG
	cout << "Log[func RUN_TAC_NO1_FAULT]: running RUN_TAC_NO1_FAULT" << endl;
#endif
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action = false;
	float xql, hjz;
	xql = dev->P9591 - dev->P9572;

	//����ǰ״̬����
	stat_action_200ms = ((dev->HWJ9591 || dev->HWJ9592) || ((dev->HWJ9571 == 0) && (dev->HWJ9511 || dev->HWJ9572))) && dev->Conn_S2;
	//����״̬����
	stat_action = (((fault->T9591 || (dev->HWJ9591 == 0x0)) && (fault->T9572 || (dev->HWJ9572 == 0x0))) ||
				  ((dev->HWJ9571 == 0x0) && (fault->T9511 || (dev->HWJ9511 == 0x0)) && (fault->T9572 || (dev->HWJ9572 == 0x0)))) && dev->Conn_S2;
#ifdef _LOG
	cout << "Log[func RUN_TAC_NO1_FAULT]: stat_action_200ms = " << int(stat_action_200ms) << endl
		 << "                             stat_action       = " << int(stat_action) << endl
		 << "                             xql               = " << xql << endl;
#endif
	if (stat_action_200ms && stat_action && xql > 0.0){
		triggered = 1;//�ö�����־
		//���²���������ֲ���
		//		dev->tac.tac_num = 1;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 1);
		CalPKqFault(dev, fault, 1, 3);//��ϵͳ1��35-66���г�

		//strcpy(dev->tac.tac_num, "1-1");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;

		xql -= hjz;
		//���㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1, 3);
		//������Խ��
		ExportLoadOutput(dev, INDEX_TAC1, "1-1", xql + hjz, dev->p_all_kq + hjz);
	}

	return triggered;
}


//����2�����߼�
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
		//���²���������ֲ���
		//		dev->tac.tac_num = 2;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev,1);
		CalPKqFault(dev, fault, 1, 2);

		//strcpy(dev->tac.tac_num, "2-1");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;

		xql -= hjz;
		//���㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1, 2);
		//������Խ��
		ExportLoadOutput(dev, INDEX_TAC2, "2-1", xql + hjz, dev->p_all_kq + hjz);
	}

	return triggered;
}

//����3�����߼�
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
		//���²���������ֲ���
		ClearCuttedTag(dev);
		//		dev->tac.tac_num = 3;
		hjz = CutHJZXFirst(dev,  2);
		CalPKqFault(dev, fault, 2, 3);

		//strcpy(dev->tac.tac_num, "3-1");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;

		xql -= hjz;
		//���㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2, 3);
		//������Խ��
		ExportLoadOutput(dev, INDEX_TAC3, "3-1", xql + hjz, dev->p_all_kq + hjz);
	}

	return triggered;

}

//����4�����߼�
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
		//���²���������ֲ���
		//		dev->tac.tac_num = 4;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 2);
		CalPKqFault(dev, fault, 2, 2);

		//strcpy(dev->tac.tac_num, "4-1");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;

		xql -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 2, 2);
		//���㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2, 2);
		//������Խ��
		ExportLoadOutput(dev, INDEX_TAC4, "4-1", xql + hjz, dev->p_all_kq + hjz);
	}

	return triggered;

}

//����5�����߼�
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

	if (stat_action_200ms && stat_action && (dev->HWJ9572 == 0)){//9572ͣ��
		triggered++;
		xql1 = dev->P9591 - dev->P9572;
		xql2 = dev->P9592 + dev->P9572;
		//���²���������ֲ���
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 1);
		CalPKqFault(dev,fault,1,3);
		//		dev->tac.tac_num = 5;
		//strcpy(dev->tac.tac_num, "5-1");
		//dev->tac.tac_yq = xql1;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql1 -= hjz;
		//ϵͳ1���㸺���г���Ϣ
		LoadCuttedByPxql(xql1, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ1���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1, 3);
		//���ϵͳ1�и�����Ϣ 
		ExportLoadOutput(dev, INDEX_TAC5, "5-1", xql1 + hjz, dev->p_all_kq + hjz);

		//ϵͳ2����
		ClearCuttedTag(dev);
		hjz = CutHJZXFirst(dev, 2);
		CalPKqFault(dev, fault, 2, 3);
		//strcpy(dev->tac.tac_num, "5-2");
		//dev->tac.tac_yq = xql2;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql2 -= hjz;
		//ϵͳ2���㸺���г���Ϣ
		LoadCuttedByPxql(xql2, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ2���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2, 3);
		//������Խ��
		ExportLoadOutput(dev, INDEX_TAC5+1, "5-2", xql2 + hjz, dev->p_all_kq + hjz);

	}else if (stat_action_200ms && stat_action && dev->HWJ9572){//9572����
		triggered++;
		xql = dev->P9591 + dev->P9592;
		//���²���������ֲ���
		//		dev->tac.tac_num = 5;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 3);
		CalPKqFault(dev, fault, 3, 3);

		//strcpy(dev->tac.tac_num, "5-3");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql -= hjz;
		//ȫ�����㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ȫ�����¸����г���Ϣ
		UpdateCuttedInfo(dev, 3, 3);
		//������Խ��
		ExportLoadOutput(dev, INDEX_TAC5+2, "5-3", xql + hjz, dev->p_all_kq + hjz);

	}

	return triggered;

}

//����6�����߼�
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

	if (stat_action_200ms && stat_action && dev->HWJ9572 == 0){//9572ͣ��
		triggered++;
		xql1 = dev->P9591 - dev->P9572;
		xql2 = dev->P9562 + dev->P9572;
		//���²���������ֲ���
		//		dev->tac.tac_num = 6;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 1);
		CalPKqFault(dev,fault, 1, 3);
		//strcpy(dev->tac.tac_num, "6-1");
		//dev->tac.tac_yq = xql1;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql1 -= hjz;
		//ϵͳ1���㸺���г���Ϣ
		LoadCuttedByPxql(xql1, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ1���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1, 3);
		//������Խ��
		ExportLoadOutput(dev, INDEX_TAC6, "6-1", xql1 + hjz, dev->p_all_kq + hjz);

		//ϵͳ2����
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 2);
		CalPKqFault(dev, fault, 2, 2);

		//strcpy(dev->tac.tac_num, "6-2");
		//dev->tac.tac_yq = xql2;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql2 -= hjz;
		//ϵͳ2���㸺���г���Ϣ
		LoadCuttedByPxql(xql2, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ2���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2, 2);
		//������Խ��
		ExportLoadOutput(dev, INDEX_TAC6+1, "6-2", xql2 + hjz, dev->p_all_kq + hjz);
	}else if (stat_action_200ms && stat_action && dev->HWJ9572){//9572����
		triggered++;
		xql = dev->P9591 + dev->P9592;
		//���²���������ֲ���
		//		dev->tac.tac_num = 6;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 3);
		CalPKqFault(dev, fault, 3, 3);
		//strcpy(dev->tac.tac_num, "6-3");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql -= hjz;
		//ȫ�����㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ȫ�����¸����г���Ϣ
		UpdateCuttedInfo(dev, 3, 3);
		//������Խ��
		ExportLoadOutput(dev, INDEX_TAC6+2, "6-3", xql + hjz, dev->p_all_kq + hjz);

	}

	return triggered;
}

//����7�����߼�
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

	if (stat_action_200ms && stat_action && dev->HWJ9572 == 0){//9572ͣ��
		triggered++;
		xql1 = dev->P9561 - dev->P9572;
		xql2 = dev->P9592 + dev->P9572;
		//���²���������ֲ���
		//		dev->tac.tac_num = 7;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 2);
		CalPKqFault(dev, fault, 2, 3);
		//strcpy(dev->tac.tac_num, "7-1");
		//dev->tac.tac_yq = xql1;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql1 -= hjz;
		//ϵͳ1���㸺���г���Ϣ
		LoadCuttedByPxql(xql1, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ1���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2, 3);
		//������Խ��
		ExportLoadOutput(dev, INDEX_TAC7, "7-1", xql1 + hjz, dev->p_all_kq + hjz);

		//ϵͳ2����
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 1);
		CalPKqFault(dev, fault, 1, 2);
		//strcpy(dev->tac.tac_num, "7-2");
		//dev->tac.tac_yq = xql2;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql2 -= hjz;
		//ϵͳ2���㸺���г���Ϣ
		LoadCuttedByPxql(xql2, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ2���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1, 2);
		//������Խ��
		ExportLoadOutput(dev, INDEX_TAC7+1, "7-2", xql2 + hjz, dev->p_all_kq + hjz);
	}else if (stat_action_200ms && stat_action && dev->HWJ9572){//9572����
		triggered++;
		xql = dev->P9592 + dev->P9561;
		//���²���������ֲ���
		//		dev->tac.tac_num = 7;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 3);
		CalPKqFault(dev, fault, 3, 3);
		//strcpy(dev->tac.tac_num, "7-3");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql -= hjz;
		//ȫ�����㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ȫ�����¸����г���Ϣ
		UpdateCuttedInfo(dev, 3, 3);


		//������Խ��
		ExportLoadOutput(dev, INDEX_TAC7+2, "7-3", xql + hjz, dev->p_all_kq + hjz);

	}

	return triggered;

}

//����8�����߼�
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

	if (stat_action_200ms && stat_action && (dev->HWJ9572 == 0)){//9572ͣ��
		xql1 = dev->P9561 - dev->P9572;
		xql2 = dev->P9562 + dev->P9572;
		//���²���������ֲ���
		//		dev->tac.tac_num = 8;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 1);
		CalPKqFault(dev, fault, 1, 2);
		//strcpy(dev->tac.tac_num, "8-1");
		//dev->tac.tac_yq = xql1;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql1 -= hjz;
		//ϵͳ1���㸺���г���Ϣ
		LoadCuttedByPxql(xql1, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ1���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1, 2);
		//������Խ��
		ExportLoadOutput(dev, INDEX_TAC8, "8-1", xql1 + hjz, dev->p_all_kq + hjz);

		//ϵͳ2����
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 2);
		CalPKqFault(dev, fault, 2, 2);
		//strcpy(dev->tac.tac_num, "8-2");
		//dev->tac.tac_yq = xql2;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql2 -= hjz;
		//ϵͳ2���㸺���г���Ϣ
		LoadCuttedByPxql(xql2, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ2���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2, 2);
		
		ExportLoadOutput(dev, INDEX_TAC8+1, "8-2", xql2 + hjz, dev->p_all_kq + hjz);

	}else if (stat_action_200ms && stat_action && dev->HWJ9572){//9572����
		triggered++;
		xql = dev->P9562 + dev->P9561;
		//���²���������ֲ���
		//		dev->tac.tac_num = 8;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 3);
		CalPKqFault(dev, fault, 3, 2);
		//strcpy(dev->tac.tac_num, "8-3");
		//dev->tac.tac_yq = xql;
		//dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql -= hjz;
		//ȫ�����㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ȫ�����¸����г���Ϣ
		UpdateCuttedInfo(dev, 3, 2);
		//������Խ��
		ExportLoadOutput(dev, INDEX_TAC8+2, "8-3", xql + hjz, dev->p_all_kq + hjz);

	}

	return triggered;

}

//��ʼ�����Ͽ���
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

//��ʼ������������
void InitializeTacOutput(DEVINFO* dev){
	//���Ա��
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

//����ȫ���Լ���
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

//����ϵͳ���ϼ�����λ����������Ʋ�ϵͳ�������
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


//���ݹ���Ƶ�ʽ��ͼ�����й���
void CalPKqFault(DEVINFO*dev, FAULTINFO* fault, uint8 sys, uint8 vl){
	uint8 prior;
	uint8 uSys, uVl, FT_SYS;
	bool  under40;
	float p;

	dev->p_all_kq = 0.0;
	dev->p_40_kq = 0.0;
	//��ʼ�����ȼ���������
	for (int i = 0;i < MAX_PRIOR;i++){
		dev->p_prior[i] = 0.0;
		dev->cutted_prior[i] = false;
	}

	//�������ȼ�ͳ�Ƹ��ɹ���
	for (int i = 0; i < LOAD_P_NUM; ++i){
		p = dev->load[i].pload;
		prior = dev->load[i].prior;
		uSys = dev->load[i].onWhichSys;
		uVl = dev->load[i].voltagelevel;

		if(!dev->load[i].alive) continue;	//����δͶ�ˣ���ͳ��
		if(prior <=0 || prior > MAX_PRIOR) continue;//���ȼ����ԣ���ͳ��

		prior <= 40 ? under40 = true : under40 = false;
		
		if (i < INDEX_EKY){//����վ����
			FT_SYS = (fault->FT_KGZ_S1 & 0x1) | ((fault->FT_KGZ_S2 & 0x1)<<1);
			if (((uSys & sys) == 0x0) || ((uVl & vl) == 0x0) || ((uSys & FT_SYS) == 0x0)){
				continue;
			}
		}else if (i < INDEX_CH3){//����ѹ
			FT_SYS = (fault->FT_EKY_S1 & 0x1) | ((fault->FT_EKY_S2 & 0x1)<<1);
			if (((uSys & sys) == 0x0) || ((uVl & vl) == 0x0) || ((uSys & FT_SYS) == 0x0)){
				continue;
			}
		}else if (i < INDEX_CH4){//���߻�
			FT_SYS = (fault->FT_CH3_S1 & 0x1) | ((fault->FT_CH3_S2 & 0x1)<<1);
			if (((uSys & sys) == 0x0) || ((uVl & vl) == 0x0) || ((uSys & FT_SYS) == 0x0)){
				continue;
			}
		}else{//�Ĵ߻�
			FT_SYS = (fault->FT_CH4_S1 & 0x1) | ((fault->FT_CH4_S2 & 0x1)<<1);
			if (((uSys & sys) == 0x0) || ((uVl & vl) == 0x0) || ((uSys & FT_SYS) == 0x0)){
				continue;
			}
		}

		//��ʼ�������ˣ�˵����������ǿ����еġ�
		dev->p_all_kq += p;
		under40 ? dev->p_40_kq += p : dev->p_40_kq += 0.0;
		dev->p_prior[prior - 1] += p;//�����ȼ������ۼ�
#ifdef _DEBUG
		cout << i << " - " << int(prior) << " - " << p << endl;
#endif
	}
	return;
}

//��̬�����ģ�⺯��
void run_tac_simulate(){

	//1. ��ʼ��
	Initialize(&devdata, &faultdata);
	//2. ��ȡ����
	ReadDevInfo(&devdata, &faultdata);
	//3. ��������Ϣ
	HandleLoadSys(&devdata);	
	//4. ������Ϻ�ϵͳ����
	CheckSysConn(&devdata, &faultdata);

	SetAllFault(&faultdata);
	devdata.Conn_S1 = 1;
	devdata.Conn_S2 = 1;
	devdata.Conn_S1S2 = 0;

	if(devdata.Conn_S1S2) return;//ϵͳ12�������������򲻼�����Ӧ����

	InitializeTacOutput(&devdata);
	//CalLoadStatics(&devdata);
#ifdef _LOG
	//���ϵͳ״̬����
	LogFuncSysdata(&devdata);
	cout << "��������" << endl;
	cout <<"9511:" << int(devdata.HWJ9511) << int(faultdata.T9511)<< endl;
	cout <<"9512:" << int(devdata.HWJ9512) << int(faultdata.T9512)<< endl
		 <<"9591:" << int(devdata.HWJ9591) << int(faultdata.T9591)<< endl
		 <<"9592:" << int(devdata.HWJ9592) << int(faultdata.T9592)<< endl
		 <<"9561:" << int(devdata.HWJ9561) << int(faultdata.T9561)<< endl
		 <<"9562:" << int(devdata.HWJ9562) << int(faultdata.T9562)<< endl
		 <<"9572:" << int(devdata.HWJ9572) << int(faultdata.T9572)<< endl
		 <<"9571:" << int(devdata.HWJ9571) << endl;
	cout << "Ƶ���½�ģ�⣺" << endl;
	cout << "����վϵͳ1��" << int(faultdata.FT_KGZ_S1) << endl
		 << "����վϵͳ2��" << int(faultdata.FT_KGZ_S2) << endl
		 << "����ѹϵͳ1��" << int(faultdata.FT_EKY_S1) << endl
		 << "����ѹϵͳ2��" << int(faultdata.FT_EKY_S2) << endl
		 << "���߻�ϵͳ1��" << int(faultdata.FT_CH3_S1) << endl
		 << "���߻�ϵͳ2��" << int(faultdata.FT_CH3_S2) << endl
		 << "�Ĵ߻�ϵͳ1��" << int(faultdata.FT_CH4_S1) << endl
		 << "�Ĵ߻�ϵͳ2��" << int(faultdata.FT_CH4_S2) << endl;
#endif

	//4. ���Լ���
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


