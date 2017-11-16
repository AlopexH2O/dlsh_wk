#ifndef SIMULATOR_DEFINE
#define SIMULATOR_DEFINE

typedef unsigned char uint8;

typedef struct {
	uint8 fun_num;//��Ҫ�Ĳ�����
	uint8 inf_num;//��Ҫ�Ĳ����Ŀ��
	float value;//�����ֵ������ʱ���룩
} InputItem;

typedef struct {
	uint8 fun_num;//���ɵ����
	uint8 inf_num;//������Ŀ��
	bool cutted;//�Ƿ���
} OutputItem;

typedef struct {
    char tac_num[8];//���Ա��
	float tac_yq;//������
	float tac_kq;//������
	float tac_pcutted;//�г�������
	uint8 tac_ncutted;//�г�������
	uint8 data_num;//����и��ɸ���
    OutputItem *data;//�и�������
} TacOutput;

#endif //SIMULATOR_DEFINE
