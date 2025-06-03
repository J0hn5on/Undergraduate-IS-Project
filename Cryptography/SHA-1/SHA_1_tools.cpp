#include<iostream>
#include<fstream>
#include<cmath>
#include"SHA_1.h"
using namespace std;

unsigned int K[80];

void Generate_Kt() {
	int i = 0;
	for (i = 0; i < 20; i++) 
		K[i] = 0x5A827999;
	for (; i < 40; i++) 
		K[i] = 0x6ED9EBA1;
	for (; i < 60; i++) 
		K[i] = 0x8F1BBCDC;
	for (; i < 80; i++) 
		K[i] = 0xCA62C1D6;
	return;
}

int File_Operate(string Input_FileName,string Hash_Value_FileName) {

	ifstream Read;
	ofstream Write;

	Write.open(Hash_Value_FileName, ios::out | ios::binary);
	Read.open(Input_FileName, ios::in | ios::binary);


	if (!Read.is_open()) {
		cout << "无法成功打开初值文件" << endl;
		return -1;
	}

	//文件长度
	int Length_Plaintext = 0;
	int String_Nums = 0;
	Read.seekg(0, ios::end);

	Length_Plaintext = (int)Read.tellg();
	String_Nums = Length_Plaintext / 512 + 1;//注意被整除

	Read.seekg(0, ios::beg);

	unsigned int H0 = 0x67452301, H1 = 0xEFCDAB89, H2 = 0x98BADCFE, H3 = 0x10325476, H4 = 0xC3D2E1F0;


	Generate_Kt();

	for (int i = 1; i <= String_Nums; i++) {

		unsigned char HEX[64] = { 0 };
		unsigned int INT[16] = { 0 };
		if (i == String_Nums) {
			unsigned char Scattered_String[64] = { 0 };
			int j = 0;
			for (; !Read.eof(); j++)//读到头
				Read.read((char*)&Scattered_String[j], sizeof(Scattered_String[j]));

			SHA_1_PAD(Scattered_String, HEX, j-1, Length_Plaintext*8);

		}
		else
			for (int j = 0; j < 64; j++)
				Read.read((char*)&HEX[j], sizeof(HEX[j]));
		//char转为int
		for (int j = 0; j < 16; j++)
			for (int k = 0; k < 4; k++)
				INT[j] += HEX[4 * j + k] * (unsigned int)pow(256, 3 - k);


		SHA_1_Cal(INT, H0, H1, H2, H3, H4);

	}

	
	Write << hex << H0 << H1 << H2 << H3 << H4;


	Read.close();
	Write.close();

	cout << "SHA-1函数调用完毕，Hash值已生成" << endl;
	return 0;
}


string Binary(int x){
	string s = "";
	while (x) {
		if (x % 2 == 0)
			s = '0' + s;
		else
			s = '1' + s;
		x /= 2;
	}
	return s;
}

//64个char
void SHA_1_PAD(unsigned char *Scattered_String, unsigned char * Padded_String, int Length,int Sum_Length) {

	
	int i = 0;

	for (i = 0; i < Length; i++)
		Padded_String[i] = Scattered_String[i];



	//合并后面的
	Padded_String[i++] = 0b10000000;

	int D = (55 - Length);

	for (int j = 0; j < D; j++)
		Padded_String[i++] = 0;



	unsigned char L[64] = { 0 };

	string L_String = Binary(Sum_Length);

	

	for (int j = 0; j < (int)L_String.size(); j++)
		L[63 - j] = L_String[(int)L_String.size() - 1 - j] - '0';

	for (int k=0; k < 8;k++, i++)
		for (int j = 0; j < 8; j++)
			Padded_String[i] += L[8 * k + j] * (unsigned int)pow(2, 7 - j);


	return;
}






unsigned int Ft(int t, unsigned int B, unsigned int C, unsigned int D) {

	int Segment = t / 20;
	unsigned int Result = 0;

	switch (Segment)
	{
	case 0:
		Result = (B & C) | ((~B) & D);
		break;
	case 1:
		Result = B ^ C ^ D;
		break;
	case 2:
		Result = (B & C) | (B & D) | (C & D);
		break;
	case 3:
		Result = B ^ C ^ D;
		break;
	default:
		break;
	}




	return Result;
}


//字的循环左移
unsigned int ROTLs(int n ,unsigned int Before) {
	unsigned int res = Before << n;
	res |= Before >> (32 - n);
	return res;
}




void SHA_1_Cal(const unsigned int M[16], unsigned int &H0, unsigned int &H1, unsigned int &H2, unsigned int &H3, unsigned int &H4) {

	unsigned int W[80] = { 0 };
	for (int i = 0; i < 16; i++)
		W[i] = M[i];

	for (int i = 16; i <= 79; i++)
		W[i] = ROTLs(1, W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]);

	unsigned int A = H0, B = H1, C = H2, D = H3, E = H4;

	for (int i = 0; i < 80; i++) {

		unsigned int temp = ROTLs(5, A) + Ft(i, B, C, D) + E + W[i] + K[i];
		E = D;
		D = C;
		C = ROTLs(30, B);
		B = A;
		A = temp;
	}

	H0 += A;
	H1 += B;
	H2 += C;
	H3 += D;
	H4 += E;

	return;
}