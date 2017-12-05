//��ʼ����̬�⣬ע�������ص������� ָ�봫�ݸ���̬�⣬
//һ���ص�������ȡ���Ľӿڣ�����һ���ص������ǲ���ִ�з��ؽ����

#ifndef SYSTAC_H
#define SYSTAC_H

#include "../include/simulator_define.h"


typedef void (*DATA_HANDLER)(const char* station_code,InputItem *input,uint8 data_num,void *env);
typedef void (*TAC_HANDLER)( const char* station_code,TacOutput *output,uint8 data_num,void *env);

extern "C"{
//����ص�����
void data_register(DATA_HANDLER data_handler,void *env); //env�������ݸ�DATA_HANDLER�е�env

//����ص�����
void result_register(TAC_HANDLER tac_handler,void *env); //env�������ݸ�TAC_HANDLER�е�env

//��̬�����ģ�⺯��
void run_tac_simulate();
};

#endif