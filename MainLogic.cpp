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

//����ȫ�ֱ���
static DEVINFO       devdata;	
static DATA_HANDLER  func_read;
static void*         env_read;
static TAC_HANDLER   func_send;
static void*         env_send;

//����ص�����
void data_register(DATA_HANDLER data_handler,void *env){
	func_read = data_handler;
	env_read = env;
	return;
}
//����ص�����
void result_register(TAC_HANDLER tac_handler,void *env){
	func_send = tac_handler;
	env_send = env;
	return;
}
//��ʼ��
void Initialize(DEVINFO* dev){
	//ϵͳģ����
	for (int i = 0; i < SYS_P_NUM; ++i){
		dev->Sys_P[i].fun_num = FUN_SYS_P[i];
		dev->Sys_P[i].inf_num = INF_SYS_P[i];
		dev->Sys_P[i].value = 0;
	}
	//��������
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
	return;
}
//��ȡװ����Ϣ
void ReadDevInfo(DEVINFO* dev){

#ifndef _DEBUG
	//��ȡϵͳģ������Ϣ
	func_read(SHZZ,dev->Sys_P, SYS_P_NUM, env_read);
	//��ȡ������Ϣ
	func_read(SHZZ,dev->Load_P, LOAD_P_NUM, env_read);
	//��ȡ���ȼ���ֵ
	func_read(SHZZ,dev->Load_Prior, LOAD_P_NUM+1, env_read);
	//��ȡϵͳ����״̬
	func_read(SHZZ,dev->Load_Conn, LOAD_CONN_NUM, env_read);
	//��ȡϵͳ��������״̬
	func_read(SHZZ,dev->Sys_Stat, SYS_STAT_NUM, env_read);

	//����վ��ȡ��Ϣ
	func_read(KGZ,dev->Load_Conn_KGZ, LINE_NUM_KGZ, env_read);
	//����ѹ��ȡ��Ϣ
	func_read(EKY,dev->Load_Conn_EKY, LINE_NUM_EKY, env_read);
	//���߻���ȡ��Ϣ
	func_read(CH3,dev->Load_Conn_CH3, LINE_NUM_CH3, env_read);
	//�Ĵ߻���ȡ��Ϣ
	func_read(CH4,dev->Load_Conn_CH4, LINE_NUM_CH4, env_read);
	//ʯ���Ӷ�ȡ��Ϣ
	func_read(SHZ,dev->Load_Conn_SHZ, LINE_NUM_SHZ, env_read);


#else
	//���ļ��ж�ȡϵͳ״̬
	bool res = ReadTestCaseFile(std::string("C:\\Users\\zhengh.NR-RD\\Desktop\\����ʯ����Ŀ\\XDC.sta"), std::string("C:\\Users\\zhengh.NR-RD\\Desktop\\����ʯ����Ŀ\\XDC.set"), dev);
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
	dev->P_HZX_1 = dev->Sys_P[7].value;
	dev->P_HZX_2 = dev->Sys_P[8].value;
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
	dev->HWJ9571 = uint8(dev->Load_Conn_SHZ[0].value) == 0 ? 1 : 0;

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
#ifdef _DEBUG
				cout << "load_no: " << i + 1 << " " << p << " " << int(uSys) << " " << int(prior) << " " << int(vl) << endl;
#endif

			//����ϵͳ1��
			if (uSys == 0x1){
				dev->p_all_kq_s1 += p;
				under40 == true ? dev->p_40_kq_s1 += p: dev->p_40_kq_s1 += 0.0;
				//ͳ��ϵͳ1��66kV����
				if (vl == 2){
					dev->p_kq_s1_66 += p;
					under40 == true ? dev->p_40_kq_s1_66 += p: dev->p_40_kq_s1_66 += 0.0;
				}
			}
			//����ϵͳ2��
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

//����г���־
void ClearCuttedTag(DEVINFO* dev){
	for (int i = 0;i < LOAD_P_NUM + 4;++i){
		dev->load[i].beCutted = false;
	}
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
		if ((dev->load[i].onWhichSys != sys) || ((dev->load[i].voltagelevel & vl) == 0x0)){
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
		if ((no_sys == dev->load[i].onWhichSys) && ((vl & dev->load[i].voltagelevel)!= 0x0)){
			prior = dev->load[i].prior;
			if (dev->cutted_prior[prior - 1]){
				dev->load[i].beCutted = true;
			}
		}
	}
	return;
}


//��������г���Ϣ
void ExportLoadOutput(DEVINFO* dev){
	float pcutted = 0.0;//�����г���
	uint8 ncutted = 0;//�����г�����
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
	//����г���Ϣ
	func_send(SHZZ,&(dev->tac), 1, env_send);
#else
	bool res = SendTacFile(std::string(".\\tacoutfile.txt"), dev);
	if (!res){
		std::cout<< "Error: Failed to SendTacFile!" << endl;
	}
#endif

	return;
}
//�����г�����˫�ߣ�����˫��
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

//����1�����߼�
int RUN_TAC_NO1(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql, hjz;
	xql = dev->P9591 - dev->P9572;
	stat_action_200ms = ((dev->HWJ9591 || dev->HWJ9592) ||
		((dev->HWJ9571 == 0) && (dev->HWJ9511 || dev->HWJ9572))) 
		&& dev->Conn_S2;
	if (stat_action_200ms && xql > 0.0){
		//���²���������ֲ���
//		dev->tac.tac_num = 1;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 1);

		strcpy(dev->tac.tac_num, "1-1");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq_s1 + hjz;
		
		xql -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 1, 3);
		//���㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1, 3);
		//������Խ��
		ExportLoadOutput(dev);
	}

	return triggered;
}

//����2�����߼�
int RUN_TAC_NO2(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql, hjz;
	xql = dev->P9561 - dev->P9572;

	stat_action_200ms = (dev->HWJ9561 || dev->HWJ9572) && dev->Conn_S2;
	if (stat_action_200ms && xql > 0.0){
		//���²���������ֲ���
//		dev->tac.tac_num = 2;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev,1);

		strcpy(dev->tac.tac_num, "2-1");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_kq_s1_66 + hjz;

		xql -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 1, 2);
		//���㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_kq_s1_66, dev->p_40_kq_s1_66, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1, 2);
		//������Խ��
		ExportLoadOutput(dev);
	}

	return triggered;
}

//����3�����߼�
int RUN_TAC_NO3(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql, hjz;
	xql = dev->P9592 + dev->P9572;

	stat_action_200ms = ((dev->HWJ9592 || dev->HWJ9572) || ((dev->HWJ9571 == 0) && (dev->HWJ9512 || dev->HWJ9572))) && dev->Conn_S1;
	if (stat_action_200ms && xql > 0.0){
		//���²���������ֲ���
		ClearCuttedTag(dev);
//		dev->tac.tac_num = 3;
		hjz = CutHJZXFirst(dev,  2);

		strcpy(dev->tac.tac_num, "3-1");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq_s2 + hjz;

		xql -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 2, 3);
		//���㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2, 3);
		//������Խ��
		ExportLoadOutput(dev);
	}

	return triggered;
}

//����4�����߼�
int RUN_TAC_NO4(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql, hjz;
	xql = dev->P9562 + dev->P9572;

	stat_action_200ms = (dev->HWJ9562 || dev->HWJ9572) && dev->Conn_S1;
	if (stat_action_200ms && xql > 0.0){
		//���²���������ֲ���
//		dev->tac.tac_num = 4;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 2);

		strcpy(dev->tac.tac_num, "4-1");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_kq_s2_66 + hjz;

		xql -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 2, 2);
		//���㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2, 2);
		//������Խ��
		ExportLoadOutput(dev);
	}

	return triggered;
}

//����5�����߼�
int RUN_TAC_NO5(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action_200ms1 = false;
	float xql, xql1, xql2, hjz;
	stat_action_200ms = (dev->HWJ9511 || dev->HWJ9591) && (dev->HWJ9512 || dev->HWJ9592);
	stat_action_200ms1 = (dev->HWJ9511 && dev->HWJ9591) && (dev->HWJ9512 && dev->HWJ9592);
	if (stat_action_200ms1 && dev->HWJ9572 == 0){//9572ͣ��
		xql1 = dev->P9591 - dev->P9572;
		xql2 = dev->P9592 + dev->P9572;
		//���²���������ֲ���
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 1);
//		dev->tac.tac_num = 5;
		strcpy(dev->tac.tac_num, "5-1");
		dev->tac.tac_yq = xql1;
		dev->tac.tac_kq = dev->p_all_kq_s1 + hjz;

		xql1 -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 1, 3);
		//ϵͳ1���㸺���г���Ϣ
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ1���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1, 3);
		//���ϵͳ1�и�����Ϣ 
		ExportLoadOutput(dev);

		//ϵͳ2����
		ClearCuttedTag(dev);
		hjz = CutHJZXFirst(dev, 2);
		strcpy(dev->tac.tac_num, "5-2");
		dev->tac.tac_yq = xql2;
		dev->tac.tac_kq = dev->p_all_kq_s2 + hjz;

		xql2 -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 2, 3);
		//ϵͳ2���㸺���г���Ϣ
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ2���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2, 3);
		//������Խ��
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572����
		xql = dev->P9591 + dev->P9592;
		//���²���������ֲ���
//		dev->tac.tac_num = 5;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 3);

		strcpy(dev->tac.tac_num, "5-3");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq + hjz;

		xql -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 3, 3);
		//ȫ�����㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ȫ�����¸����г���Ϣ
		UpdateCuttedInfo(dev, 3, 3);
		//������Խ��
		ExportLoadOutput(dev);

	}

	return triggered;
}

//����6�����߼�
int RUN_TAC_NO6(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action_200ms1 = false;
	float xql, xql1, xql2, hjz;
	stat_action_200ms = ((dev->HWJ9591 || dev->HWJ9562) || ((dev->HWJ9571 == 0) && (dev->HWJ9511 || dev->HWJ9562))) && dev->HWJ9561;
	stat_action_200ms1 = ((dev->HWJ9591 && dev->HWJ9562) || ((dev->HWJ9571 == 0) && (dev->HWJ9511 && dev->HWJ9562))) && dev->HWJ9561;
	if (stat_action_200ms1 && dev->HWJ9572 == 0){//9572ͣ��
		xql1 = dev->P9591 - dev->P9572;
		xql2 = dev->P9562 + dev->P9572;
		//���²���������ֲ���
//		dev->tac.tac_num = 6;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 1);
		strcpy(dev->tac.tac_num, "6-1");
		dev->tac.tac_yq = xql1;
		dev->tac.tac_kq = dev->p_all_kq_s1 + hjz;

		xql1 -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 1, 3);
		//ϵͳ1���㸺���г���Ϣ
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ1���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1, 3);
		//������Խ��
		ExportLoadOutput(dev);
		
		//ϵͳ2����
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 2);
		strcpy(dev->tac.tac_num, "6-2");
		dev->tac.tac_yq = xql2;
		dev->tac.tac_kq = dev->p_all_kq_s2 + hjz;
		xql2 -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 2, 2);
		//ϵͳ2���㸺���г���Ϣ
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ2���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2, 2);
		//������Խ��
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572����
		xql = dev->P9591 + dev->P9592;
		//���²���������ֲ���
//		dev->tac.tac_num = 6;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 3);
		strcpy(dev->tac.tac_num, "6-3");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 3, 3);
		//ȫ�����㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ȫ�����¸����г���Ϣ
		UpdateCuttedInfo(dev, 3, 3);


		//������Խ��
		ExportLoadOutput(dev);

	}

	return triggered;
}

//����7�����߼�
int RUN_TAC_NO7(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action_200ms1 = false;
	float xql, xql1, xql2, hjz;
	stat_action_200ms = ((dev->HWJ9592 || dev->HWJ9561) || ((dev->HWJ9571 == 0) && (dev->HWJ9512 || dev->HWJ9561))) && dev->HWJ9562;
	stat_action_200ms1 = ((dev->HWJ9592 && dev->HWJ9561) || ((dev->HWJ9571 == 0) && (dev->HWJ9512 && dev->HWJ9561))) && dev->HWJ9562;
	if (stat_action_200ms1 && dev->HWJ9572 == 0){//9572ͣ��
		xql1 = dev->P9561 - dev->P9572;
		xql2 = dev->P9592 + dev->P9572;
		//���²���������ֲ���
//		dev->tac.tac_num = 7;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 1);
		strcpy(dev->tac.tac_num, "7-1");
		dev->tac.tac_yq = xql1;
		dev->tac.tac_kq = dev->p_all_kq_s1 + hjz;
		xql1 -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 2, 3);
		//ϵͳ1���㸺���г���Ϣ
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ1���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1, 3);
		//������Խ��
		ExportLoadOutput(dev);

		//ϵͳ2����
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 2);
		strcpy(dev->tac.tac_num, "7-2");
		dev->tac.tac_yq = xql2;
		dev->tac.tac_kq = dev->p_all_kq_s2 + hjz;
		xql2 -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 1, 2);
		//ϵͳ2���㸺���г���Ϣ
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ2���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2, 2);
		//������Խ��
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572����
		xql = dev->P9592 + dev->P9561;
		//���²���������ֲ���
//		dev->tac.tac_num = 7;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 1);
		strcpy(dev->tac.tac_num, "7-3");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 3, 3);
		//ȫ�����㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ȫ�����¸����г���Ϣ
		UpdateCuttedInfo(dev, 3, 3);


		//������Խ��
		ExportLoadOutput(dev);

	}

	return triggered;
}

//����8�����߼�
int RUN_TAC_NO8(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	bool stat_action_200ms1 = false;
	float xql, xql1, xql2, hjz;
	stat_action_200ms = (dev->HWJ9561 || dev->HWJ9562);
	stat_action_200ms1 = (dev->HWJ9561 && dev->HWJ9562);
	if (stat_action_200ms1 && (dev->HWJ9572 == 0)){//9572ͣ��
		xql1 = dev->P9561 - dev->P9572;
		xql2 = dev->P9562 + dev->P9572;
		//���²���������ֲ���
//		dev->tac.tac_num = 8;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 1);
		strcpy(dev->tac.tac_num, "8-1");
		dev->tac.tac_yq = xql1;
		dev->tac.tac_kq = dev->p_all_kq_s1 + hjz;
		xql1 -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 1, 2);
		//ϵͳ1���㸺���г���Ϣ
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ1���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1, 2);
		//������Խ��
		ExportLoadOutput(dev);

		//ϵͳ2����
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 1);
		strcpy(dev->tac.tac_num, "8-2");
		dev->tac.tac_yq = xql2;
		dev->tac.tac_kq = dev->p_all_kq_s2 + hjz;
		xql2 -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 2, 2);
		//ϵͳ2���㸺���г���Ϣ
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ2���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2, 2);

		//������Խ��
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572����
		xql = dev->P9562 + dev->P9561;
		//���²���������ֲ���
//		dev->tac.tac_num = 8;
		ClearCuttedTag(dev);
		//���г�����˫�ߡ�����˫��
		hjz = CutHJZXFirst(dev, 1);
		strcpy(dev->tac.tac_num, "8-3");
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq + hjz;
		xql -= hjz;
		//�γ����ȼ�������Ϣ
		CalLoadInfoByPrior(dev, 3, 2);
		//ȫ�����㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ȫ�����¸����г���Ϣ
		UpdateCuttedInfo(dev, 3, 2);
		//������Խ��
		ExportLoadOutput(dev);

	}

	return triggered;
}


//��̬�����ģ�⺯��
void run_tac_simulate(){

	//1. ��ʼ��
	Initialize(&devdata);
	//2. ��ȡ����
	ReadDevInfo(&devdata);
	//3. ��������Ϣ
	HandleLoadSys(&devdata);	
	CalLoadStatics(&devdata);

	//4. ���Լ���
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


