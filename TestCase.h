#ifndef TESTCASE_H
#define TESTCASE_H

#include <string>
#include "DeviceDef.h"

//��������
//inf_stat: ϵͳ״̬�ļ�
//inf_set:  ��ֵ�����ļ�
//dev	:	װ����Ϣ�ṹ��
bool ReadTestCaseFile(std::string& inf_stat, std::string& inf_set, DEVINFO* dev, FAULTINFO* fault);

//���Լ�����
bool SendTacFile(std::string& oufile, DEVINFO* dev);


#endif