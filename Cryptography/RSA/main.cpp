#include <iostream>
#include<NTL/ZZ.h>
#include"../RSA/RSA.h"
using namespace std;
using namespace NTL;


int main()
{
	//n and b is public
	//a,p,q is private
	//p,q,Eular这些加解密用不到的已经封装到void KeyGeneration(ZZ& n, ZZ& b, ZZ& a)中
	ZZ  n, b, a;   // n=p*q, b---加密密钥,  d---解密密钥
	ZZ Plaintext, Ciphertext;
	cout << "请输入明文：" << endl;
	cin >> Plaintext;

	KeyGeneration(n, b, a);

	

	//加密
	Ciphertext = Encryption(b, n, Plaintext);
	cout << "密文是：" << Ciphertext << endl;

	//解密: M=C^a(Mod n)
	ZZ Decryptedtext;
	Decryptedtext = Decryption(a, n, Ciphertext);

	return 0;

}