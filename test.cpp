#include <iostream>
#include "simulator_define.h"
#include "systac.h"
using namespace  std;


void main(){
	InputItem ii;
	ii.fun_num = 3;
	ii.inf_num = 3;
	ii.value = 23;

	run_tac_simulate();


	return;
}