#include<iostream>
#include"SHA_1.h"
using namespace std;




int main() {
	string Input_FileName = "C:\\Users\\����\\Desktop\\Input.txt";
	string Hash_Value_FileName = "C:\\Users\\����\\Desktop\\Hash.txt";


	cout << "����������ļ�������" << endl;
	cin >> Input_FileName;
	cout << "���������Hashֵ�ļ�������" << endl;
	cin >> Hash_Value_FileName;
	File_Operate(Input_FileName, Hash_Value_FileName);

	return 0;

}