#include <iostream>
#include<NTL/ZZ.h>
#include"../RSA/RSA.h"
using namespace std;
using namespace NTL;


int main()
{
	//n and b is public
	//a,p,q is private
	//p,q,Eular��Щ�ӽ����ò������Ѿ���װ��void KeyGeneration(ZZ& n, ZZ& b, ZZ& a)��
	ZZ  n, b, a;   // n=p*q, b---������Կ,  d---������Կ
	ZZ Plaintext, Ciphertext;
	cout << "���������ģ�" << endl;
	cin >> Plaintext;

	KeyGeneration(n, b, a);

	

	//����
	Ciphertext = Encryption(b, n, Plaintext);
	cout << "�����ǣ�" << Ciphertext << endl;

	//����: M=C^a(Mod n)
	ZZ Decryptedtext;
	Decryptedtext = Decryption(a, n, Ciphertext);

	return 0;

}