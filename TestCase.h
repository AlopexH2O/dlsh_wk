#ifndef TESTCASE_H
#define TESTCASE_H

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "DeviceDef.h"

//读入数据
//inf_stat: 系统状态文件
//inf_set:  定值备份文件
//dev	:	装置信息结构体
bool ReadTestCaseFile(const std::string& inf_stat, const std::string& inf_set, DEVINFO* dev, FAULTINFO* fault);

//策略计算结果
bool SendTacFile(const std::string& oufile, DEVINFO* dev);


#endif