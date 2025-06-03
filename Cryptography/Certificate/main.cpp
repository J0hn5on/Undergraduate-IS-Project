#include <iostream>
#include<fstream>
#include<NTL/ZZ.h>
#include"../RSA/RSA.h"
using namespace std;
using namespace NTL;


int main() {

	ZZ ID_Alice, n_Alice, a_Alice, b_Alice;
	ZZ ID_TA, n_TA, a_TA, b_TA;
	ZZ s;

	cout << "������Alice�������Ϣ��ID_Alice��" << endl;
	cin >> ID_Alice;
	cout << "������TA�������Ϣ��ID_TA��" << endl;
	cin >> ID_TA;




	string Certification_FileName;
	cout << "��Ҫ����֤���ļ�������" << endl;
	cin >> Certification_FileName;

	

	cout << "���ڳ�ʼ��TA......" << endl;
	KeyGeneration(n_TA, b_TA, a_TA);
	cout << "TA��ʼ�����" << endl;

	cout << "Alice����������Կ" << endl;
	KeyGeneration(n_Alice, b_Alice, a_Alice);
	cout << "Alice������Կ���" << endl;

	//�䷢
	Issued_Certification(ID_Alice, n_Alice, a_Alice, b_Alice, ID_TA, n_TA, a_TA, b_TA, s, Certification_FileName);
	//��֤
	if (Verify_Certification(ID_Alice, n_Alice, b_Alice, s, n_TA, b_TA))
		cout << "֤����֤ͨ��" << endl;
	else
		cout << "֤����֤ʧ��" << endl;



	return 0;



}