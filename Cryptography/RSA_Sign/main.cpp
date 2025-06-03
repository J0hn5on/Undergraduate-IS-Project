#include <iostream>
#include<NTL/ZZ.h>
#include"../RSA/RSA.h"
using namespace std;
using namespace NTL;


int main() {

	//n and b is public
    //a,p,q is private
    //p,q,Eular这些加解密用不到的已经封装到void KeyGeneration(ZZ& n, ZZ& b, ZZ& a)中
	ZZ  n, b, a;   // n=p*q, b---加密密钥,  d---解密密钥
	ZZ Name, Signature;
	cout << "请输入明文：" << endl;
	cin >> Name;

	KeyGeneration(n, b, a);


	//签名
	Signature = Encryption(a, n, Name);
	cout << "签名是：" << Signature << endl;


	//验证
	if (Verify_Signature(Name, Signature, b, n))
		cout << "经验证，是对方的签名" << endl;
	else
		cout << "经验证，不是对方的签名，请注意安全" << endl;


	return 0;





}