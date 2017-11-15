#include "systac.h"
#include "DeviceSet.h"
#include "DeviceDef.h"
#include <stdio.h>
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
	dev->HWJ9571  = 1;//Ĭ��9571Ϊ����״̬
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
//��ȡװ����Ϣ
void ReadDevInfo(DEVINFO* dev){
	//��ȡϵͳģ������Ϣ
	//func_read(dev->Sys_P, SYS_P_NUM, env_read);
	//��ȡ������Ϣ
	//func_read(dev->Load_P, LOAD_P_NUM, env_read);
	//��ȡ���ȼ���ֵ
	//func_read(dev->Load_Prior, LOAD_P_NUM+1, env_read);
	//��ȡϵͳ����״̬
	//func_read(dev->Load_Conn, LOAD_CONN_NUM, env_read);
	//��ȡϵͳ��������״̬
	//func_read(dev->Sys_Stat, SYS_STAT_NUM, env_read);

	//��������Ԥ����
	dev->P9591 = dev->Sys_P[0].value;
	dev->P9561 = dev->Sys_P[1].value;
	dev->P9592 = dev->Sys_P[2].value;
	dev->P9562 = dev->Sys_P[3].value;
	dev->P_HJX_1 = dev->Sys_P[4].value;
	dev->P_HJX_2 = dev->Sys_P[5].value;
	dev->P_HSX = dev->Sys_P[6].value;
	dev->P_HZX = dev->Sys_P[7].value;
	//ϵͳ����״̬Ԥ����
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

	//�������ݴ���
	dev->p_qq_setting = dev->Load_Prior[LOAD_P_NUM].value;//Ƶ��Ƿ�й��ʶ�ֵ
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
//�����ɹ���ϵͳ״̬
void HandleLoadSys(DEVINFO* dev){
	int32 temp; 
	int32 stat1, stat2;
	// ����վϵͳ1��·
	temp = int32(dev->Sys_Stat[0].value);
	for (int i = 0; i < LINE_NUM_KGZ; ++i){
		dev->load[i].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 1 :0;
	}
	//����վϵͳ��·2
	temp = int32(dev->Sys_Stat[1].value);
	for (int i = 0; i < LINE_NUM_KGZ; ++i){
		dev->load[i].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 2 :0;
	}
	//����ѹϵͳ1��·
	temp = int32(dev->Sys_Stat[2].value);
	for (int i = 0; i < LINE_NUM_EKY; ++i){
		dev->load[i+INDEX_EKY].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 1 :0;
	}
	//����ѹϵͳ2��·
	temp = int32(dev->Sys_Stat[3].value);
	for (int i = 0; i < LINE_NUM_EKY; ++i){
		dev->load[i+INDEX_EKY].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 2 :0;
	}
	//���߻�ϵͳ1��·
	stat1 = int32(dev->Sys_Stat[4].value);
	stat2 = int32(dev->Sys_Stat[5].value);
	temp = (stat1 & 0xffff)|((stat2 & 0xffff)<<16);
	for (int i = 0; i < LINE_NUM_CH3; ++i){
		dev->load[i+INDEX_CH3].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 1 :0;
	}
	//���߻�ϵͳ2��·
	stat1 = int32(dev->Sys_Stat[6].value);
	stat2 = int32(dev->Sys_Stat[7].value);
	temp = (stat1 & 0xffff)|((stat2 & 0xffff)<<16);
	for (int i = 0; i < LINE_NUM_CH3; ++i){
		dev->load[i+INDEX_CH3].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 2 :0;
	}
	//�Ĵ߻�ϵͳ1��·
	stat1 = int32(dev->Sys_Stat[8].value);
	stat2 = int32(dev->Sys_Stat[9].value);
	temp = (stat1 & 0xffff)|((stat2 & 0xffff)<<16);
	for (int i = 0; i < LINE_NUM_CH3; ++i){
		dev->load[i+INDEX_CH4].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 1 :0;
	}
	//�Ĵ߻�ϵͳ2��·
	stat1 = int32(dev->Sys_Stat[10].value);
	stat2 = int32(dev->Sys_Stat[11].value);
	temp = (stat1 & 0xffff)|((stat2 & 0xffff)<<16);
	for (int i = 0; i < LINE_NUM_CH3; ++i){
		dev->load[i+INDEX_CH4].onWhichSys = (temp & (0x1<<i)) == 0x1 ? 2 :0;
	}
	return;
}
//�������ȼ�ͳ�Ƹ��ɹ���
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

	//�������ȼ�ͳ�Ƹ��ɹ���
	for (int i = 0; i < LOAD_P_NUM; ++i){
		p = dev->load[i].pload;
		prior = dev->load[i].prior;
		uSys = dev->load[i].onWhichSys;

		if(!dev->load[i].alive) continue;	//����δͶ�ˣ���ͳ��

		if (prior > 0 && prior <= MAX_PRIOR){
			prior <= 40 ? under40 = true : under40 = false;
			//�������
			dev->p_all_kq += p;
			dev->p_prior_s1s2[prior-1] += p;
			under40 == true ? dev->p_40_kq += p: dev->p_40_kq += 0.0;

			//����ϵͳ1
			if (uSys == 1){
				dev->p_all_kq_s1 += p;
				dev->p_prior_s1[prior-1] += p;
				under40 == true ? dev->p_40_kq_s1 += p: dev->p_40_kq_s1 += 0.0;
			}else if(uSys == 2){
				dev->p_all_kq_s2 += p;
				dev->p_prior_s2[prior-1] += p;
				under40 == true ? dev->p_40_kq_s2 += p: dev->p_40_kq_s2 += 0.0;
			}else{
				//����ϵͳ������

			}
		}
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
	//float p;
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

//  ���¸����г���Ϣ
//	dev:װ�ýṹ���ַ
//  no_sys: 1-ϵͳ1  2-ϵͳ2   3-ȫ��
void UpdateCuttedInfo(DEVINFO* dev, int no_sys){

	int prior;
	if (no_sys <= 0) return;
	for (int i = 0; i < LOAD_P_NUM; ++i){
		//����δͶ�˲�����
		if (dev->load[i].alive == false) continue;
		//������ϵͳ1��ϵͳ2���г�����ϵͳ״̬�������򲻴���
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

//��������г���Ϣ
void ExportLoadOutput(DEVINFO* dev){
	for (int i = 0; i < LOAD_P_NUM; ++i){
		dev->LoadOutput[i].fun_num = dev->load[i].fun;
		dev->LoadOutput[i].inf_num = dev->load[i].inf;
		dev->LoadOutput[i].cutted = dev->load[i].beCutted;

		dev->load[i].beCutted = false;//��������г���Ϣ�����Ϊ��һ�β��Լ�����׼��
	}
//	dev->tac.data = dev->LoadOutput;
	dev->tac.data_num = LOAD_P_NUM;

	//����г���Ϣ
//	func_send(&(dev->tac), 1, env_send);

	return;
}

//����1�����߼�
int RUN_TAC_NO1(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql;
	xql = dev->P9591 - dev->P9572;
	stat_action_200ms = ((dev->HWJ9591 || dev->HWJ9592) ||
		((dev->HWJ9571 == 0) && (dev->HWJ9571 || dev->HWJ9572))) 
		&& dev->Conn_S2;
	if (stat_action_200ms && xql > 0.0){
		//���²���������ֲ���
		dev->tac.tac_num = 1;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq_s1;
		//���㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior_s1, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1);
		//������Խ��
		ExportLoadOutput(dev);
	}

	return triggered;
}

//����2�����߼�
int RUN_TAC_NO2(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql;
	xql = dev->P9561 - dev->P9572;
	stat_action_200ms = (dev->HWJ9561 || dev->HWJ9572) && dev->Conn_S2;
	if (stat_action_200ms && xql > 0.0){
		//���²���������ֲ���
		dev->tac.tac_num = 2;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq_s1;
		//���㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior_s1, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1);
		//������Խ��
		ExportLoadOutput(dev);
	}

	return triggered;
}

//����3�����߼�
int RUN_TAC_NO3(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql;
	xql = dev->P9592 + dev->P9572;
	stat_action_200ms = ((dev->HWJ9592 || dev->HWJ9572) || ((dev->HWJ9571 == 0) && (dev->HWJ9512 || dev->HWJ9572))) && dev->Conn_S1;
	if (stat_action_200ms && xql > 0.0){
		//���²���������ֲ���
		dev->tac.tac_num = 3;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq_s2;
		//���㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior_s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2);
		//������Խ��
		ExportLoadOutput(dev);
	}

	return triggered;
}

//����4�����߼�
int RUN_TAC_NO4(DEVINFO* dev){
	int triggered = 0;
	bool stat_action_200ms = false;
	float xql;
	xql = dev->P9562 + dev->P9572;
	stat_action_200ms = (dev->HWJ9562 || dev->HWJ9572) && dev->Conn_S1;
	if (stat_action_200ms && xql > 0.0){
		//���²���������ֲ���
		dev->tac.tac_num = 4;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq_s2;
		//���㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior_s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2);
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
	float xql, xql1, xql2;
	stat_action_200ms = (dev->HWJ9511 || dev->HWJ9591) && (dev->HWJ9512 || dev->HWJ9592);
	stat_action_200ms1 = (dev->HWJ9511 && dev->HWJ9591) && (dev->HWJ9512 && dev->HWJ9592);
	if (stat_action_200ms1 && dev->HWJ9572 == 0){//9572ͣ��
		xql1 = dev->P9591 - dev->P9572;
		xql2 = dev->P9592 + dev->P9572;
		//���²���������ֲ���
		dev->tac.tac_num = 5;
		dev->tac.tac_yq = xql1 + xql2;
		dev->tac.tac_kq = dev->p_all_kq;
		//ϵͳ1���㸺���г���Ϣ
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior_s1, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ1���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1);

		//ϵͳ2���㸺���г���Ϣ
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior_s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ2���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2);

		//������Խ��
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572����
		xql = dev->P9591 + dev->P9592;
		//���²���������ֲ���
		dev->tac.tac_num = 5;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq;
		//ȫ�����㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior_s1s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ȫ�����¸����г���Ϣ
		UpdateCuttedInfo(dev, 3);


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
	float xql, xql1, xql2;
	stat_action_200ms = ((dev->HWJ9591 || dev->HWJ9562) || ((dev->HWJ9571 == 0) && (dev->HWJ9511 || dev->HWJ9562))) && dev->HWJ9561;
	stat_action_200ms1 = ((dev->HWJ9591 && dev->HWJ9562) || ((dev->HWJ9571 == 0) && (dev->HWJ9511 && dev->HWJ9562))) && dev->HWJ9561;
	if (stat_action_200ms1 && dev->HWJ9572 == 0){//9572ͣ��
		xql1 = dev->P9591 - dev->P9572;
		xql2 = dev->P9562 + dev->P9572;
		//���²���������ֲ���
		dev->tac.tac_num = 6;
		dev->tac.tac_yq = xql1 + xql2;
		dev->tac.tac_kq = dev->p_all_kq;
		//ϵͳ1���㸺���г���Ϣ
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior_s1, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ1���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1);

		//ϵͳ2���㸺���г���Ϣ
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior_s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ2���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2);

		//������Խ��
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572����
		xql = dev->P9591 + dev->P9592;
		//���²���������ֲ���
		dev->tac.tac_num = 6;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq;
		//ȫ�����㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior_s1s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ȫ�����¸����г���Ϣ
		UpdateCuttedInfo(dev, 3);


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
	float xql, xql1, xql2;
	stat_action_200ms = ((dev->HWJ9592 || dev->HWJ9561) || ((dev->HWJ9571 == 0) && (dev->HWJ9512 || dev->HWJ9561))) && dev->HWJ9562;
	stat_action_200ms1 = ((dev->HWJ9592 && dev->HWJ9561) || ((dev->HWJ9571 == 0) && (dev->HWJ9512 && dev->HWJ9561))) && dev->HWJ9562;
	if (stat_action_200ms1 && dev->HWJ9572 == 0){//9572ͣ��
		xql1 = dev->P9561 - dev->P9572;
		xql2 = dev->P9592 + dev->P9572;
		//���²���������ֲ���
		dev->tac.tac_num = 7;
		dev->tac.tac_yq = xql1 + xql2;
		dev->tac.tac_kq = dev->p_all_kq;
		//ϵͳ1���㸺���г���Ϣ
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior_s1, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ1���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1);

		//ϵͳ2���㸺���г���Ϣ
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior_s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ2���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2);

		//������Խ��
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572����
		xql = dev->P9592 + dev->P9561;
		//���²���������ֲ���
		dev->tac.tac_num = 7;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq;
		//ȫ�����㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior_s1s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ȫ�����¸����г���Ϣ
		UpdateCuttedInfo(dev, 3);


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
	float xql, xql1, xql2;
	stat_action_200ms = (dev->HWJ9561 || dev->HWJ9562);
	stat_action_200ms1 = (dev->HWJ9561 && dev->HWJ9562);
	if (stat_action_200ms1 && (dev->HWJ9572 == 0)){//9572ͣ��
		xql1 = dev->P9561 - dev->P9572;
		xql2 = dev->P9562 + dev->P9572;
		//���²���������ֲ���
		dev->tac.tac_num = 8;
		dev->tac.tac_yq = xql1 + xql2;
		dev->tac.tac_kq = dev->p_all_kq;
		//ϵͳ1���㸺���г���Ϣ
		LoadCuttedByPxql(xql1, dev->p_all_kq_s1, dev->p_40_kq_s1, dev->p_prior_s1, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ1���¸����г���Ϣ
		UpdateCuttedInfo(dev, 1);

		//ϵͳ2���㸺���г���Ϣ
		LoadCuttedByPxql(xql2, dev->p_all_kq_s2, dev->p_40_kq_s2, dev->p_prior_s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ϵͳ2���¸����г���Ϣ
		UpdateCuttedInfo(dev, 2);

		//������Խ��
		ExportLoadOutput(dev);
	}else if (stat_action_200ms && dev->HWJ9572){//9572����
		xql = dev->P9562 + dev->P9561;
		//���²���������ֲ���
		dev->tac.tac_num = 8;
		dev->tac.tac_yq = xql;
		dev->tac.tac_kq = dev->p_all_kq;
		//ȫ�����㸺���г���Ϣ
		LoadCuttedByPxql(xql, dev->p_all_kq, dev->p_40_kq, dev->p_prior_s1s2, dev->cutted_prior, MAX_PRIOR, dev->p_qq_setting);
		//ȫ�����¸����г���Ϣ
		UpdateCuttedInfo(dev, 3);


		//������Խ��
		ExportLoadOutput(dev);

	}

	return triggered;
}


//��̬�����ģ�⺯��
void run_tac_simulate(){

//	DEVINFO devdata;
	//1. ��ʼ��
	Initialize(&devdata);
	//2. ��ȡ����
	ReadDevInfo(&devdata);
	//3. ��������Ϣ
	HandleLoadSys(&devdata);	
	CalLoadPByPrior(&devdata);

	//4. ���Լ���
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


