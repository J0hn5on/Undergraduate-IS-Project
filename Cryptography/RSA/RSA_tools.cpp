#include <iostream>
#include<fstream>
#include<NTL/ZZ.h>
#include"../RSA/RSA.h"
using namespace std;
using namespace NTL;

#define BITS 512      //Ҫ��������� p , q �ı���λ���� BITS bits

void A_and_B_Generation(ZZ& b, ZZ& a, ZZ& Euler) //����b,a
{
	RandomPrime(b, BITS, 10);
	a = InvMod(b, Euler);
}

ZZ Encryption(ZZ& b, ZZ& n, ZZ& P) //���ܺ���
{
	return PowerMod(P, b, n);
}

ZZ Decryption(ZZ& a, ZZ& n, ZZ& C) //���ܺ���
{
	return PowerMod(C, a, n);
}


// n=p*q,  b---������Կ,  d---������Կ
void KeyGeneration(ZZ& n, ZZ& b, ZZ& a) {
	ZZ  p, q, Euler;   //���� BITS ���ص������������ p , q    Euler=(p-1)*(q-1)
	RandomPrime(p, BITS, 10);//�����������������
	RandomPrime(q, BITS, 10);
	n = p * q;//���� n=p*q 
	Euler = (p - 1) * (q - 1);    //ŷ������ֵ euler(n)=(p-1)*(q-1)
	A_and_B_Generation(a, b, Euler);    //������Կ: d, e , d*e=1 Mod euler(n)
}



//ǩ����֤
bool Verify_Signature(ZZ Name, ZZ Signature, ZZ b, ZZ n) {

	ZZ Decryptedtext;
	Decryptedtext = Decryption(b, n, Signature);

	if (Name == Decryptedtext)
		return true;
	else
		return false;
}









//�γ����Ҫ���֤��䷢����֤

//Alice��֤��Cert(Alice)��ʽ���£�
//Cert(Alice) = (ID(Alice) || verAlice || s || ID(TA) || flag)
//����ǩ��s���¼���
//s = sigTA��˽Կ(ID(Alice) || verAlice)
//verAlice��ʾAlice�Ĺ�Կ��flag��ʶAlice�Ĺ�Կ����(����p��qΪ512��1024λ)
//��Ӧ����֤�㷨���䣬��
//verTA�Ĺ�Կ(ID(Alice) || verAlice, s) = true
//��˵��֤����ţ����򲻿��š�


int Issued_Certification(ZZ ID_Alice, ZZ n_Alice, ZZ a_Alice, ZZ b_Alice,
	ZZ ID_TA, ZZ n_TA, ZZ a_TA, ZZ b_TA,
	ZZ& s, string Certification_FileName)
{
	long Flag = BITS * 2;

	//s = sigTA��˽Կ(ID(Alice) || verAlice) �����������
	ZZ sigTA_Name = ((ID_Alice << Flag) + n_Alice * BITS + b_Alice) % n_TA;

	//��˽Կǩ��

	//sigTA_NameҪ��n_TAС����������������������������������������������������������������
	s = Encryption(a_TA, n_TA, sigTA_Name);



	ofstream Write;
	Write.open(Certification_FileName, ios::out);
	if (!Write.is_open()) {
		cout << "�޷��ɹ���֤���ļ�" << endl;
		return -1;
	}
	
		
	Write << ID_Alice << ' ';
	Write << n_Alice << ' ';
	Write << b_Alice;
	Write << s << ' ';
	Write << ID_TA << ' ';
	Write << (ZZ)Flag << ' ';
	cout << "֤��ǩ����ɣ��ļ���Ϊ" << Certification_FileName << endl;

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