#include <iostream>
#include<fstream>
#include<NTL/ZZ.h>
#include"../RSA/RSA.h"
using namespace std;
using namespace NTL;


int main() {

	ZZ ID_Alice, n_Alice, a_Alice, b_Alice;
	ZZ ID_TA, n_TA, a_TA, b_TA;
	ZZ s;

	cout << "请输入Alice的身份信息（ID_Alice）" << endl;
	cin >> ID_Alice;
	cout << "请输入TA的身份信息（ID_TA）" << endl;
	cin >> ID_TA;




	string Certification_FileName;
	cout << "想要生成证书文件的名字" << endl;
	cin >> Certification_FileName;

	

	cout << "正在初始化TA......" << endl;
	KeyGeneration(n_TA, b_TA, a_TA);
	cout << "TA初始化完成" << endl;

	cout << "Alice正在申请密钥" << endl;
	KeyGeneration(n_Alice, b_Alice, a_Alice);
	cout << "Alice申请密钥完成" << endl;

	//颁发
	Issued_Certification(ID_Alice, n_Alice, a_Alice, b_Alice, ID_TA, n_TA, a_TA, b_TA, s, Certification_FileName);
	//验证
	if (Verify_Certification(ID_Alice, n_Alice, b_Alice, s, n_TA, b_TA))
		cout << "证书验证通过" << endl;
	else
		cout << "证书验证失败" << endl;



	return 0;



}