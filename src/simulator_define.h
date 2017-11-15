#pragma once
#ifndef SIMULATOR_DEFINE
#define SIMLATOR_DEFINE

//typedef unsigned char int;

typedef struct {
	int fun_num;//需要的测点组号
	int inf_num;//需要的测点条目号
	float value;//测点数值（返回时填入）
} InputItem;

typedef struct {
	int fun_num;//负荷的组号
	int inf_num;//负荷条目号
	bool cutted;//是否被切
} OutputItem;

typedef struct {
	int tac_num;//策略编号
	float tac_yq;//需切量
	float tac_kq;//可切量
	int data_num;//输出切负荷个数
	OutputItem *data;//切负荷数据
} TacOutput;

#endif //SIMULATOR_DEFINE
