#include<iostream>
#include<fstream>
#include<cmath>
#include<NTL/ZZ.h>
#include"../SHA-1/SHA_1.h"
#include "../AES/AES.h"
using namespace std;
using namespace NTL;


//生成文件m的SHA - 1散列值SHA - 1(m)
ZZ Cal_SHA_Value(string Input_FileName) {

	ifstream Read;

	Read.open(Input_FileName, ios::in | ios::binary);


	if (!Read.is_open()) {
		cout << "无法成功打开初值文件" << endl;
		return (ZZ) - 1;
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

			SHA_1_PAD(Scattered_String, HEX, j - 1, Length_Plaintext * 8);

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
	ZZ H0_Z = (ZZ)H0;
	ZZ H1_Z = (ZZ)H1;
	ZZ H2_Z = (ZZ)H2;
	ZZ H3_Z = (ZZ)H3;
	ZZ H4_Z = (ZZ)H4;

	ZZ Result = (H0_Z << (32L * 4L)) + (H1_Z << (32L * 3L)) + (H2_Z << (32L * 2L)) + (H3_Z << (32L * 1L)) + H4_Z;
	Read.close();

	return Result;
}


