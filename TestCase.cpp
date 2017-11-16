#include <fstream>
#include "TestCase.h"
using namespace std;

//����װ���ļ�
bool ReadTestCaseFile(string& inf_stat, string& inf_set, DEVINFO* dev){
	bool res = false;




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

