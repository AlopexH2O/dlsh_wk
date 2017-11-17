#include <fstream>
#include <iostream>
#include "TestCase.h"
using namespace std;

bool OutputDevInfo(string& outfile, DEVINFO* dev){
	bool res = false;
	ofstream fout;
	fout.open(outfile, ios::out);

	if (!fout.is_open()){
		cout << "Error: Failed to write in " << outfile << endl;
		return res;
	}
	res = true;
	fout << endl;
	fout << "===============================ϵͳ����====================================="<< endl
		 << "1#��߹��ʣ�" << dev->Sys_P[0].value << endl
		 << "1#���й��ʣ�" << dev->Sys_P[1].value << endl
		 << "2#��߹��ʣ�" << dev->Sys_P[2].value << endl
		 << "2#���й��ʣ�" << dev->Sys_P[3].value << endl
		 << "ĸ��9572���ʣ�" << dev->Sys_P[4].value << endl
		 << "����һ�߹��ʣ�" << dev->Sys_P[5].value << endl
		 << "�������߹��ʣ�" << dev->Sys_P[6].value << endl
		 << "���ܶ����ʣ�" << dev->Sys_P[7].value << endl
		 << "����һ���ʣ�" << dev->Sys_P[8].value << endl;
	fout << "=============================������·����====================================="<< endl
		<< "����վϵͳ1��·��" << dev->Load_Conn[0].value << endl
		<< "����վϵͳ2��·��" << dev->Load_Conn[1].value << endl
		<< "����ѹϵͳ1��·��" << dev->Load_Conn[2].value << endl
		<< "����ѹϵͳ2��·��" << dev->Load_Conn[3].value << endl
		<< "���߻�ϵͳ1��·1��" << dev->Load_Conn[4].value << endl
		<< "���߻�ϵͳ1��·2��" << dev->Load_Conn[5].value << endl
		<< "���߻�ϵͳ2��·1��" << dev->Load_Conn[6].value << endl
		<< "���߻�ϵͳ2��·2��" << dev->Load_Conn[7].value << endl
		<< "�Ĵ߻�ϵͳ1��·1��" << dev->Load_Conn[8].value << endl
		<< "�Ĵ߻�ϵͳ1��·2��" << dev->Load_Conn[9].value << endl
		<< "�Ĵ߻�ϵͳ2��·1��" << dev->Load_Conn[10].value << endl
		<< "�Ĵ߻�ϵͳ2��·2��" << dev->Load_Conn[11].value << endl;
	fout << "=============================����λ����Ϣ====================================="<< endl
		<< "ϵͳ1������" << dev->Sys_Stat[0].value << endl
		<< "ϵͳ2������" << dev->Sys_Stat[1].value << endl
		<< "ϵͳ12������" << dev->Sys_Stat[2].value << endl
		<< "9511���أ�" << dev->Sys_Stat[3].value << endl
		<< "9512���أ�" << dev->Sys_Stat[4].value << endl
		<< "9561���أ�" << dev->Sys_Stat[5].value << endl
		<< "9562���أ�" << dev->Sys_Stat[6].value << endl
		<< "9591���أ�" << dev->Sys_Stat[7].value << endl
		<< "9592���أ�" << dev->Sys_Stat[8].value << endl
		<< "9571���أ�" << dev->Sys_Stat[9].value << endl
		<< "9572���أ�" << dev->Sys_Stat[10].value << endl;
	fout << "=============================������Ϣ====================================="<< endl
		<< "��������\t" << "����P\t" << "���ȼ�" << endl
		<< "8012����һ�߹��ʣ�    " << dev->Load_P[0 ].value << "\t" << dev->Load_Prior[0 ].value << endl
		<< "8013�����ѻ����ʣ�    " << dev->Load_P[1 ].value << "\t" << dev->Load_Prior[1 ].value << endl
		<< "8014ú����⹦�ʣ�    " << dev->Load_P[2 ].value << "\t" << dev->Load_Prior[2 ].value << endl
		<< "8015���ͼ��⹦�ʣ�    " << dev->Load_P[3 ].value << "\t" << dev->Load_Prior[3 ].value << endl
		<< "������·05���ʣ�      " << dev->Load_P[4 ].value << "\t" << dev->Load_Prior[4 ].value << endl
		<< "������·06���ʣ�      " << dev->Load_P[5 ].value << "\t" << dev->Load_Prior[5 ].value << endl
		<< "8022�������߹��ʣ�    " << dev->Load_P[6 ].value << "\t" << dev->Load_Prior[6 ].value << endl
		<< "8023�����ѻ����߹��ʣ�" << dev->Load_P[7 ].value << "\t" << dev->Load_Prior[7 ].value << endl
		<< "8024ú�������߹��ʣ�" << dev->Load_P[8 ].value << "\t" << dev->Load_Prior[8 ].value << endl
		<< "8025���ͼ�����߹��ʣ�" << dev->Load_P[9 ].value << "\t" << dev->Load_Prior[9 ].value << endl
		<< "������·11���ʣ�      " << dev->Load_P[10].value << "\t" << dev->Load_Prior[10].value << endl
		<< "������·12���ʣ�      " << dev->Load_P[11].value << "\t" << dev->Load_Prior[11].value << endl
		<< "3101�³�����߹��ʣ�  " << dev->Load_P[12].value << "\t" << dev->Load_Prior[12].value << endl
		<< "3103��ѭ���߹��ʣ�    " << dev->Load_P[13].value << "\t" << dev->Load_Prior[13].value << endl
		<< "3105�������߹��ʣ�    " << dev->Load_P[14].value << "\t" << dev->Load_Prior[14].value << endl
		<< "������·04���ʣ�      " << dev->Load_P[15].value << "\t" << dev->Load_Prior[15].value << endl
		<< "3102�³������߹��ʣ�  " << dev->Load_P[16].value << "\t" << dev->Load_Prior[16].value << endl
		<< "3104��ѭ���߹��ʣ�    " << dev->Load_P[17].value << "\t" << dev->Load_Prior[17].value << endl
		<< "3105�������߹��ʣ�    " << dev->Load_P[18].value << "\t" << dev->Load_Prior[18].value << endl
		<< "3151���ʣ�            " << dev->Load_P[19].value << "\t" << dev->Load_Prior[19].value << endl
		<< "3152���ʣ�            " << dev->Load_P[20].value << "\t" << dev->Load_Prior[20].value << endl
		<< "3557�������߹��ʣ�    " << dev->Load_P[21].value << "\t" << dev->Load_Prior[21].value << endl
		<< "3558�������߹��ʣ�    " << dev->Load_P[22].value << "\t" << dev->Load_Prior[22].value << endl
		<< "3605���ͼ�����߹��ʣ�" << dev->Load_P[23].value << "\t" << dev->Load_Prior[23].value << endl
		<< "3607�����ͼ��߹��ʣ�  " << dev->Load_P[24].value << "\t" << dev->Load_Prior[24].value << endl
		<< "3609���߻�5#�书�ʣ�  " << dev->Load_P[25].value << "\t" << dev->Load_Prior[25].value << endl
		<< "3551��6kV1ĸ�����ʣ�  " << dev->Load_P[26].value << "\t" << dev->Load_Prior[26].value << endl
		<< "3552��6kV2ĸ�����ʣ�  " << dev->Load_P[27].value << "\t" << dev->Load_Prior[27].value << endl
		<< "3651��6kV3ĸ�����ʣ�  " << dev->Load_P[28].value << "\t" << dev->Load_Prior[28].value << endl
		<< "3569�����书�ʣ�      " << dev->Load_P[29].value << "\t" << dev->Load_Prior[29].value << endl
		<< "3606���ͼ������߹��ʣ�" << dev->Load_P[30].value << "\t" << dev->Load_Prior[30].value << endl
		<< "3608�������ҹ��ʣ�    " << dev->Load_P[31].value << "\t" << dev->Load_Prior[31].value << endl
		<< "3611����׹��ʣ�      " << dev->Load_P[32].value << "\t" << dev->Load_Prior[32].value << endl
		<< "3615��ѹ���׹��ʣ�    " << dev->Load_P[33].value << "\t" << dev->Load_Prior[33].value << endl
		<< "3617�����׹��ʣ�      " << dev->Load_P[34].value << "\t" << dev->Load_Prior[34].value << endl
		<< "3612�����ҹ��ʣ�      " << dev->Load_P[35].value << "\t" << dev->Load_Prior[35].value << endl
		<< "3616��ѹ���ҹ��ʣ�    " << dev->Load_P[36].value << "\t" << dev->Load_Prior[36].value << endl
		<< "3618�����ҹ��ʣ�      " << dev->Load_P[37].value << "\t" << dev->Load_Prior[37].value << endl
		<< "3653��6kV5ĸ�����ʣ�  " << dev->Load_P[38].value << "\t" << dev->Load_Prior[38].value << endl
		<< "3654��6kV6ĸ�����ʣ�  " << dev->Load_P[39].value << "\t" << dev->Load_Prior[39].value << endl
		<< "3652��6kV4ĸ�����ʣ�  " << dev->Load_P[40].value << "\t" << dev->Load_Prior[40].value << endl
		<< "3903��ˮ���߹��ʣ�    " << dev->Load_P[41].value << "\t" << dev->Load_Prior[41].value << endl
		<< "3905�ܿؼ��߹��ʣ�    " << dev->Load_P[42].value << "\t" << dev->Load_Prior[42].value << endl
		<< "������·03���ʣ�      " << dev->Load_P[43].value << "\t" << dev->Load_Prior[43].value << endl
		<< "3904��ˮ���߹��ʣ�    " << dev->Load_P[44].value << "\t" << dev->Load_Prior[44].value << endl
		<< "3906�ܿ����߹��ʣ�    " << dev->Load_P[45].value << "\t" << dev->Load_Prior[45].value << endl
		<< "���ù���1��           " << dev->Load_P[46].value << "\t" << dev->Load_Prior[46].value << endl
		<< "3953���ʣ�            " << dev->Load_P[47].value << "\t" << dev->Load_Prior[47].value << endl
		<< "3954���ʣ�            " << dev->Load_P[48].value << "\t" << dev->Load_Prior[48].value << endl
		<< "3931���ʣ�            " << dev->Load_P[49].value << "\t" << dev->Load_Prior[49].value << endl
		<< "3941���ʣ�            " << dev->Load_P[50].value << "\t" << dev->Load_Prior[50].value << endl
		<< "4801�м�޼��߹��ʣ�  " << dev->Load_P[51].value << "\t" << dev->Load_Prior[51].value << endl
		<< "���ù���2��           " << dev->Load_P[52].value << "\t" << dev->Load_Prior[52].value << endl
		<< "���ù���3��           " << dev->Load_P[53].value << "\t" << dev->Load_Prior[53].value << endl
		<< "���ù���4��           " << dev->Load_P[54].value << "\t" << dev->Load_Prior[54].value << endl
		<< "���ù���5��           " << dev->Load_P[55].value << "\t" << dev->Load_Prior[55].value << endl
		<< "4802�м�����߹��ʣ�  " << dev->Load_P[56].value << "\t" << dev->Load_Prior[56].value << endl
		<< "���ù���6��           " << dev->Load_P[57].value << "\t" << dev->Load_Prior[57].value << endl
		<< "���ù���7��           " << dev->Load_P[58].value << "\t" << dev->Load_Prior[58].value << endl
		<< "���ù���8��           " << dev->Load_P[59].value << "\t" << dev->Load_Prior[59].value << endl
		<< "���ù���9��           " << dev->Load_P[60].value << "\t" << dev->Load_Prior[60].value << endl
		<< "4851����10��          " << dev->Load_P[61].value << "\t" << dev->Load_Prior[61].value << endl
		<< "4852����11��          " << dev->Load_P[62].value << "\t" << dev->Load_Prior[62].value << endl;

	fout << "===============================��ֵ======================================"<< endl
		<< "Ƶ��Ƿ�й��ʶ�ֵ��" << dev->Load_Prior[63].value << endl;


	fout.close();

	return res;
}

//����װ���ļ�
bool ReadTestCaseFile(string& inf_stat, string& inf_set, DEVINFO* dev){
	bool res = false;
	ifstream fstat;
	ifstream fset;
	fstat.open(inf_stat, ios::in);
	fset.open(inf_set, ios::in);
	if (!fstat.is_open() || !fset.is_open()){
		cout << "Error: Failed in Opening file!" << endl;
		return res;
	}
	string s;
	string value;
	while (fstat >> s){
		if(s == "1#��߹��ʣ�"){
			fstat >> value;
			dev->Sys_P[0].value = atof(value.c_str());
			continue;
		}
		if(s == "1#���й��ʣ�"){
			fstat >> value;
			dev->Sys_P[1].value = atof(value.c_str());
			continue;
		}
		if(s == "2#��߹��ʣ�"){
			fstat >> value;
			dev->Sys_P[2].value = atof(value.c_str());
			continue;
		}
		if(s == "2#���й��ʣ�"){
			fstat >> value;
			dev->Sys_P[3].value = atof(value.c_str());
			continue;
		}
		if(s == "66kVĸ��9572���ʣ�"){
			fstat >> value;
			dev->Sys_P[4].value = atof(value.c_str());
			continue;
		}
		if(s == "����һ�߹��ʣ�"){
			fstat >> value;
			dev->Sys_P[5].value = atof(value.c_str());
			continue;
		}
		if(s == "�������߹��ʣ�"){
			fstat >> value;
			dev->Sys_P[6].value = atof(value.c_str());
			continue;
		}
		if(s == "���ܶ����ʣ�"){
			fstat >> value;
			dev->Sys_P[7].value = atof(value.c_str());
			continue;
		}
		if(s == "����վϵͳ1��·��"){
			fstat >> value;
			dev->Sys_Stat[0].value = atof(value.c_str());
			continue;
		}
		if(s == "����վϵͳ2��·��"){
			fstat >> value;
			dev->Sys_Stat[1].value = atof(value.c_str());
			continue;
		}
		if(s == "����ѹϵͳ1��·��"){
			fstat >> value;
			dev->Sys_Stat[2].value = atof(value.c_str());
			continue;
		}
		if(s == "����ѹϵͳ2��·��"){
			fstat >> value;
			dev->Sys_Stat[3].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻�ϵͳ1��·1��"){
			fstat >> value;
			dev->Sys_Stat[4].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻�ϵͳ1��·2��"){
			fstat >> value;
			dev->Sys_Stat[5].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻�ϵͳ2��·1��"){
			fstat >> value;
			dev->Sys_Stat[6].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻�ϵͳ2��·2��"){
			fstat >> value;
			dev->Sys_Stat[7].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻�ϵͳ1��·1��"){
			fstat >> value;
			dev->Sys_Stat[8].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻�ϵͳ1��·2��"){
			fstat >> value;
			dev->Sys_Stat[9].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻�ϵͳ2��·1��"){
			fstat >> value;
			dev->Sys_Stat[10].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻�ϵͳ2��·2��"){
			fstat >> value;
			dev->Sys_Stat[11].value = atof(value.c_str());
			continue;
		}
		//��·����
		int byxl = 0;
		if(s == "8012����һ�߹��ʣ�"){
			fstat >> value;
			dev->Load_P[0].value = atof(value.c_str());
			continue;
		}
		if(s == "8013�����ѻ����ʣ�"){
			fstat >> value;
			dev->Load_P[1].value = atof(value.c_str());
			continue;
		}
		if(s == "8014ú����⹦�ʣ�"){
			fstat >> value;
			dev->Load_P[2].value = atof(value.c_str());
			continue;
		}
		if(s == "8015���ͼ��⹦�ʣ�"){
			fstat >> value;
			dev->Load_P[3].value = atof(value.c_str());
			continue;
		}
		if(s == "������·05���ʣ�"){
			fstat >> value;
			dev->Load_P[4].value = atof(value.c_str());
			continue;
		}
		if(s == "������·06���ʣ�"){
			fstat >> value;
			dev->Load_P[5].value = atof(value.c_str());
			continue;
		}
		if(s == "8022�������߹��ʣ�"){
			fstat >> value;
			dev->Load_P[6].value = atof(value.c_str());
			continue;
		}
		if(s == "8023�����ѻ����߹��ʣ�"){
			fstat >> value;
			dev->Load_P[7].value = atof(value.c_str());
			continue;
		}
		if(s == "8024ú�������߹��ʣ�"){
			fstat >> value;
			dev->Load_P[8].value = atof(value.c_str());
			continue;
		}
		if(s == "8025���ͼ�����߹��ʣ�"){
			fstat >> value;
			dev->Load_P[9].value = atof(value.c_str());
			continue;
		}
		if(s == "������·11���ʣ�"){
			fstat >> value;
			dev->Load_P[10].value = atof(value.c_str());
			continue;
		}
		if(s == "������·12���ʣ�"){
			fstat >> value;
			dev->Load_P[11].value = atof(value.c_str());
			continue;
		}
		if(s == "3101�³�����߹��ʣ�"){
			fstat >> value;
			dev->Load_P[12].value = atof(value.c_str());
			continue;
		}
		if(s == "3103��ѭ���߹��ʣ�"){
			fstat >> value;
			dev->Load_P[13].value = atof(value.c_str());
			continue;
		}
		if(s == "3105�������߹��ʣ�"){
			fstat >> value;
			dev->Load_P[14].value = atof(value.c_str());
			continue;
		}
		if(s == "������·04���ʣ�"){
			fstat >> value;
			dev->Load_P[15].value = atof(value.c_str());
			continue;
		}
		if(s == "3102�³������߹��ʣ�"){
			fstat >> value;
			dev->Load_P[16].value = atof(value.c_str());
			continue;
		}
		if(s == "3104��ѭ���߹��ʣ�"){
			fstat >> value;
			dev->Load_P[17].value = atof(value.c_str());
			continue;
		}
		if(s == "3105�������߹��ʣ�"){
			fstat >> value;
			dev->Load_P[18].value = atof(value.c_str());
			continue;
		}
		if(s == "3151���ʣ�"){
			fstat >> value;
			dev->Load_P[19].value = atof(value.c_str());
			continue;
		}
		if(s == "3152���ʣ�"){
			fstat >> value;
			dev->Load_P[20].value = atof(value.c_str());
			continue;
		}
		if(s == "3557�������߹��ʣ�"){
			fstat >> value;
			dev->Load_P[21].value = atof(value.c_str());
			continue;
		}
		if(s == "3558�������߹��ʣ�"){
			fstat >> value;
			dev->Load_P[22].value = atof(value.c_str());
			continue;
		}
		if(s == "3605���ͼ�����߹��ʣ�"){
			fstat >> value;
			dev->Load_P[23].value = atof(value.c_str());
			continue;
		}
		if(s == "3607�����ͼ��߹��ʣ�"){
			fstat >> value;
			dev->Load_P[24].value = atof(value.c_str());
			continue;
		}
		if(s == "3609���߻�5#�书�ʣ�"){
			fstat >> value;
			dev->Load_P[25].value = atof(value.c_str());
			continue;
		}
		if(s == "3551��6kV1ĸ�����ʣ�"){
			fstat >> value;
			dev->Load_P[26].value = atof(value.c_str());
			continue;
		}
		if(s == "3552��6kV2ĸ�����ʣ�"){
			fstat >> value;
			dev->Load_P[27].value = atof(value.c_str());
			continue;
		}
		if(s == "3651��6kV3ĸ�����ʣ�"){
			fstat >> value;
			dev->Load_P[28].value = atof(value.c_str());
			continue;
		}
		if(s == "3569�����书�ʣ�"){
			fstat >> value;
			dev->Load_P[29].value = atof(value.c_str());
			continue;
		}
		if(s == "3606���ͼ������߹��ʣ�"){
			fstat >> value;
			dev->Load_P[30].value = atof(value.c_str());
			continue;
		}
		if(s == "3608�������ҹ��ʣ�"){
			fstat >> value;
			dev->Load_P[31].value = atof(value.c_str());
			continue;
		}
		if(s == "3611����׹��ʣ�"){
			fstat >> value;
			dev->Load_P[32].value = atof(value.c_str());
			continue;
		}
		if(s == "3615��ѹ���׹��ʣ�"){
			fstat >> value;
			dev->Load_P[33].value = atof(value.c_str());
			continue;
		}
		if(s == "3617�����׹��ʣ�"){
			fstat >> value;
			dev->Load_P[34].value = atof(value.c_str());
			continue;
		}
		if(s == "3612�����ҹ��ʣ�"){
			fstat >> value;
			dev->Load_P[35].value = atof(value.c_str());
			continue;
		}
		if(s == "3616��ѹ���ҹ��ʣ�"){
			fstat >> value;
			dev->Load_P[36].value = atof(value.c_str());
			continue;
		}
		if(s == "3618�����ҹ��ʣ�"){
			fstat >> value;
			dev->Load_P[37].value = atof(value.c_str());
			continue;
		}
		if(s == "3653��6kV5ĸ�����ʣ�"){
			fstat >> value;
			dev->Load_P[38].value = atof(value.c_str());
			continue;
		}
		if(s == "3654��6kV6ĸ�����ʣ�"){
			fstat >> value;
			dev->Load_P[39].value = atof(value.c_str());
			continue;
		}
		if(s == "3652��6kV4ĸ�����ʣ�"){
			fstat >> value;
			dev->Load_P[40].value = atof(value.c_str());
			continue;
		}
		if(s == "3903��ˮ���߹��ʣ�"){
			fstat >> value;
			dev->Load_P[41].value = atof(value.c_str());
			continue;
		}
		if(s == "3905�ܿؼ��߹��ʣ�"){
			fstat >> value;
			dev->Load_P[42].value = atof(value.c_str());
			continue;
		}
		if(s == "������·03���ʣ�"){
			fstat >> value;
			dev->Load_P[43].value = atof(value.c_str());
			continue;
		}
		if(s == "3904��ˮ���߹��ʣ�"){
			fstat >> value;
			dev->Load_P[44].value = atof(value.c_str());
			continue;
		}
		if(s == "3906�ܿ����߹��ʣ�"){
			fstat >> value;
			dev->Load_P[45].value = atof(value.c_str());
			continue;
		}
		if(s == "���ù���1��"){
			fstat >> value;
			dev->Load_P[46].value = atof(value.c_str());
			continue;
		}
		if(s == "3953���ʣ�"){
			fstat >> value;
			dev->Load_P[47].value = atof(value.c_str());
			continue;
		}
		if(s == "3954���ʣ�"){
			fstat >> value;
			dev->Load_P[48].value = atof(value.c_str());
			continue;
		}
		if(s == "3931���ʣ�"){
			fstat >> value;
			dev->Load_P[49].value = atof(value.c_str());
			continue;
		}
		if(s == "3941���ʣ�"){
			fstat >> value;
			dev->Load_P[50].value = atof(value.c_str());
			continue;
		}
		if(s == "4801�м�޼��߹��ʣ�"){
			fstat >> value;
			dev->Load_P[51].value = atof(value.c_str());
			continue;
		}
		if(s == "���ù���2��"){
			fstat >> value;
			dev->Load_P[52].value = atof(value.c_str());
			continue;
		}
		if(s == "���ù���3��"){
			fstat >> value;
			dev->Load_P[53].value = atof(value.c_str());
			continue;
		}
		if(s == "���ù���4��"){
			fstat >> value;
			dev->Load_P[54].value = atof(value.c_str());
			continue;
		}
		if(s == "���ù���5��"){
			fstat >> value;
			dev->Load_P[55].value = atof(value.c_str());
			continue;
		}
		if(s == "4802�м�����߹��ʣ�"){
			fstat >> value;
			dev->Load_P[56].value = atof(value.c_str());
			continue;
		}
		if(s == "���ù���6��"){
			fstat >> value;
			dev->Load_P[57].value = atof(value.c_str());
			continue;
		}
		if(s == "���ù���7��"){
			fstat >> value;
			dev->Load_P[58].value = atof(value.c_str());
			continue;
		}
		if(s == "���ù���8��"){
			fstat >> value;
			dev->Load_P[59].value = atof(value.c_str());
			continue;
		}
		if(s == "���ù���9��"){
			fstat >> value;
			dev->Load_P[60].value = atof(value.c_str());
			continue;
		}
		if(s == "4851����10��"){
			fstat >> value;
			dev->Load_P[61].value = atof(value.c_str());
			continue;
		}
		if(s == "4852����11��"){
			fstat >> value;
			dev->Load_P[62].value = atof(value.c_str());
			continue;
		}

		//ϵͳ������״̬
		if(s == "ϵͳ1������"){
			fstat >> value;
			dev->Sys_Stat[0].value = atof(value.c_str());
			continue;
		}
		if(s == "ϵͳ2������"){
			fstat >> value;
			dev->Sys_Stat[1].value = atof(value.c_str());
			continue;
		}
		if(s == "ϵͳ12����������"){
			fstat >> value;
			dev->Sys_Stat[2].value = atof(value.c_str());
			continue;
		}
		if(s == "9511�������У�"){
			fstat >> value;
			dev->Sys_Stat[3].value = atof(value.c_str());
			continue;
		}
		if(s == "9512�������У�"){
			fstat >> value;
			dev->Sys_Stat[4].value = atof(value.c_str());
			continue;
		}
		if(s == "9561�������У�"){
			fstat >> value;
			dev->Sys_Stat[5].value = atof(value.c_str());
			continue;
		}
		if(s == "9562�������У�"){
			fstat >> value;
			dev->Sys_Stat[6].value = atof(value.c_str());
			continue;
		}
		if(s == "9591�������У�"){
			fstat >> value;
			dev->Sys_Stat[7].value = atof(value.c_str());
			continue;
		}
		if(s == "9592�������У�"){
			fstat >> value;
			dev->Sys_Stat[8].value = atof(value.c_str());
			continue;
		}
		if(s == "9572�������У�"){
			fstat >> value;
			dev->Sys_Stat[10].value = atof(value.c_str());
			continue;
		}

	}//end while fot stat
	fstat.close();

	while (fset >> s){
		if(s == "����վ��·01���ȼ�:"){
			fset >> value;
			dev->Load_Prior[0].value = atof(value.c_str());
			continue;
		}
		if(s == "����վ��·02���ȼ�:"){
			fset >> value;
			dev->Load_Prior[1].value = atof(value.c_str());
			continue;
		}		
		if(s == "����վ��·03���ȼ�:"){
			fset >> value;
			dev->Load_Prior[2].value = atof(value.c_str());
			continue;
		}		
		if(s == "����վ��·04���ȼ�:"){
			fset >> value;
			dev->Load_Prior[3].value = atof(value.c_str());
			continue;
		}	
		if(s == "����վ��·05���ȼ�:"){
			fset >> value;
			dev->Load_Prior[4].value = atof(value.c_str());
			continue;
		}	
		if(s == "����վ��·06���ȼ�:"){
			fset >> value;
			dev->Load_Prior[5].value = atof(value.c_str());
			continue;
		}	
		if(s == "����վ��·07���ȼ�:"){
			fset >> value;
			dev->Load_Prior[6].value = atof(value.c_str());
			continue;
		}	
		if(s == "����վ��·08���ȼ�:"){
			fset >> value;
			dev->Load_Prior[7].value = atof(value.c_str());
			continue;
		}	
		if(s == "����վ��·09���ȼ�:"){
			fset >> value;
			dev->Load_Prior[8].value = atof(value.c_str());
			continue;
		}
		if(s == "����վ��·10���ȼ�:"){
			fset >> value;
			dev->Load_Prior[9].value = atof(value.c_str());
			continue;
		}
		if(s == "����վ��·11���ȼ�:"){
			fset >> value;
			dev->Load_Prior[10].value = atof(value.c_str());
			continue;
		}
		if(s == "����վ��·12���ȼ�:"){
			fset >> value;
			dev->Load_Prior[11].value = atof(value.c_str());
			continue;
		}
		if(s == "����ѹ��·01���ȼ�:"){
			fset >> value;
			dev->Load_Prior[12].value = atof(value.c_str());
			continue;
		}
		if(s == "����ѹ��·02���ȼ�:"){
			fset >> value;
			dev->Load_Prior[13].value = atof(value.c_str());
			continue;
		}
		if(s == "����ѹ��·03���ȼ�:"){
			fset >> value;
			dev->Load_Prior[14].value = atof(value.c_str());
			continue;
		}
		if(s == "����ѹ��·04���ȼ�:"){
			fset >> value;
			dev->Load_Prior[15].value = atof(value.c_str());
			continue;
		}
		if(s == "����ѹ��·05���ȼ�:"){
			fset >> value;
			dev->Load_Prior[16].value = atof(value.c_str());
			continue;
		}
		if(s == "����ѹ��·06���ȼ�:"){
			fset >> value;
			dev->Load_Prior[17].value = atof(value.c_str());
			continue;
		}
		if(s == "����ѹ��·07���ȼ�:"){
			fset >> value;
			dev->Load_Prior[18].value = atof(value.c_str());
			continue;
		}
		if(s == "����ѹ��·08���ȼ�:"){
			fset >> value;
			dev->Load_Prior[19].value = atof(value.c_str());
			continue;
		}
		if(s == "����ѹ��·09���ȼ�:"){
			fset >> value;
			dev->Load_Prior[20].value = atof(value.c_str());
			continue;
		}
		//���߻���·
		if(s == "���߻���·01���ȼ�:"){
			fset >> value;
			dev->Load_Prior[21].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·02���ȼ�:"){
			fset >> value;
			dev->Load_Prior[22].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·03���ȼ�:"){
			fset >> value;
			dev->Load_Prior[23].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·04���ȼ�:"){
			fset >> value;
			dev->Load_Prior[24].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·05���ȼ�:"){
			fset >> value;
			dev->Load_Prior[25].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·06���ȼ�:"){
			fset >> value;
			dev->Load_Prior[26].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·07���ȼ�:"){
			fset >> value;
			dev->Load_Prior[27].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·08���ȼ�:"){
			fset >> value;
			dev->Load_Prior[28].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·09���ȼ�:"){
			fset >> value;
			dev->Load_Prior[29].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·10���ȼ�:"){
			fset >> value;
			dev->Load_Prior[30].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·11���ȼ�:"){
			fset >> value;
			dev->Load_Prior[31].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·12���ȼ�:"){
			fset >> value;
			dev->Load_Prior[32].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·13���ȼ�:"){
			fset >> value;
			dev->Load_Prior[33].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·14���ȼ�:"){
			fset >> value;
			dev->Load_Prior[34].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·15���ȼ�:"){
			fset >> value;
			dev->Load_Prior[35].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·16���ȼ�:"){
			fset >> value;
			dev->Load_Prior[36].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·17���ȼ�:"){
			fset >> value;
			dev->Load_Prior[37].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·18���ȼ�:"){
			fset >> value;
			dev->Load_Prior[38].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·19���ȼ�:"){
			fset >> value;
			dev->Load_Prior[39].value = atof(value.c_str());
			continue;
		}
		if(s == "���߻���·20���ȼ�:"){
			fset >> value;
			dev->Load_Prior[40].value = atof(value.c_str());
			continue;
		}
		//�Ĵ߻�
		if(s == "�Ĵ߻���������·01���ȼ�:"){
			fset >> value;
			dev->Load_Prior[41].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·02���ȼ�:"){
			fset >> value;
			dev->Load_Prior[43].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·03���ȼ�:"){
			fset >> value;
			dev->Load_Prior[43].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·04���ȼ�:"){
			fset >> value;
			dev->Load_Prior[44].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·05���ȼ�:"){
			fset >> value;
			dev->Load_Prior[45].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·06���ȼ�:"){
			fset >> value;
			dev->Load_Prior[46].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·07���ȼ�:"){
			fset >> value;
			dev->Load_Prior[47].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·08���ȼ�:"){
			fset >> value;
			dev->Load_Prior[48].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·09���ȼ�:"){
			fset >> value;
			dev->Load_Prior[49].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·10���ȼ�:"){
			fset >> value;
			dev->Load_Prior[50].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·11���ȼ�:"){
			fset >> value;
			dev->Load_Prior[51].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·12���ȼ�:"){
			fset >> value;
			dev->Load_Prior[52].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·13���ȼ�:"){
			fset >> value;
			dev->Load_Prior[53].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·14���ȼ�:"){
			fset >> value;
			dev->Load_Prior[54].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·15���ȼ�:"){
			fset >> value;
			dev->Load_Prior[55].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·16���ȼ�:"){
			fset >> value;
			dev->Load_Prior[56].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·17���ȼ�:"){
			fset >> value;
			dev->Load_Prior[57].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·18���ȼ�:"){
			fset >> value;
			dev->Load_Prior[58].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·19���ȼ�:"){
			fset >> value;
			dev->Load_Prior[59].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·20���ȼ�:"){
			fset >> value;
			dev->Load_Prior[60].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·21���ȼ�:"){
			fset >> value;
			dev->Load_Prior[61].value = atof(value.c_str());
			continue;
		}
		if(s == "�Ĵ߻���������·22���ȼ�:"){
			fset >> value;
			dev->Load_Prior[62].value = atof(value.c_str());
			continue;
		}
		if(s == "Ƶ��Ƿ�й��ʶ�ֵ:"){
			fset >> value;
			dev->Load_Prior[63].value = atof(value.c_str());
			continue;
		}

	}

	fset.close();

	if (!OutputDevInfo(string("tmp.log"), dev)){
		exit(0);
	}
	return false;
}

//������Խ��
bool SendTacFile(string& oufile, DEVINFO* dev){
	bool res = false;
	ofstream fout;
	fout.open(oufile, ios::out|ios::app);
	
	if (!fout.is_open()){
		return res;
	}
	res = true;
	//������Զ������
	fout << endl;
	fout << "=====================================================================" << endl;
	fout << "tac_no:      " << dev->tac.tac_num << endl;
	fout << "tac_yq:      " << dev->tac.tac_yq << endl;
	fout << "tac_kq:      " << dev->tac.tac_kq << endl;
	fout << "tac_pcutted: " << dev->tac.tac_pcutted << endl;
	fout << "tac_ncutted: " << dev->tac.tac_ncutted << endl;
	fout << "== Loadinfo ==" << endl;
	for (int i = 0;i <= dev->tac.data_num;i++){
		fout << "���ɱ��-" << i+1 << " ---  " << dev->tac.data[i].cutted << " --- " << dev->load[i].pload << endl;
	}
	fout << "=====================================================================" << endl;

	fout.close();
	return res;
}

