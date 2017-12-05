#ifndef TESTCASE_H
#define TESTCASE_H

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "DeviceDef.h"

//��������
//inf_stat: ϵͳ״̬�ļ�
//inf_set:  ��ֵ�����ļ�
//dev	:	װ����Ϣ�ṹ��
bool ReadTestCaseFile(const std::string& inf_stat, const std::string& inf_set, DEVINFO* dev, FAULTINFO* fault);

//���Լ�����
bool SendTacFile(const std::string& oufile, DEVINFO* dev);


#endif