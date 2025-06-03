#include<iostream>
#include<cmath>
#include "../AES/AES.h"
#include <fstream>
using namespace std;


int Encode_File_Operate(string Plaintext_Name,string Ciphertext_Name, unsigned char* key_input) {

	ifstream Read_Plaintext;
	ofstream Write_Ciphertext;


	Read_Plaintext.open(Plaintext_Name, ios::in| ios::binary);
	Write_Ciphertext.open(Ciphertext_Name, ios::out| ios::binary);

	if (!Read_Plaintext.is_open()) {
		cout << "无法成功打开明文文件" << endl;
		return -1;
	}

	if (!Write_Ciphertext.is_open()) {
		cout << "无法成功打开密文文件" << endl;
		return -1;
	}

	//文件长度
	int Length_Plaintext = 0;
	int Encode_Times = 0;
	Read_Plaintext.seekg(0, ios::end);

	Length_Plaintext = (int)Read_Plaintext.tellg();
	Encode_Times = Length_Plaintext / 16 + 1;

	Read_Plaintext.seekg(0, ios::beg);

	//进行Encode_Times次
	for (int i = 1; i <= Encode_Times; i++) {

		unsigned char Plaintext_Byte[16] = { 0 };
		unsigned char Ciphertext_Byte[16] = { 0 };
		int j = 0;
		//最后一次是填充得到的
		if (i == Encode_Times) {
			for (j = 0; Read_Plaintext.tellg() != Length_Plaintext&& Read_Plaintext.tellg()>=0; j++)
				 Read_Plaintext.read((char*)&Plaintext_Byte[j],sizeof(Plaintext_Byte[j]));

			int Fill_Num = 16 - j;
			for (; j < 16; j++)
				Plaintext_Byte[j] = Fill_Num;
		}

		else {
			for (j = 0; j < 16; j++)
				Read_Plaintext.read((char*)&Plaintext_Byte[j], sizeof(Plaintext_Byte[j]));
		}


		Encode_128_bits_by_128_bits(Plaintext_Byte, key_input, Ciphertext_Byte);

		for (j = 0; j < 16; j++)
			Write_Ciphertext.write((char*)&Ciphertext_Byte[j], sizeof(Ciphertext_Byte[j]));
	}

	Read_Plaintext.close();
	Write_Ciphertext.close();
	cout << "加密完成" << endl;
	return 0;

}


int Decrypt_File_Operate(string Decrypted_text_Name, string Plaintext_Name, unsigned char* key_input) {

	ifstream Read_Ciphertext;
	ofstream Write_Plaintext;


	Read_Ciphertext.open(Decrypted_text_Name, ios::in| ios::binary);
	Write_Plaintext.open(Plaintext_Name, ios::out| ios::binary);

	if (!Read_Ciphertext.is_open()) {
		cout << "无法成功打开密文文件" << endl;
		return -1;
	}

	if (!Write_Plaintext.is_open()) {
		cout << "无法成功打开解密的文件" << endl;
		return -1;
	}

	//文件长度
	int Length_Plaintext = 0;
	int Encode_Times = 0;
	Read_Ciphertext.seekg(0, ios::end);

	Length_Plaintext = (int)Read_Ciphertext.tellg();
	Encode_Times = Length_Plaintext / 16;//密文肯定是16的倍数

	Read_Ciphertext.seekg(0, ios::beg);


	//进行Encode_Times次
	for (int i = 1; i <= Encode_Times; i++) {

		unsigned char Plaintext_Byte[16] = { 0 };
		unsigned char Ciphertext_Byte[16] = { 0 };
		int j = 0;

		for (j = 0; j < 16; j++)
			Read_Ciphertext.read((char*)&Ciphertext_Byte[j], sizeof(Ciphertext_Byte[j]));

		Decrypt_128_bits_by_128_bits(Ciphertext_Byte, key_input, Plaintext_Byte);

		//最后一次是填充得到的
		if (i == Encode_Times)
			for (j = 0; j < 16 - Plaintext_Byte[15]; j++)
				Write_Plaintext.write((char*)&Plaintext_Byte[j], sizeof(Plaintext_Byte[j]));
		else
			for (j = 0; j < 16 ; j++)
				Write_Plaintext.write((char*)&Plaintext_Byte[j], sizeof(Plaintext_Byte[j]));
		
	}

	Read_Ciphertext.close();
	Write_Plaintext.close();
	cout << "解密完成" << endl;
	return 0;
	

}

