#include<iostream>
#include"SHA_1.h"
using namespace std;




int main() {
	string Input_FileName = "C:\\Users\\戴尔\\Desktop\\Input.txt";
	string Hash_Value_FileName = "C:\\Users\\戴尔\\Desktop\\Hash.txt";


	cout << "请输入加密文件的名称" << endl;
	cin >> Input_FileName;
	cout << "请输入输出Hash值文件的名称" << endl;
	cin >> Hash_Value_FileName;
	File_Operate(Input_FileName, Hash_Value_FileName);

	return 0;

}