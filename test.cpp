#include <iostream>
#include "../include/simulator_define.h"
#include "systac.h"
using namespace  std;


int main(){

#ifdef _DEBUG
	cout << "Find _DEBUG" << endl;
#else
	cout << "NO _DEBUG" << endl;
#endif


	run_tac_simulate();

	return 0 ;
}