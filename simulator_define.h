#ifndef SIMULATOR_DEFINE
#define SIMULATOR_DEFINE

typedef unsigned char uint8;

typedef struct {
	uint8 fun_num;//需要的测点组号
	uint8 inf_num;//需要的测点条目号
	float value;//测点数值（返回时填入）
} InputItem;

typedef struct {
	uint8 fun_num;//负荷的组号
	uint8 inf_num;//负荷条目号
	bool cutted;//是否被切
} OutputItem;

typedef struct {
    char tac_num[8];//策略编号
	float tac_yq;//需切量
	float tac_kq;//可切量
	float tac_pcutted;//切除负荷量
	uint8 tac_ncutted;//切除负荷线
	uint8 data_num;//输出切负荷个数
    OutputItem *data;//切负荷数据
} TacOutput;

#endif //SIMULATOR_DEFINE
