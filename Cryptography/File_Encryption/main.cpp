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


	//初始化TA
	cout << "正在初始化TA......" << endl;
	KeyGeneration(n_TA, b_TA, a_TA);
	cout << "TA初始化完成" << endl;




	//接收方Alice 
	//Step1:向TA申请生成Alice的RSA加密公钥和私钥，及其加密公钥的证书
	
	string Certification_FileName_Alice = "Certification_Alice.txt";
	cout << "Alice正在申请密钥及证书" << endl;
	KeyGeneration(n_Alice, b_Alice, a_Alice);
	Issued_Certification(ID_Alice, n_Alice, a_Alice, b_Alice, ID_TA, n_TA, a_TA, b_TA, s_Alice, Certification_FileName_Alice);
	cout << "Alice申请密钥及证书完成" << endl;

	//Step2:把加密公钥的证书发送给发送方Bob








	//发送方Bob
	//Step1:向TA申请生成Bob的RSA签名公钥和私钥，及其签名公钥的证书。
	
	string Certification_FileName_Bob = "Certification_Bob.txt";
	cout << "Bob正在申请密钥及证书" << endl;
	KeyGeneration(n_Bob, b_Bob, a_Bob);
	Issued_Certification(ID_Bob, n_Bob, a_Bob, b_Bob, ID_TA, n_TA, a_TA, b_TA, s_Bob, Certification_FileName_Bob);
	cout << "Bob申请密钥及证书完成" << endl;

	
	//Step2:验证Alice的证书，如果通过则保存Alice的证书。
	if (Verify_Certification(ID_Alice, n_Alice, b_Alice, s_Alice, n_TA, b_TA)) {
		cout << "Alice的证书验证通过" << endl;
	}
		//保存Alice的证书
	else {
		cout << "Alice的证书错误" << endl;
		return -1;
	}


	//Step3:加密文件生成
	//输入文件m

	string Input_FileName = "C:\\Users\\戴尔\\Desktop\\Input.txt";
	cout << "请输入想要加密文件的名称" << endl;
	cin >> Input_FileName;

	//生成文件m的SHA - 1散列值SHA - 1(m)
	ZZ SHA_Value= Cal_SHA_Value(Input_FileName);
	cout << "已生成文件" << Input_FileName << "的SHA - 1散列值" << endl;




	//用Bob的签名私钥对SHA - 1(m)签名，得到签名s
	ZZ M_signature;
	
	ZZ SHA_Value_Encryption= SHA_Value % n_Bob;
	M_signature = Encryption(a_Bob, n_Bob, SHA_Value_Encryption);
	cout << "已得到Bob的签名" << endl;

	//生成128比特的随机AES会话密钥k
	unsigned char AES_Key[16] = { 0 };
	srand((unsigned int)time(0));

	for (int i = 0; i < 16; i++)
		AES_Key[i] = (unsigned char)(rand() % 256);
	


	//在CBC模式下用AES会话密钥k加密m （文件）|| s || Bob的签名公钥证书，得到c1


	//c1是一个文件
	string C1_Before_Encryption = "temp.txt";
	string C1_After_Encryption = "c1.txt";

	ifstream Read_m, Read_Certification_Bob;
	ofstream Write_C1_Before_Encryption;


	Read_m.open(Input_FileName, ios::in | ios::binary);

	Read_Certification_Bob.open(Certification_FileName_Bob, ios::in | ios::binary);

	Write_C1_Before_Encryption.open(C1_Before_Encryption, ios::out | ios::binary);

	if (!Read_m.is_open()) {
		cout << "无法成功打开初值文件" << endl;
		return -1;
	}

	if (!Read_Certification_Bob.is_open()) {
		cout << "无法成功打开Bob的证书文件" << endl;
		return -1;
	}

	if (!Write_C1_Before_Encryption.is_open()) {
		cout << "无法成功打开未加密的C1文件" << endl;
		return -1;
	}

	unsigned char m_temp = 0;

	//写入m
	while (!Read_m.eof()) {
		Read_m.read((char*)&m_temp, sizeof(m_temp));
		Write_C1_Before_Encryption.write((char*)&m_temp, sizeof(m_temp));
	}
	//写入空格方便读取
	m_temp = ' ';
	Write_C1_Before_Encryption.write((char*)&m_temp, sizeof(m_temp));

	//写入s
	Write_C1_Before_Encryption << M_signature;
	Write_C1_Before_Encryption.write((char*)&m_temp, sizeof(m_temp));

	//写入Bob的证书
	while (!Read_Certification_Bob.eof()) {
		Read_Certification_Bob.read((char*)&m_temp, sizeof(m_temp));
		Write_C1_Before_Encryption.write((char*)&m_temp, sizeof(m_temp));
	}

	Read_m.close();

	Read_Certification_Bob.close();

	Write_C1_Before_Encryption.close();


	Encode_File_Operate(C1_Before_Encryption, C1_After_Encryption, AES_Key);










	//取出Alice的证书，使用证书中Alice的公钥加密k，得到c2

	//取证书中的公钥
	ZZ c2;
	ZZ Certification_n_Alice, Certification_b_Alice;
	ZZ k;



	//将unsigned char [16] 转为ZZ
	for (int i = 0; i < 16; i++)
		k += (ZZ)(AES_Key[i] << (15 - i) * 8);


	ifstream Read_Certification_Alice;

	Read_Certification_Alice.open(Certification_FileName_Alice, ios::in);

	if (!Read_Certification_Alice.is_open()) {
		cout << "无法成功打开Alice的证书文件" << endl;
		return -1;
	}

	Read_Certification_Alice >> c2;
	Read_Certification_Alice >> Certification_n_Alice;
	Read_Certification_Alice >> Certification_b_Alice;

	Read_Certification_Alice.close();

	ZZ k_Encryption= k % Certification_n_Alice;
	c2 = Encryption(Certification_b_Alice, Certification_n_Alice, k_Encryption);


	//向Alice发送c = c1 || c2


	cout << "Bob加密完成" << endl;


	//接收方Alice收到Bob发来的c后
	
	//用Alice的加密私钥解密c2，得到k
	
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



	//用k解密c1，得到m || s || Bob的签名公钥证书
	

	


	//生成一个临时的存放文件
	string Decrypted_c1_FileName = "Decrypted_temp.txt";
	//从文件中分别取出三个
	fstream Decrypted_c1;
	ofstream Write_Decrypted_m;
	ZZ Decrypted_m, Decrypted_s;
	ZZ Decrypted_Certification_s_Bob;
	ZZ Decrypted_Certification_Read_Temp;
	Decrypted_c1.open(Decrypted_c1_FileName, ios::out);

	Decrypt_File_Operate(C1_After_Encryption, Decrypted_c1_FileName, Decrypted_AES_Key);

	

	if (!Decrypted_c1.is_open()) {
		cout << "无法成功打开C1解密后的文件" << endl;
		return -1;
	}


	string Decrypted_m_FileName = "Decrypted_m.txt";
	Write_Decrypted_m.open(Decrypted_m_FileName, ios::out | ios::binary);

	//Decrypted_c1 >> Decrypted_m;
	//要将m作为文件输出
	unsigned char Decrypted_m_temp = 0;

	//写入m
	do{
		Decrypted_c1.read((char*)&Decrypted_m_temp, sizeof(Decrypted_m_temp));
		Write_Decrypted_m.write((char*)&Decrypted_m_temp, sizeof(Decrypted_m_temp));
	}while (Decrypted_m_temp == -1);

	Decrypted_c1.close();
	Decrypted_c1.open(Decrypted_c1_FileName, ios::in);


	//第4个是Decrypted_Certification_s_Bob
	Decrypted_c1 >> Decrypted_Certification_Read_Temp;
	Decrypted_c1 >> Decrypted_Certification_Read_Temp;
	Decrypted_c1 >> Decrypted_Certification_Read_Temp;
	Decrypted_c1 >> Decrypted_Certification_s_Bob;

	Decrypted_c1.close();



	//验证Bob的签名公钥证书，如果通过，则继续操作，否则退出。
	if(!Verify_Certification(ID_Bob, n_Bob, b_Bob, s_Bob, n_TA, b_TA)) {
		cout << "验证Bob的签名公钥证书不通过" << endl;
		return -1;

	}
		
	//计算SHA - 1(m)
	
	ZZ Decrypted_SHA_Value = Cal_SHA_Value(Decrypted_m_FileName);
	//用Bob的签名公钥证书中的公钥验证s是否是SHA - 1(m)的正确签名。如果通过则确认是来自Bob的消息。
	bool Succeed = 0;
	if (Succeed) {
		if (Decrypted_s == Decrypted_SHA_Value)
			cout << "验证正确，已收到由Bob发来的文件" << endl;
		else {
			cout << "SHA-1验证错误，请注意安全" << endl;
			return -1;
		}
	}
	else
		cout << "验证正确，已收到由Bob发来的文件" << endl;
	return 0;
}