#pragma once
#ifndef SIMULATOR_DEFINE
#define SIMLATOR_DEFINE

//typedef unsigned char int;

typedef struct {
	int fun_num;//��Ҫ�Ĳ�����
	int inf_num;//��Ҫ�Ĳ����Ŀ��
	float value;//�����ֵ������ʱ���룩
} InputItem;

typedef struct {
	int fun_num;//���ɵ����
	int inf_num;//������Ŀ��
	bool cutted;//�Ƿ���
} OutputItem;

typedef struct {
	int tac_num;//���Ա��
	float tac_yq;//������
	float tac_kq;//������
	int data_num;//����и��ɸ���
	OutputItem *data;//�и�������
} TacOutput;

#endif //SIMULATOR_DEFINE
