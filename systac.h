//初始化动态库，注册两个回调函数， 指针传递给动态库，
//一个回调函数是取数的接口，另外一个回调函数是策略执行返回结果。

#ifndef SYSTAC_H
#define SYSTAC_H

#include "../include/simulator_define.h"


typedef void (*DATA_HANDLER)(const char* station_code,InputItem *input,uint8 data_num,void *env);
typedef void (*TAC_HANDLER)( const char* station_code,TacOutput *output,uint8 data_num,void *env);

extern "C"{
//输入回调函数
void data_register(DATA_HANDLER data_handler,void *env); //env参数传递给DATA_HANDLER中的env

//输出回调函数
void result_register(TAC_HANDLER tac_handler,void *env); //env参数传递给TAC_HANDLER中的env

//动态库策略模拟函数
void run_tac_simulate();
};

#endif