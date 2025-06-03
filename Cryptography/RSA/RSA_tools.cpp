#include <iostream>
#include<fstream>
#include<NTL/ZZ.h>
#include"../RSA/RSA.h"
using namespace std;
using namespace NTL;

#define BITS 512      //要求概率素数 p , q 的比特位数达 BITS bits

void A_and_B_Generation(ZZ& b, ZZ& a, ZZ& Euler) //生成b,a
{
	RandomPrime(b, BITS, 10);
	a = InvMod(b, Euler);
}

ZZ Encryption(ZZ& b, ZZ& n, ZZ& P) //加密函数
{
	return PowerMod(P, b, n);
}

ZZ Decryption(ZZ& a, ZZ& n, ZZ& C) //解密函数
{
	return PowerMod(C, a, n);
}


// n=p*q,  b---加密密钥,  d---解密密钥
void KeyGeneration(ZZ& n, ZZ& b, ZZ& a) {
	ZZ  p, q, Euler;   //两个 BITS 比特的随机概率素数 p , q    Euler=(p-1)*(q-1)
	RandomPrime(p, BITS, 10);//随机生成两个大素数
	RandomPrime(q, BITS, 10);
	n = p * q;//计算 n=p*q 
	Euler = (p - 1) * (q - 1);    //欧拉函数值 euler(n)=(p-1)*(q-1)
	A_and_B_Generation(a, b, Euler);    //生成密钥: d, e , d*e=1 Mod euler(n)
}



//签名验证
bool Verify_Signature(ZZ Name, ZZ Signature, ZZ b, ZZ n) {

	ZZ Decryptedtext;
	Decryptedtext = Decryption(b, n, Signature);

	if (Name == Decryptedtext)
		return true;
	else
		return false;
}









//课程设计要求的证书颁发和验证

//Alice的证书Cert(Alice)格式如下：
//Cert(Alice) = (ID(Alice) || verAlice || s || ID(TA) || flag)
//其中签名s如下计算
//s = sigTA的私钥(ID(Alice) || verAlice)
//verAlice表示Alice的公钥，flag标识Alice的公钥长度(素数p和q为512或1024位)
//对应的验证算法不变，即
//verTA的公钥(ID(Alice) || verAlice, s) = true
//则说明证书可信，否则不可信。


int Issued_Certification(ZZ ID_Alice, ZZ n_Alice, ZZ a_Alice, ZZ b_Alice,
	ZZ ID_TA, ZZ n_TA, ZZ a_TA, ZZ b_TA,
	ZZ& s, string Certification_FileName)
{
	long Flag = BITS * 2;

	//s = sigTA的私钥(ID(Alice) || verAlice) 括号里的内容
	ZZ sigTA_Name = ((ID_Alice << Flag) + n_Alice * BITS + b_Alice) % n_TA;

	//用私钥签名

	//sigTA_Name要比n_TA小！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	s = Encryption(a_TA, n_TA, sigTA_Name);



	ofstream Write;
	Write.open(Certification_FileName, ios::out);
	if (!Write.is_open()) {
		cout << "无法成功打开证书文件" << endl;
		return -1;
	}
	
		
	Write << ID_Alice << ' ';
	Write << n_Alice << ' ';
	Write << b_Alice;
	Write << s << ' ';
	Write << ID_TA << ' ';
	Write << (ZZ)Flag << ' ';
	cout << "证书签发完成，文件名为" << Certification_FileName << endl;

	Write.close();

	return 0;
}


bool Verify_Certification(ZZ ID_Alice, ZZ n_Alice, ZZ b_Alice, ZZ s, ZZ n_TA, ZZ b_TA) {


	ZZ sigTA_Name = ((ID_Alice << BITS * 2) + n_Alice * BITS + b_Alice)%n_TA;

	if (Verify_Signature(sigTA_Name, s, b_TA, n_TA))
		return true;
	else
		return false;

}



string numberToString(ZZ num)
{
	long len = (long)ceil(log(num) / log(128));
	char str[BITS] = { 0 };
	for (long i = len - 1; i >= 0; i--)
	{
		str[i] = conv<int>(num % 128);
		num /= 128;
	}

	return (string)str;
}

ZZ stringToNumber(string str)
{
	ZZ number = conv<ZZ>(str[0]);
	long len = str.length();
	for (long i = 1; i < len; i++)
	{
		number *= 128;
		number += conv<ZZ>(str[i]);
	}

	return number;
}