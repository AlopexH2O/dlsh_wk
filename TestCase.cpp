#include <fstream>
#include <ostream>
#include <iostream>
#include <string.h>
#include "TestCase.h"
using namespace std;

bool OutputDevInfo(const string& outfile, DEVINFO* dev, FAULTINFO* fault){
	bool res = false;
	fstream fout;
	fout.open(outfile.c_str(), ios::out);

	if (!fout.is_open()){
		cout << "Error: Failed to write in " << outfile << endl;
		return res;
	}
	res = true;
	fout << endl;
	fout << "===============================系统功率====================================="<< endl
		 << "1#变高功率：" << dev->Sys_P[0].value << endl
		 << "1#变中功率：" << dev->Sys_P[1].value << endl
		 << "2#变高功率：" << dev->Sys_P[2].value << endl
		 << "2#变中功率：" << dev->Sys_P[3].value << endl
		 << "母联9572功率：" << dev->Sys_P[4].value << endl
		 << "化机一线功率：" << dev->Sys_P[5].value << endl
		 << "化机二线功率：" << dev->Sys_P[6].value << endl
		 << "化总二功率：" << dev->Sys_P[7].value << endl
		 << "化总一功率：" << dev->Sys_P[8].value << endl;
	fout << "=============================负荷线路挂载====================================="<< endl
		<< "开关站系统1线路：" << dev->Load_Conn[0].value << endl
		<< "开关站系统2线路：" << dev->Load_Conn[1].value << endl
		<< "二空压系统1线路：" << dev->Load_Conn[2].value << endl
		<< "二空压系统2线路：" << dev->Load_Conn[3].value << endl
		<< "三催化系统1线路1：" << dev->Load_Conn[4].value << endl
		<< "三催化系统1线路2：" << dev->Load_Conn[5].value << endl
		<< "三催化系统2线路1：" << dev->Load_Conn[6].value << endl
		<< "三催化系统2线路2：" << dev->Load_Conn[7].value << endl
		<< "四催化系统1线路1：" << dev->Load_Conn[8].value << endl
		<< "四催化系统1线路2：" << dev->Load_Conn[9].value << endl
		<< "四催化系统2线路1：" << dev->Load_Conn[10].value << endl
		<< "四催化系统2线路2：" << dev->Load_Conn[11].value << endl
		<< "-------------------------------------------------------" << endl;
		for (int i = 0;i < LINE_NUM_KGZ;++i){
			fout << "开关站线路" << i + 1 << ":" << dev->Load_Conn_KGZ[i].value << endl;
		}
		fout << "-------------------------------------------------------" << endl;
		for (int i = 0;i < LINE_NUM_EKY;++i){
			fout << "二空压线路" << i + 1 << ":" << dev->Load_Conn_EKY[i].value << endl;
		}
		fout << "-------------------------------------------------------" << endl;
		for (int i = 0;i < LINE_NUM_CH3;++i){
			fout << "三催化线路" << i + 1 << ":" << dev->Load_Conn_CH3[i].value << endl;
		}
		fout << "-------------------------------------------------------" << endl;
		for (int i = 0;i < LINE_NUM_CH4;++i){
			fout << "四催化线路" << i + 1 << ":" << dev->Load_Conn_CH4[i].value << endl;
		}
	fout << "=============================开关位置信息====================================="<< endl
		<< "系统1联网：" << dev->Sys_Stat[0].value << endl
		<< "系统2联网：" << dev->Sys_Stat[1].value << endl
		<< "系统12联网：" << dev->Sys_Stat[2].value << endl
		<< "9511开关：" << dev->Sys_Stat[3].value << endl
		<< "9512开关：" << dev->Sys_Stat[4].value << endl
		<< "9561开关：" << dev->Sys_Stat[5].value << endl
		<< "9562开关：" << dev->Sys_Stat[6].value << endl
		<< "9591开关：" << dev->Sys_Stat[7].value << endl
		<< "9592开关：" << dev->Sys_Stat[8].value << endl
		<< "9572开关：" << dev->Sys_Stat[9].value << endl
		<< "9573开关：" << dev->Sys_Stat[10].value << endl
		<< "35kVI母归于系统I " << dev->Sys_Stat[11].value << endl
		<< "35kVI母归于系统II " << dev->Sys_Stat[12].value << endl
		<< "35kVII母归于系统I " << dev->Sys_Stat[13].value << endl
		<< "35kVII母归于系统II " << dev->Sys_Stat[14].value << endl;

	fout << "=============================负荷信息====================================="<< endl
		<< "负荷名称\t" << "功率P\t" << "优先级\t" << "系统\t"<< endl
		<< "8012重整一线功率：    " << dev->Load_P[0 ].value << "\t" << dev->Load_Prior[0 ].value << "\t" << dev->Load_Conn_KGZ[0].value <<endl
		<< "8013加氢裂化功率：    " << dev->Load_P[1 ].value << "\t" << dev->Load_Prior[1 ].value << "\t" << dev->Load_Conn_KGZ[1].value<< endl
		<< "8014煤柴加氢功率：    " << dev->Load_P[2 ].value << "\t" << dev->Load_Prior[2 ].value << "\t" << dev->Load_Conn_KGZ[2].value<< endl
		<< "8015渣油加氢功率：    " << dev->Load_P[3 ].value << "\t" << dev->Load_Prior[3 ].value << "\t" << dev->Load_Conn_KGZ[3].value<< endl
		<< "备用线路05功率：      " << dev->Load_P[4 ].value << "\t" << dev->Load_Prior[4 ].value << "\t" << dev->Load_Conn_KGZ[4].value<< endl
		<< "备用线路06功率：      " << dev->Load_P[5 ].value << "\t" << dev->Load_Prior[5 ].value << "\t" << dev->Load_Conn_KGZ[5].value<< endl
		<< "8022重整二线功率：    " << dev->Load_P[6 ].value << "\t" << dev->Load_Prior[6 ].value << "\t" << dev->Load_Conn_KGZ[6].value<< endl
		<< "8023加氢裂化二线功率：" << dev->Load_P[7 ].value << "\t" << dev->Load_Prior[7 ].value << "\t" << dev->Load_Conn_KGZ[7].value<< endl
		<< "8024煤柴加氢二线功率：" << dev->Load_P[8 ].value << "\t" << dev->Load_Prior[8 ].value << "\t" << dev->Load_Conn_KGZ[8].value<< endl
		<< "8025渣油加氢二线功率：" << dev->Load_P[9 ].value << "\t" << dev->Load_Prior[9 ].value << "\t" << dev->Load_Conn_KGZ[9].value<< endl
		<< "备用线路11功率：      " << dev->Load_P[10].value << "\t" << dev->Load_Prior[10].value << "\t" << dev->Load_Conn_KGZ[10].value<< endl
		<< "备用线路12功率：      " << dev->Load_P[11].value << "\t" << dev->Load_Prior[11].value << "\t" << dev->Load_Conn_KGZ[11].value<< endl
		<< "-------------------------------------------------------------" << endl
		<< "3101新沉箱甲线功率：  " << dev->Load_P[12].value << "\t" << dev->Load_Prior[12].value << "\t" << dev->Load_Conn_EKY[0].value<< endl
		<< "3103二循甲线功率：    " << dev->Load_P[13].value << "\t" << dev->Load_Prior[13].value << "\t" << dev->Load_Conn_EKY[1].value<< endl
		<< "3105热力甲线功率：    " << dev->Load_P[14].value << "\t" << dev->Load_Prior[14].value << "\t" << dev->Load_Conn_EKY[2].value<< endl
		<< "备用线路04功率：      " << dev->Load_P[15].value << "\t" << dev->Load_Prior[15].value << "\t" << dev->Load_Conn_EKY[3].value<< endl
		<< "3102新沉箱乙线功率：  " << dev->Load_P[16].value << "\t" << dev->Load_Prior[16].value << "\t" << dev->Load_Conn_EKY[4].value<< endl
		<< "3104二循乙线功率：    " << dev->Load_P[17].value << "\t" << dev->Load_Prior[17].value << "\t" << dev->Load_Conn_EKY[5].value<< endl
		<< "3105热力乙线功率：    " << dev->Load_P[18].value << "\t" << dev->Load_Prior[18].value << "\t" << dev->Load_Conn_EKY[6].value<< endl
		<< "3151功率：            " << dev->Load_P[19].value << "\t" << dev->Load_Prior[19].value << "\t" << dev->Load_Conn_EKY[7].value<< endl
		<< "3152功率：            " << dev->Load_P[20].value << "\t" << dev->Load_Prior[20].value << "\t" << dev->Load_Conn_EKY[8].value<< endl
		<< "-------------------------------------------------------------" << endl
		<< "3557干气甲线功率：    " << dev->Load_P[21].value << "\t" << dev->Load_Prior[21].value << "\t" << dev->Load_Conn_CH3[0].value<< endl
		<< "3558干气乙线功率：    " << dev->Load_P[22].value << "\t" << dev->Load_Prior[22].value << "\t" << dev->Load_Conn_CH3[1].value<< endl
		<< "3605柴油加氢甲线功率：" << dev->Load_P[23].value << "\t" << dev->Load_Prior[23].value << "\t" << dev->Load_Conn_CH3[2].value<< endl
		<< "3607重污油甲线功率：  " << dev->Load_P[24].value << "\t" << dev->Load_Prior[24].value << "\t" << dev->Load_Conn_CH3[3].value<< endl
		<< "3609三催化5#变功率：  " << dev->Load_P[25].value << "\t" << dev->Load_Prior[25].value << "\t" << dev->Load_Conn_CH3[4].value<< endl
		<< "3551（6kV1母）功率：  " << dev->Load_P[26].value << "\t" << dev->Load_Prior[26].value << "\t" << dev->Load_Conn_CH3[5].value<< endl
		<< "3552（6kV2母）功率：  " << dev->Load_P[27].value << "\t" << dev->Load_Prior[27].value << "\t" << dev->Load_Conn_CH3[6].value<< endl
		<< "3651（6kV3母）功率：  " << dev->Load_P[28].value << "\t" << dev->Load_Prior[28].value << "\t" << dev->Load_Conn_CH3[7].value<< endl
		<< "3569启动变功率：      " << dev->Load_P[29].value << "\t" << dev->Load_Prior[29].value << "\t" << dev->Load_Conn_CH3[8].value<< endl
		<< "3606柴油加氢乙线功率：" << dev->Load_P[30].value << "\t" << dev->Load_Prior[30].value << "\t" << dev->Load_Conn_CH3[9].value<< endl
		<< "3608重污油乙功率：    " << dev->Load_P[31].value << "\t" << dev->Load_Prior[31].value << "\t" << dev->Load_Conn_CH3[10].value<< endl
		<< "3611富氢甲功率：      " << dev->Load_P[32].value << "\t" << dev->Load_Prior[32].value << "\t" << dev->Load_Conn_CH3[11].value<< endl
		<< "3615氢压机甲功率：    " << dev->Load_P[33].value << "\t" << dev->Load_Prior[33].value << "\t" << dev->Load_Conn_CH3[12].value<< endl
		<< "3617柴升甲功率：      " << dev->Load_P[34].value << "\t" << dev->Load_Prior[34].value << "\t" << dev->Load_Conn_CH3[13].value<< endl
		<< "3612富氢乙功率：      " << dev->Load_P[35].value << "\t" << dev->Load_Prior[35].value << "\t" << dev->Load_Conn_CH3[14].value<< endl
		<< "3616氢压机乙功率：    " << dev->Load_P[36].value << "\t" << dev->Load_Prior[36].value << "\t" << dev->Load_Conn_CH3[15].value<< endl
		<< "3618柴升乙功率：      " << dev->Load_P[37].value << "\t" << dev->Load_Prior[37].value << "\t" << dev->Load_Conn_CH3[16].value<< endl
		<< "3653（6kV5母）功率：  " << dev->Load_P[38].value << "\t" << dev->Load_Prior[38].value << "\t" << dev->Load_Conn_CH3[17].value<< endl
		<< "3654（6kV6母）功率：  " << dev->Load_P[39].value << "\t" << dev->Load_Prior[39].value << "\t" << dev->Load_Conn_CH3[18].value<< endl
		<< "3652（6kV4母）功率：  " << dev->Load_P[40].value << "\t" << dev->Load_Prior[40].value << "\t" << dev->Load_Conn_CH3[19].value<< endl
		<< "-------------------------------------------------------------" << endl
		<< "3903中水甲线功率：    " << dev->Load_P[41].value << "\t" << dev->Load_Prior[41].value << "\t" << dev->Load_Conn_CH4[0].value<< endl
		<< "3905管控甲线功率：    " << dev->Load_P[42].value << "\t" << dev->Load_Prior[42].value << "\t" << dev->Load_Conn_CH4[1].value<< endl
		<< "备用线路03功率：      " << dev->Load_P[43].value << "\t" << dev->Load_Prior[43].value << "\t" << dev->Load_Conn_CH4[2].value<< endl
		<< "3904中水乙线功率：    " << dev->Load_P[44].value << "\t" << dev->Load_Prior[44].value << "\t" << dev->Load_Conn_CH4[3].value<< endl
		<< "3906管控乙线功率：    " << dev->Load_P[45].value << "\t" << dev->Load_Prior[45].value << "\t" << dev->Load_Conn_CH4[4].value<< endl
		<< "备用功率1：           " << dev->Load_P[46].value << "\t" << dev->Load_Prior[46].value << "\t" << dev->Load_Conn_CH4[5].value<< endl
		<< "3953功率：            " << dev->Load_P[47].value << "\t" << dev->Load_Prior[47].value << "\t" << dev->Load_Conn_CH4[6].value<< endl
		<< "3954功率：            " << dev->Load_P[48].value << "\t" << dev->Load_Prior[48].value << "\t" << dev->Load_Conn_CH4[7].value<< endl
		<< "3931功率：            " << dev->Load_P[49].value << "\t" << dev->Load_Prior[49].value << "\t" << dev->Load_Conn_CH4[8].value<< endl
		<< "3941功率：            " << dev->Load_P[50].value << "\t" << dev->Load_Prior[50].value << "\t" << dev->Load_Conn_CH4[9].value<< endl
		<< "4801中间罐甲线功率：  " << dev->Load_P[51].value << "\t" << dev->Load_Prior[51].value << "\t" << dev->Load_Conn_CH4[10].value<< endl
		<< "备用功率2：           " << dev->Load_P[52].value << "\t" << dev->Load_Prior[52].value << "\t" << dev->Load_Conn_CH4[11].value<< endl
		<< "备用功率3：           " << dev->Load_P[53].value << "\t" << dev->Load_Prior[53].value << "\t" << dev->Load_Conn_CH4[12].value<< endl
		<< "备用功率4：           " << dev->Load_P[54].value << "\t" << dev->Load_Prior[54].value << "\t" << dev->Load_Conn_CH4[13].value<< endl
		<< "备用功率5：           " << dev->Load_P[55].value << "\t" << dev->Load_Prior[55].value << "\t" << dev->Load_Conn_CH4[14].value<< endl
		<< "4802中间罐乙线功率：  " << dev->Load_P[56].value << "\t" << dev->Load_Prior[56].value << "\t" << dev->Load_Conn_CH4[15].value<< endl
		<< "备用功率6：           " << dev->Load_P[57].value << "\t" << dev->Load_Prior[57].value << "\t" << dev->Load_Conn_CH4[16].value<< endl
		<< "备用功率7：           " << dev->Load_P[58].value << "\t" << dev->Load_Prior[58].value << "\t" << dev->Load_Conn_CH4[17].value<< endl
		<< "备用功率8：           " << dev->Load_P[59].value << "\t" << dev->Load_Prior[59].value << "\t" << dev->Load_Conn_CH4[18].value<< endl
		<< "备用功率9：           " << dev->Load_P[60].value << "\t" << dev->Load_Prior[60].value << "\t" << dev->Load_Conn_CH4[19].value<< endl
		<< "4851功率10：          " << dev->Load_P[61].value << "\t" << dev->Load_Prior[61].value << "\t" << dev->Load_Conn_CH4[20].value<< endl
		<< "4852功率11：          " << dev->Load_P[62].value << "\t" << dev->Load_Prior[62].value << "\t" << dev->Load_Conn_CH4[21].value<< endl;

	fout << "===============================定值======================================"<< endl
		<< "频稳欠切功率定值：" << dev->Load_Prior[63].value << endl;

	fout << "===============================故障信息==================================" << endl
		 << "9511:" << int(dev->HWJ9511) << "\t" << int(fault->T9511) << endl
		 << "9512:" << int(dev->HWJ9512) << "\t" << int(fault->T9512) << endl
		 << "9591:" << int(dev->HWJ9591) << "\t" << int(fault->T9591) << endl
		 << "9592:" << int(dev->HWJ9592) << "\t" << int(fault->T9592) << endl
		 << "9561:" << int(dev->HWJ9561) << "\t" << int(fault->T9561) << endl
		 << "9562:" << int(dev->HWJ9562) << "\t" << int(fault->T9562) << endl
		 << "9572:" << int(dev->HWJ9572) << "\t" << int(fault->T9572) << endl
		 << "开关站系统1："<< int(fault->FT_KGZ_S1) << endl
		 << "开关站系统2："<< int(fault->FT_KGZ_S2) << endl
		 << "二空压系统1："<< int(fault->FT_EKY_S1) << endl
		 << "二空压系统2："<< int(fault->FT_EKY_S2) << endl
		 << "三催化系统1："<< int(fault->FT_CH3_S1) << endl
		 << "三催化系统2："<< int(fault->FT_CH3_S2) << endl
		 << "四催化系统1："<< int(fault->FT_CH4_S1) << endl
		 << "四催化系统2："<< int(fault->FT_CH4_S2) << endl;
		 
		 
		 fout.close();

	return res;
}

//读入装置文件
bool ReadTestCaseFile(const string& inf_stat, const string& inf_set, DEVINFO* dev, FAULTINFO* fault){
	bool res = false;
	fstream fstat;
	//fstream fset;
	fstat.open(inf_stat.c_str(), ios::in);
	//fset.open(inf_set.c_str(), ios::in);
	if (!fstat.is_open()){
		cout << "Error: Failed in Opening file!" << endl;
		return res;
	}
	string s;
	string value;
	while (fstat >> s){
		if(s == "1#变高功率："){
			fstat >> value;
			dev->Sys_P[0].value = atof(value.c_str());
			continue;
		}
		if(s == "1#变中功率："){
			fstat >> value;
			dev->Sys_P[1].value = atof(value.c_str());
			continue;
		}
		if(s == "2#变高功率："){
			fstat >> value;
			dev->Sys_P[2].value = atof(value.c_str());
			continue;
		}
		if(s == "2#变中功率："){
			fstat >> value;
			dev->Sys_P[3].value = atof(value.c_str());
			continue;
		}
		if(s == "66kV母联9572功率："){
			fstat >> value;
			dev->Sys_P[4].value = atof(value.c_str());
			continue;
		}
		if(s == "化机一线功率："){
			fstat >> value;
			dev->Sys_P[5].value = atof(value.c_str());
			continue;
		}
		if(s == "化机二线功率："){
			fstat >> value;
			dev->Sys_P[6].value = atof(value.c_str());
			continue;
		}
		if(s == "化总一功率："){
			fstat >> value;
			dev->Sys_P[7].value = atof(value.c_str());
			continue;
		}
		if(s == "化总二功率："){
			fstat >> value;
			dev->Sys_P[8].value = atof(value.c_str());
			continue;
		}
		if(s == "开关站系统1线路："){
			fstat >> value;
			dev->Sys_Stat[0].value = atof(value.c_str());
			continue;
		}
		if(s == "开关站系统2线路："){
			fstat >> value;
			dev->Sys_Stat[1].value = atof(value.c_str());
			continue;
		}
		if(s == "二空压系统1线路："){
			fstat >> value;
			dev->Sys_Stat[2].value = atof(value.c_str());
			continue;
		}
		if(s == "二空压系统2线路："){
			fstat >> value;
			dev->Sys_Stat[3].value = atof(value.c_str());
			continue;
		}
		if(s == "三催化系统1线路1："){
			fstat >> value;
			dev->Sys_Stat[4].value = atof(value.c_str());
			continue;
		}
		if(s == "三催化系统1线路2："){
			fstat >> value;
			dev->Sys_Stat[5].value = atof(value.c_str());
			continue;
		}
		if(s == "三催化系统2线路1："){
			fstat >> value;
			dev->Sys_Stat[6].value = atof(value.c_str());
			continue;
		}
		if(s == "三催化系统2线路2："){
			fstat >> value;
			dev->Sys_Stat[7].value = atof(value.c_str());
			continue;
		}
		if(s == "四催化系统1线路1："){
			fstat >> value;
			dev->Sys_Stat[8].value = atof(value.c_str());
			continue;
		}
		if(s == "四催化系统1线路2："){
			fstat >> value;
			dev->Sys_Stat[9].value = atof(value.c_str());
			continue;
		}
		if(s == "四催化系统2线路1："){
			fstat >> value;
			dev->Sys_Stat[10].value = atof(value.c_str());
			continue;
		}
		if(s == "四催化系统2线路2："){
			fstat >> value;
			dev->Sys_Stat[11].value = atof(value.c_str());
			continue;
		}
		//线路功率
		int byxl = 0;
		if(s == "8012重整一线功率："){
			fstat >> value;
			dev->Load_P[0].value = atof(value.c_str());
			continue;
		}
		if(s == "8013加氢裂化功率："){
			fstat >> value;
			dev->Load_P[1].value = atof(value.c_str());
			continue;
		}
		if(s == "8014煤柴加氢功率："){
			fstat >> value;
			dev->Load_P[2].value = atof(value.c_str());
			continue;
		}
		if(s == "8015渣油加氢功率："){
			fstat >> value;
			dev->Load_P[3].value = atof(value.c_str());
			continue;
		}
		if(s == "备用线路05功率："){
			fstat >> value;
			dev->Load_P[4].value = atof(value.c_str());
			continue;
		}
		if(s == "备用线路06功率："){
			fstat >> value;
			dev->Load_P[5].value = atof(value.c_str());
			continue;
		}
		if(s == "8022重整二线功率："){
			fstat >> value;
			dev->Load_P[6].value = atof(value.c_str());
			continue;
		}
		if(s == "8023加氢裂化二线功率："){
			fstat >> value;
			dev->Load_P[7].value = atof(value.c_str());
			continue;
		}
		if(s == "8024煤柴加氢二线功率："){
			fstat >> value;
			dev->Load_P[8].value = atof(value.c_str());
			continue;
		}
		if(s == "8025渣油加氢二线功率："){
			fstat >> value;
			dev->Load_P[9].value = atof(value.c_str());
			continue;
		}
		if(s == "备用线路11功率："){
			fstat >> value;
			dev->Load_P[10].value = atof(value.c_str());
			continue;
		}
		if(s == "备用线路12功率："){
			fstat >> value;
			dev->Load_P[11].value = atof(value.c_str());
			continue;
		}
		if(s == "3101新沉箱甲线功率："){
			fstat >> value;
			dev->Load_P[12].value = atof(value.c_str());
			continue;
		}
		if(s == "3103二循甲线功率："){
			fstat >> value;
			dev->Load_P[13].value = atof(value.c_str());
			continue;
		}
		if(s == "3105热力甲线功率："){
			fstat >> value;
			dev->Load_P[14].value = atof(value.c_str());
			continue;
		}
		if(s == "备用线路04功率："){
			fstat >> value;
			dev->Load_P[15].value = atof(value.c_str());
			continue;
		}
		if(s == "3102新沉箱乙线功率："){
			fstat >> value;
			dev->Load_P[16].value = atof(value.c_str());
			continue;
		}
		if(s == "3104二循乙线功率："){
			fstat >> value;
			dev->Load_P[17].value = atof(value.c_str());
			continue;
		}
		if(s == "3105热力乙线功率："){
			fstat >> value;
			dev->Load_P[18].value = atof(value.c_str());
			continue;
		}
		if(s == "3151功率："){
			fstat >> value;
			dev->Load_P[19].value = atof(value.c_str());
			continue;
		}
		if(s == "3152功率："){
			fstat >> value;
			dev->Load_P[20].value = atof(value.c_str());
			continue;
		}
		if(s == "3557干气甲线功率："){
			fstat >> value;
			dev->Load_P[21].value = atof(value.c_str());
			continue;
		}
		if(s == "3558干气乙线功率："){
			fstat >> value;
			dev->Load_P[22].value = atof(value.c_str());
			continue;
		}
		if(s == "3605柴油加氢甲线功率："){
			fstat >> value;
			dev->Load_P[23].value = atof(value.c_str());
			continue;
		}
		if(s == "3607重污油甲线功率："){
			fstat >> value;
			dev->Load_P[24].value = atof(value.c_str());
			continue;
		}
		if(s == "3609三催化5#变功率："){
			fstat >> value;
			dev->Load_P[25].value = atof(value.c_str());
			continue;
		}
		if(s == "3551（6kV1母）功率："){
			fstat >> value;
			dev->Load_P[26].value = atof(value.c_str());
			continue;
		}
		if(s == "3552（6kV2母）功率："){
			fstat >> value;
			dev->Load_P[27].value = atof(value.c_str());
			continue;
		}
		if(s == "3651（6kV3母）功率："){
			fstat >> value;
			dev->Load_P[28].value = atof(value.c_str());
			continue;
		}
		if(s == "3569启动变功率："){
			fstat >> value;
			dev->Load_P[29].value = atof(value.c_str());
			continue;
		}
		if(s == "3606柴油加氢乙线功率："){
			fstat >> value;
			dev->Load_P[30].value = atof(value.c_str());
			continue;
		}
		if(s == "3608重污油乙功率："){
			fstat >> value;
			dev->Load_P[31].value = atof(value.c_str());
			continue;
		}
		if(s == "3611富氢甲功率："){
			fstat >> value;
			dev->Load_P[32].value = atof(value.c_str());
			continue;
		}
		if(s == "3615氢压机甲功率："){
			fstat >> value;
			dev->Load_P[33].value = atof(value.c_str());
			continue;
		}
		if(s == "3617柴升甲功率："){
			fstat >> value;
			dev->Load_P[34].value = atof(value.c_str());
			continue;
		}
		if(s == "3612富氢乙功率："){
			fstat >> value;
			dev->Load_P[35].value = atof(value.c_str());
			continue;
		}
		if(s == "3616氢压机乙功率："){
			fstat >> value;
			dev->Load_P[36].value = atof(value.c_str());
			continue;
		}
		if(s == "3618柴升乙功率："){
			fstat >> value;
			dev->Load_P[37].value = atof(value.c_str());
			continue;
		}
		if(s == "3653（6kV5母）功率："){
			fstat >> value;
			dev->Load_P[38].value = atof(value.c_str());
			continue;
		}
		if(s == "3654（6kV6母）功率："){
			fstat >> value;
			dev->Load_P[39].value = atof(value.c_str());
			continue;
		}
		if(s == "3652（6kV4母）功率："){
			fstat >> value;
			dev->Load_P[40].value = atof(value.c_str());
			continue;
		}
		if(s == "3903中水甲线功率："){
			fstat >> value;
			dev->Load_P[41].value = atof(value.c_str());
			continue;
		}
		if(s == "3905管控甲线功率："){
			fstat >> value;
			dev->Load_P[42].value = atof(value.c_str());
			continue;
		}
		if(s == "备用线路03功率："){
			fstat >> value;
			dev->Load_P[43].value = atof(value.c_str());
			continue;
		}
		if(s == "3904中水乙线功率："){
			fstat >> value;
			dev->Load_P[44].value = atof(value.c_str());
			continue;
		}
		if(s == "3906管控乙线功率："){
			fstat >> value;
			dev->Load_P[45].value = atof(value.c_str());
			continue;
		}
		if(s == "备用功率1："){
			fstat >> value;
			dev->Load_P[46].value = atof(value.c_str());
			continue;
		}
		if(s == "3953功率："){
			fstat >> value;
			dev->Load_P[47].value = atof(value.c_str());
			continue;
		}
		if(s == "3954功率："){
			fstat >> value;
			dev->Load_P[48].value = atof(value.c_str());
			continue;
		}
		if(s == "3931功率："){
			fstat >> value;
			dev->Load_P[49].value = atof(value.c_str());
			continue;
		}
		if(s == "3941功率："){
			fstat >> value;
			dev->Load_P[50].value = atof(value.c_str());
			continue;
		}
		if(s == "4801中间罐甲线功率："){
			fstat >> value;
			dev->Load_P[51].value = atof(value.c_str());
			continue;
		}
		if(s == "备用功率2："){
			fstat >> value;
			dev->Load_P[52].value = atof(value.c_str());
			continue;
		}
		if(s == "备用功率3："){
			fstat >> value;
			dev->Load_P[53].value = atof(value.c_str());
			continue;
		}
		if(s == "备用功率4："){
			fstat >> value;
			dev->Load_P[54].value = atof(value.c_str());
			continue;
		}
		if(s == "备用功率5："){
			fstat >> value;
			dev->Load_P[55].value = atof(value.c_str());
			continue;
		}
		if(s == "4802中间罐乙线功率："){
			fstat >> value;
			dev->Load_P[56].value = atof(value.c_str());
			continue;
		}
		if(s == "备用功率6："){
			fstat >> value;
			dev->Load_P[57].value = atof(value.c_str());
			continue;
		}
		if(s == "备用功率7："){
			fstat >> value;
			dev->Load_P[58].value = atof(value.c_str());
			continue;
		}
		if(s == "备用功率8："){
			fstat >> value;
			dev->Load_P[59].value = atof(value.c_str());
			continue;
		}
		if(s == "备用功率9："){
			fstat >> value;
			dev->Load_P[60].value = atof(value.c_str());
			continue;
		}
		if(s == "4851功率10："){
			fstat >> value;
			dev->Load_P[61].value = atof(value.c_str());
			continue;
		}
		if(s == "4852功率11："){
			fstat >> value;
			dev->Load_P[62].value = atof(value.c_str());
			continue;
		}

		//系统开关量状态
		if(s == "系统1联网："){
			fstat >> value;
			dev->Sys_Stat[0].value = atof(value.c_str());
			continue;
		}
		if(s == "系统2联网："){
			fstat >> value;
			dev->Sys_Stat[1].value = atof(value.c_str());
			continue;
		}
		if(s == "系统12互联联网："){
			fstat >> value;
			dev->Sys_Stat[2].value = atof(value.c_str());
			continue;
		}
		if(s == "9511开关运行："){
			fstat >> value;
			dev->Sys_Stat[3].value = atof(value.c_str());
			continue;
		}
		if(s == "9512开关运行："){
			fstat >> value;
			dev->Sys_Stat[4].value = atof(value.c_str());
			continue;
		}
		if(s == "9561开关运行："){
			fstat >> value;
			dev->Sys_Stat[5].value = atof(value.c_str());
			continue;
		}
		if(s == "9562开关运行："){
			fstat >> value;
			dev->Sys_Stat[6].value = atof(value.c_str());
			continue;
		}
		if(s == "9591开关运行："){
			fstat >> value;
			dev->Sys_Stat[7].value = atof(value.c_str());
			continue;
		}
		if(s == "9592开关运行："){
			fstat >> value;
			dev->Sys_Stat[8].value = atof(value.c_str());
			continue;
		}
		if(s == "9572开关运行："){
			fstat >> value;
			dev->Sys_Stat[9].value = atof(value.c_str());
			continue;
		}
		if(s == "35kVI母归于系统I："){
			fstat >> value;
			dev->Sys_Stat[11].value = atof(value.c_str());
			continue;
		}
		if(s == "35kVI母归于系统II："){
			fstat >> value;
			dev->Sys_Stat[12].value = atof(value.c_str());
			continue;
		}
		if(s == "35kVII母归于系统I："){
			fstat >> value;
			dev->Sys_Stat[13].value = atof(value.c_str());
			continue;
		}
		if(s == "35kVII母归于系统II："){
			fstat >> value;
			dev->Sys_Stat[14].value = atof(value.c_str());
			continue;
		}





	}//end while fot stat
	fstat.close();

	int stcode = 0;
	int stcoden = 0;
	FILE* fset = fopen(inf_set.c_str(), "r");
	if (fset == NULL){
		cout << "Error in reading file " << inf_set << endl;
		return false;
	}

	char ss[128] = "";
	float ff;
	int   tmp;

	while (!feof(fset)){
		fscanf(fset, "%s", ss);

		
		if(!strcmp(ss, "石化变故障状态:")){
			fscanf(fset, "%x", &tmp);
			//fset >> value;
			//int tmp = atoi(value.c_str());
			fault->T9511 = uint8(tmp & 0x1);
			fault->T9512 = uint8((tmp >> 1) & 0x1);
			fault->T9591 = uint8((tmp >> 2) & 0x1);
			fault->T9561 = uint8((tmp >> 3) & 0x1);
			fault->T9592 = uint8((tmp >> 4) & 0x1);
			fault->T9562 = uint8((tmp >> 5) & 0x1);
			fault->T9572 = uint8((tmp >> 6) & 0x1);			
			continue;
		}

		if(!strcmp(ss, "模拟站故障频率:")){
		//if(s == "模拟站故障频率:"){
			fscanf(fset, "%x", &tmp);
			//fset >> value;
			//int tmp = atoi(value.c_str());
			fault->FT_KGZ_S1 = uint8(tmp & 0x1);
			fault->FT_KGZ_S2 = uint8((tmp >> 1) & 0x1);
			fault->FT_EKY_S1 = uint8((tmp >> 2) & 0x1);
			fault->FT_EKY_S2 = uint8((tmp >> 3) & 0x1);
			fault->FT_CH3_S1 = uint8((tmp >> 4) & 0x1);
			fault->FT_CH3_S2 = uint8((tmp >> 5) & 0x1);
			fault->FT_CH4_S1 = uint8((tmp >> 6) & 0x1);			
			fault->FT_CH4_S2 = uint8((tmp >> 7) & 0x1);			
			continue;
		}

		if(!strcmp(ss, "开关站线路01优先级:")){
//		if(s == "开关站线路01优先级:"){
			fscanf(fset, "%f", &ff);
			//fset >> value;
			dev->Load_Prior[0].value = ff;
			continue;
		}
		if(!strcmp(ss, "开关站线路02优先级:")){
//		if(s == "开关站线路02优先级:"){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[1].value = ff;
			continue;
		}		
		if(!strcmp(ss, "开关站线路03优先级:")){
//		if(s == "开关站线路03优先级:"){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[2].value = ff;
			continue;
		}		
		if(!strcmp(ss, "开关站线路04优先级:")){
//		if(s == "开关站线路04优先级:"){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[3].value = ff;
			continue;
		}	
		if(!strcmp(ss, "开关站线路05优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[4].value = ff;
			continue;
		}	
		if(!strcmp(ss, "开关站线路06优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[5].value = ff;
			continue;
		}	
		if(!strcmp(ss, "开关站线路07优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[6].value = ff;
			continue;
		}	
		if(!strcmp(ss, "开关站线路08优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[7].value = ff;
			continue;
		}	
		if(!strcmp(ss, "开关站线路09优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[8].value = ff;
			continue;
		}
		if(!strcmp(ss, "开关站线路10优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[9].value = ff;
			continue;
		}
		if(!strcmp(ss, "开关站线路11优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[10].value = ff;
			continue;
		}
		if(!strcmp(ss, "开关站线路12优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[11].value = atof(value.c_str());
			continue;
		}
		if(!strcmp(ss, "二空压线路01优先级:")){
//		if(s == "二空压线路01优先级:"){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[12].value = ff;
			continue;
		}
		if(!strcmp(ss, "二空压线路02优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[13].value = ff;
			continue;
		}
		if(!strcmp(ss, "二空压线路03优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[14].value = ff;
			continue;
		}
		if(!strcmp(ss, "二空压线路04优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[15].value = ff;
			continue;
		}
		if(!strcmp(ss, "二空压线路05优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[16].value = ff;
			continue;
		}
		if(!strcmp(ss, "二空压线路06优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[17].value = ff;
			continue;
		}
		if(!strcmp(ss, "二空压线路07优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[18].value = ff;
			continue;
		}
		if(!strcmp(ss, "二空压线路08优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[19].value = ff;
			continue;
		}
		if(!strcmp(ss, "二空压线路09优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[20].value = ff;
			continue;
		}
		//三催化线路
		if(!strcmp(ss, "三催化线路01优先级:")){
			fscanf(fset, "%f", &ff);
//		if(s == "三催化线路01优先级:"){
//			fset >> value;
			dev->Load_Prior[21].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路02优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[22].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路03优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[23].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路04优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[24].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路05优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[25].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路06优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[26].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路07优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[27].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路08优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[28].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路09优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[29].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路10优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[30].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路11优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[31].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路12优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[32].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路13优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[33].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路14优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[34].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路15优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[35].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路16优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[36].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路17优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[37].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路18优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[38].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路19优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[39].value = ff;
			continue;
		}
		if(!strcmp(ss, "三催化线路20优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[40].value = ff;
			continue;
		}
		//四催化
		if(!strcmp(ss, "四催化三蒸馏线路01优先级:")){
			fscanf(fset, "%f", &ff);
//		if(s == "四催化三蒸馏线路01优先级:"){
//			fset >> value;
			dev->Load_Prior[41].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路02优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[43].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路03优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[43].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路04优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[44].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路05优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[45].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路06优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[46].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路07优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[47].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路08优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[48].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路09优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[49].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路10优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[50].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路11优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[51].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路12优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[52].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路13优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[53].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路14优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[54].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路15优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[55].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路16优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[56].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路17优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[57].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路18优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[58].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路19优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[59].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路20优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[60].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路21优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[61].value = ff;
			continue;
		}
		if(!strcmp(ss, "四催化三蒸馏线路22优先级:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[62].value = ff;
			continue;
		}
//		if(s == "频稳欠切功率定值:"){
		if(!strcmp(ss, "频稳欠切功率定值:")){
			fscanf(fset, "%f", &ff);
			dev->Load_Prior[63].value = ff;
			continue;
		}
//		if(s == "母线归属状态:"){//母线归属状态默认是9571开关状态
		if(!strcmp(ss, "母线归属状态:")){
			fscanf(fset, "%x", &tmp);
			dev->Load_Conn_SHZ[0].value = float((tmp >> 12) & 0x1);
			continue;
		}

		
//		if(s == "模拟站M试验:"){
//			fset >> value;
		if(!strcmp(ss, "模拟站M试验:")){
			fscanf(fset, "%d", &tmp);
			stcode = tmp;
			continue;
		}

//		if(s == "执行站M负荷1归属:"){
//			fset >> value;
		if(!strcmp(ss, "执行站M负荷1归属:")){
			fscanf(fset, "%f", &ff);
			if (stcode == 1){//开关站
				dev->Load_Conn_KGZ[0].value = ff;
			}else if (stcode == 2){//二空压
				dev->Load_Conn_EKY[0].value = ff;
			}else if (stcode == 3){//三催化
				dev->Load_Conn_CH3[0].value = ff;
			}else if (stcode == 4){//三催化
				dev->Load_Conn_CH4[0].value = ff;
			}
			continue;
		}
		if(!strcmp(ss, "执行站M负荷2归属:")){
			fscanf(fset, "%f", &ff);
			if (stcode == 1){//开关站
				dev->Load_Conn_KGZ[1].value = ff;
			}else if (stcode == 2){//二空压
				dev->Load_Conn_EKY[1].value = ff;
			}else if (stcode == 3){//三催化
				dev->Load_Conn_CH3[1].value = ff;
			}else if (stcode == 4){//三催化
				dev->Load_Conn_CH4[1].value = ff;
			}
			continue;
		}
		if(!strcmp(ss, "执行站M负荷3归属:")){
			fscanf(fset, "%f", &ff);
			if (stcode == 1){//开关站
				dev->Load_Conn_KGZ[2].value = ff;
			}else if (stcode == 2){//二空压
				dev->Load_Conn_EKY[2].value = ff;
			}else if (stcode == 3){//三催化
				dev->Load_Conn_CH3[2].value = ff;
			}else if (stcode == 4){//三催化
				dev->Load_Conn_CH4[2].value = ff;
			}
			continue;
		}
		if(!strcmp(ss, "执行站M负荷4归属:")){
			fscanf(fset, "%f", &ff);
			if (stcode == 1){//开关站
				dev->Load_Conn_KGZ[3].value = ff;
			}else if (stcode == 2){//二空压
				dev->Load_Conn_EKY[3].value = ff;
			}else if (stcode == 3){//三催化
				dev->Load_Conn_CH3[3].value = ff;
			}else if (stcode == 4){//三催化
				dev->Load_Conn_CH4[3].value = ff;
			}
			continue;
		}
		if(!strcmp(ss, "执行站M负荷5归属:")){
			fscanf(fset, "%f", &ff);
			if (stcode == 1){//开关站
				dev->Load_Conn_KGZ[4].value = ff;
			}else if (stcode == 2){//二空压
				dev->Load_Conn_EKY[4].value = ff;
			}else if (stcode == 3){//三催化
				dev->Load_Conn_CH3[4].value = ff;
			}else if (stcode == 4){//三催化
				dev->Load_Conn_CH4[4].value = ff;
			}
			continue;
		}
		if(!strcmp(ss, "执行站M负荷6归属:")){
			fscanf(fset, "%f", &ff);
			if (stcode == 1){//开关站
				dev->Load_Conn_KGZ[5].value = ff;
			}else if (stcode == 2){//二空压
				dev->Load_Conn_EKY[5].value = ff;
			}else if (stcode == 3){//三催化
				dev->Load_Conn_CH3[5].value = ff;
			}else if (stcode == 4){//三催化
				dev->Load_Conn_CH4[5].value = ff;
			}
			continue;
		}
		if(!strcmp(ss, "执行站M负荷7归属:")){
			fscanf(fset, "%f", &ff);
			if (stcode == 1){//开关站
				dev->Load_Conn_KGZ[6].value = ff;
			}else if (stcode == 2){//二空压
				dev->Load_Conn_EKY[6].value = ff;
			}else if (stcode == 3){//三催化
				dev->Load_Conn_CH3[6].value = ff;
			}else if (stcode == 4){//三催化
				dev->Load_Conn_CH4[6].value = ff;
			}
			continue;
		}
		if(!strcmp(ss, "执行站M负荷8归属:")){
			fscanf(fset, "%f", &ff);
			if (stcode == 1){//开关站
				dev->Load_Conn_KGZ[7].value = ff;
			}else if (stcode == 2){//二空压
				dev->Load_Conn_EKY[7].value = ff;
			}else if (stcode == 3){//三催化
				dev->Load_Conn_CH3[7].value = ff;
			}else if (stcode == 4){//三催化
				dev->Load_Conn_CH4[7].value = ff;
			}
			continue;
		}

		if(!strcmp(ss, "模拟站N试验:")){
			fscanf(fset, "%d", &tmp);
			stcoden = tmp;
			continue;
		}

		if(!strcmp(ss, "执行站N负荷1归属:")){
			fscanf(fset, "%f", &ff);
			if (stcoden == 1){//开关站
				dev->Load_Conn_KGZ[0].value = ff;
			}else if (stcoden == 2){//二空压
				dev->Load_Conn_EKY[0].value = ff;
			}else if (stcoden == 3){//三催化
				dev->Load_Conn_CH3[0].value = ff;
			}else if (stcoden == 4){//三催化
				dev->Load_Conn_CH4[0].value = ff;
			}
			continue;
		}
		if(!strcmp(ss, "执行站N负荷2归属:")){
			fscanf(fset, "%f", &ff);
			if (stcoden == 1){//开关站
				dev->Load_Conn_KGZ[1].value = ff;
			}else if (stcoden == 2){//二空压
				dev->Load_Conn_EKY[1].value = ff;
			}else if (stcoden == 3){//三催化
				dev->Load_Conn_CH3[1].value = ff;
			}else if (stcoden == 4){//三催化
				dev->Load_Conn_CH4[1].value = ff;
			}
			continue;
		}
		if(!strcmp(ss, "执行站N负荷3归属:")){
			fscanf(fset, "%f", &ff);
			if (stcoden == 1){//开关站
				dev->Load_Conn_KGZ[2].value = ff;
			}else if (stcoden == 2){//二空压
				dev->Load_Conn_EKY[2].value = ff;
			}else if (stcoden == 3){//三催化
				dev->Load_Conn_CH3[2].value = ff;
			}else if (stcoden == 4){//三催化
				dev->Load_Conn_CH4[2].value = ff;
			}
			continue;
		}
		if(!strcmp(ss, "执行站N负荷4归属:")){
			fscanf(fset, "%f", &ff);
			if (stcoden == 1){//开关站
				dev->Load_Conn_KGZ[3].value = ff;
			}else if (stcoden == 2){//二空压
				dev->Load_Conn_EKY[3].value = ff;
			}else if (stcoden == 3){//三催化
				dev->Load_Conn_CH3[3].value = ff;
			}else if (stcoden == 4){//三催化
				dev->Load_Conn_CH4[3].value = ff;
			}
			continue;
		}
		if(!strcmp(ss, "执行站N负荷5归属:")){
			fscanf(fset, "%f", &ff);
			if (stcoden == 1){//开关站
				dev->Load_Conn_KGZ[4].value = ff;
			}else if (stcoden == 2){//二空压
				dev->Load_Conn_EKY[4].value = ff;
			}else if (stcoden == 3){//三催化
				dev->Load_Conn_CH3[4].value = ff;
			}else if (stcoden == 4){//三催化
				dev->Load_Conn_CH4[4].value = ff;
			}
			continue;
		}
		if(!strcmp(ss, "执行站N负荷6归属:")){
			fscanf(fset, "%f", &ff);
			if (stcoden == 1){//开关站
				dev->Load_Conn_KGZ[5].value = ff;
			}else if (stcoden == 2){//二空压
				dev->Load_Conn_EKY[5].value = ff;
			}else if (stcoden == 3){//三催化
				dev->Load_Conn_CH3[5].value = ff;
			}else if (stcoden == 4){//三催化
				dev->Load_Conn_CH4[5].value = ff;
			}
			continue;
		}
		if(!strcmp(ss, "执行站N负荷7归属:")){
			fscanf(fset, "%f", &ff);
			if (stcoden == 1){//开关站
				dev->Load_Conn_KGZ[6].value = ff;
			}else if (stcoden == 2){//二空压
				dev->Load_Conn_EKY[6].value = ff;
			}else if (stcoden == 3){//三催化
				dev->Load_Conn_CH3[6].value = ff;
			}else if (stcoden == 4){//三催化
				dev->Load_Conn_CH4[6].value = ff;
			}
			continue;
		}
		if(!strcmp(ss, "执行站N负荷8归属:")){
			fscanf(fset, "%f", &ff);
			if (stcoden == 1){//开关站
				dev->Load_Conn_KGZ[7].value = ff;
			}else if (stcoden == 2){//二空压
				dev->Load_Conn_EKY[7].value = ff;
			}else if (stcoden == 3){//三催化
				dev->Load_Conn_CH3[7].value = ff;
			}else if (stcoden == 4){//三催化
				dev->Load_Conn_CH4[7].value = ff;
			}
			continue;
		}


	}

	fclose(fset);

	if (!OutputDevInfo(string("./tmp/tmp.log"), dev, fault)){
		exit(0);
	}
	res = true;
	return res;
}

//输出策略结果
bool SendTacFile(const string& oufile, DEVINFO* dev){
	bool res = false;
	ofstream fout;
	static int lll = 0;
	if (lll == 0){
		fout.open(oufile.c_str(), ios::out);
	}else{
		fout.open(oufile.c_str(), ios::out|ios::app);
	}
	lll++;

	if (!fout.is_open()){
		return res;
	}
	res = true;
	//输出策略动作结果
	for (int i = 0;i < TACOUT_NUM;i++){
		fout << endl;
		fout << "=====================================================================" << endl;
		fout << "tac_no:      " << dev->tac[i].tac_num << endl;
		fout << "tac_yq:      " << dev->tac[i].tac_yq << endl;
		fout << "tac_kq:      " << dev->tac[i].tac_kq << endl;
		fout << "tac_sq:      " << dev->tac[i].tac_sq << endl;
		fout << "== Loadinfo ==" << endl;
		for (int j = 0;j < dev->tac[i].data_num;j++){
			fout << "负荷编号- " << i+1 << " ---  " << (dev->tac[i].data[j].cutted ? "YES" : "NO") << endl;
		}
		fout << "=====================================================================" << endl;
	}

	fout.close();
	return res;
}

