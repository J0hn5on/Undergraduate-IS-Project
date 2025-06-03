#include <iostream>
#include<fstream>
#include <ctime>
#include <cstdlib>
#include<NTL/ZZ.h>
#include"../RSA/RSA.h"
#include"../SHA-1/SHA_1.h"
#include"../AES/AES.h"
#include"File_Encryption.h"
using namespace std;
using namespace NTL;


int main() {

	ZZ ID_Alice, n_Alice, a_Alice, b_Alice;
	ZZ ID_Bob, n_Bob, a_Bob, b_Bob;
	ZZ ID_TA, n_TA, a_TA, b_TA;
	ZZ s_Alice, s_Bob;


	//��ʼ��TA
	cout << "���ڳ�ʼ��TA......" << endl;
	KeyGeneration(n_TA, b_TA, a_TA);
	cout << "TA��ʼ�����" << endl;




	//���շ�Alice 
	//Step1:��TA��������Alice��RSA���ܹ�Կ��˽Կ��������ܹ�Կ��֤��
	
	string Certification_FileName_Alice = "Certification_Alice.txt";
	cout << "Alice����������Կ��֤��" << endl;
	KeyGeneration(n_Alice, b_Alice, a_Alice);
	Issued_Certification(ID_Alice, n_Alice, a_Alice, b_Alice, ID_TA, n_TA, a_TA, b_TA, s_Alice, Certification_FileName_Alice);
	cout << "Alice������Կ��֤�����" << endl;

	//Step2:�Ѽ��ܹ�Կ��֤�鷢�͸����ͷ�Bob








	//���ͷ�Bob
	//Step1:��TA��������Bob��RSAǩ����Կ��˽Կ������ǩ����Կ��֤�顣
	
	string Certification_FileName_Bob = "Certification_Bob.txt";
	cout << "Bob����������Կ��֤��" << endl;
	KeyGeneration(n_Bob, b_Bob, a_Bob);
	Issued_Certification(ID_Bob, n_Bob, a_Bob, b_Bob, ID_TA, n_TA, a_TA, b_TA, s_Bob, Certification_FileName_Bob);
	cout << "Bob������Կ��֤�����" << endl;

	
	//Step2:��֤Alice��֤�飬���ͨ���򱣴�Alice��֤�顣
	if (Verify_Certification(ID_Alice, n_Alice, b_Alice, s_Alice, n_TA, b_TA)) {
		cout << "Alice��֤����֤ͨ��" << endl;
	}
		//����Alice��֤��
	else {
		cout << "Alice��֤�����" << endl;
		return -1;
	}


	//Step3:�����ļ�����
	//�����ļ�m

	string Input_FileName = "C:\\Users\\����\\Desktop\\Input.txt";
	cout << "��������Ҫ�����ļ�������" << endl;
	cin >> Input_FileName;

	//�����ļ�m��SHA - 1ɢ��ֵSHA - 1(m)
	ZZ SHA_Value= Cal_SHA_Value(Input_FileName);
	cout << "�������ļ�" << Input_FileName << "��SHA - 1ɢ��ֵ" << endl;




	//��Bob��ǩ��˽Կ��SHA - 1(m)ǩ�����õ�ǩ��s
	ZZ M_signature;
	
	ZZ SHA_Value_Encryption= SHA_Value % n_Bob;
	M_signature = Encryption(a_Bob, n_Bob, SHA_Value_Encryption);
	cout << "�ѵõ�Bob��ǩ��" << endl;

	//����128���ص����AES�Ự��Կk
	unsigned char AES_Key[16] = { 0 };
	srand((unsigned int)time(0));

	for (int i = 0; i < 16; i++)
		AES_Key[i] = (unsigned char)(rand() % 256);
	


	//��CBCģʽ����AES�Ự��Կk����m ���ļ���|| s || Bob��ǩ����Կ֤�飬�õ�c1


	//c1��һ���ļ�
	string C1_Before_Encryption = "temp.txt";
	string C1_After_Encryption = "c1.txt";

	ifstream Read_m, Read_Certification_Bob;
	ofstream Write_C1_Before_Encryption;


	Read_m.open(Input_FileName, ios::in | ios::binary);

	Read_Certification_Bob.open(Certification_FileName_Bob, ios::in | ios::binary);

	Write_C1_Before_Encryption.open(C1_Before_Encryption, ios::out | ios::binary);

	if (!Read_m.is_open()) {
		cout << "�޷��ɹ��򿪳�ֵ�ļ�" << endl;
		return -1;
	}

	if (!Read_Certification_Bob.is_open()) {
		cout << "�޷��ɹ���Bob��֤���ļ�" << endl;
		return -1;
	}

	if (!Write_C1_Before_Encryption.is_open()) {
		cout << "�޷��ɹ���δ���ܵ�C1�ļ�" << endl;
		return -1;
	}

	unsigned char m_temp = 0;

	//д��m
	while (!Read_m.eof()) {
		Read_m.read((char*)&m_temp, sizeof(m_temp));
		Write_C1_Before_Encryption.write((char*)&m_temp, sizeof(m_temp));
	}
	//д��ո񷽱��ȡ
	m_temp = ' ';
	Write_C1_Before_Encryption.write((char*)&m_temp, sizeof(m_temp));

	//д��s
	Write_C1_Before_Encryption << M_signature;
	Write_C1_Before_Encryption.write((char*)&m_temp, sizeof(m_temp));

	//д��Bob��֤��
	while (!Read_Certification_Bob.eof()) {
		Read_Certification_Bob.read((char*)&m_temp, sizeof(m_temp));
		Write_C1_Before_Encryption.write((char*)&m_temp, sizeof(m_temp));
	}

	Read_m.close();

	Read_Certification_Bob.close();

	Write_C1_Before_Encryption.close();


	Encode_File_Operate(C1_Before_Encryption, C1_After_Encryption, AES_Key);










	//ȡ��Alice��֤�飬ʹ��֤����Alice�Ĺ�Կ����k���õ�c2

	//ȡ֤���еĹ�Կ
	ZZ c2;
	ZZ Certification_n_Alice, Certification_b_Alice;
	ZZ k;



	//��unsigned char [16] תΪZZ
	for (int i = 0; i < 16; i++)
		k += (ZZ)(AES_Key[i] << (15 - i) * 8);


	ifstream Read_Certification_Alice;

	Read_Certification_Alice.open(Certification_FileName_Alice, ios::in);

	if (!Read_Certification_Alice.is_open()) {
		cout << "�޷��ɹ���Alice��֤���ļ�" << endl;
		return -1;
	}

	Read_Certification_Alice >> c2;
	Read_Certification_Alice >> Certification_n_Alice;
	Read_Certification_Alice >> Certification_b_Alice;

	Read_Certification_Alice.close();

	ZZ k_Encryption= k % Certification_n_Alice;
	c2 = Encryption(Certification_b_Alice, Certification_n_Alice, k_Encryption);


	//��Alice����c = c1 || c2


	cout << "Bob�������" << endl;


	//���շ�Alice�յ�Bob������c��
	
	//��Alice�ļ���˽Կ����c2���õ�k
	
	ZZ Decrypted_k;
	Decrypted_k = Decryption(a_Alice, n_Alice, c2);

	string Decrypted_k_String;
	unsigned char Decrypted_AES_Key[16] = { 0 };

	int temp_convert = 0;
	
	for (int i = 0; i < 16; i++) {
		conv(temp_convert, Decrypted_k % (ZZ)256);
		Decrypted_AES_Key[15 - i] = temp_convert;
		Decrypted_k >>= 256L;
	}



	//��k����c1���õ�m || s || Bob��ǩ����Կ֤��
	

	


	//����һ����ʱ�Ĵ���ļ�
	string Decrypted_c1_FileName = "Decrypted_temp.txt";
	//���ļ��зֱ�ȡ������
	fstream Decrypted_c1;
	ofstream Write_Decrypted_m;
	ZZ Decrypted_m, Decrypted_s;
	ZZ Decrypted_Certification_s_Bob;
	ZZ Decrypted_Certification_Read_Temp;
	Decrypted_c1.open(Decrypted_c1_FileName, ios::out);

	Decrypt_File_Operate(C1_After_Encryption, Decrypted_c1_FileName, Decrypted_AES_Key);

	

	if (!Decrypted_c1.is_open()) {
		cout << "�޷��ɹ���C1���ܺ���ļ�" << endl;
		return -1;
	}


	string Decrypted_m_FileName = "Decrypted_m.txt";
	Write_Decrypted_m.open(Decrypted_m_FileName, ios::out | ios::binary);

	//Decrypted_c1 >> Decrypted_m;
	//Ҫ��m��Ϊ�ļ����
	unsigned char Decrypted_m_temp = 0;

	//д��m
	do{
		Decrypted_c1.read((char*)&Decrypted_m_temp, sizeof(Decrypted_m_temp));
		Write_Decrypted_m.write((char*)&Decrypted_m_temp, sizeof(Decrypted_m_temp));
	}while (Decrypted_m_temp == -1);

	Decrypted_c1.close();
	Decrypted_c1.open(Decrypted_c1_FileName, ios::in);


	//��4����Decrypted_Certification_s_Bob
	Decrypted_c1 >> Decrypted_Certification_Read_Temp;
	Decrypted_c1 >> Decrypted_Certification_Read_Temp;
	Decrypted_c1 >> Decrypted_Certification_Read_Temp;
	Decrypted_c1 >> Decrypted_Certification_s_Bob;

	Decrypted_c1.close();



	//��֤Bob��ǩ����Կ֤�飬���ͨ��������������������˳���
	if(!Verify_Certification(ID_Bob, n_Bob, b_Bob, s_Bob, n_TA, b_TA)) {
		cout << "��֤Bob��ǩ����Կ֤�鲻ͨ��" << endl;
		return -1;

	}
		
	//����SHA - 1(m)
	
	ZZ Decrypted_SHA_Value = Cal_SHA_Value(Decrypted_m_FileName);
	//��Bob��ǩ����Կ֤���еĹ�Կ��֤s�Ƿ���SHA - 1(m)����ȷǩ�������ͨ����ȷ��������Bob����Ϣ��
	bool Succeed = 0;
	if (Succeed) {
		if (Decrypted_s == Decrypted_SHA_Value)
			cout << "��֤��ȷ�����յ���Bob�������ļ�" << endl;
		else {
			cout << "SHA-1��֤������ע�ⰲȫ" << endl;
			return -1;
		}
	}
	else
		cout << "��֤��ȷ�����յ���Bob�������ļ�" << endl;
	return 0;
}