#include <iostream>
#include<NTL/ZZ.h>
#include"../RSA/RSA.h"
using namespace std;
using namespace NTL;


int main() {

	//n and b is public
    //a,p,q is private
    //p,q,Eular��Щ�ӽ����ò������Ѿ���װ��void KeyGeneration(ZZ& n, ZZ& b, ZZ& a)��
	ZZ  n, b, a;   // n=p*q, b---������Կ,  d---������Կ
	ZZ Name, Signature;
	cout << "���������ģ�" << endl;
	cin >> Name;

	KeyGeneration(n, b, a);


	//ǩ��
	Signature = Encryption(a, n, Name);
	cout << "ǩ���ǣ�" << Signature << endl;


	//��֤
	if (Verify_Signature(Name, Signature, b, n))
		cout << "����֤���ǶԷ���ǩ��" << endl;
	else
		cout << "����֤�����ǶԷ���ǩ������ע�ⰲȫ" << endl;


	return 0;





}