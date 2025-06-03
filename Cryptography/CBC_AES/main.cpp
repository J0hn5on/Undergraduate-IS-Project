#include<iostream>
using namespace std;


int Encode_File_Operate(string Plaintext_Name, string Ciphertext_Name, unsigned char* key_input);
int Decrypt_File_Operate(string Decrypted_text_Name, string Plaintext_Name, unsigned char* key_input);


int main() {

	string Plaintext_Name="C:\\Users\\戴尔\\Desktop\\13-1.jpg";
	string Ciphertext_Name="C:\\Users\\戴尔\\Desktop\\result.txt";
    string Decrypted_text_Name = "C:\\Users\\戴尔\\Desktop\\Decrypted.jpg";
    unsigned char key_input[16] = { 0 };
    string key_char_input[16];


    cout << "请输入想要加密的文件的名称" << endl;
    cin >> Plaintext_Name;
    cout << "请输入想要加密得到的的文件的名称" << endl;
    cin >> Ciphertext_Name;

    //在此处也可以调用解密函数
    cout << "请输入想要解密得到的的文件的名称" << endl;
    cin >> Decrypted_text_Name;


    //密文输入
    cout << "请输入密钥（由16个8位数字组成，8位数字用16进制输入）" << endl;
	for (int i = 0; i < 16; i++)
		cin >> key_char_input[i];

    for (int i = 0; i < 16; i++) {
        if (key_char_input[i][0] >= 'A' && key_char_input[i][0] <= 'F')
            key_input[i] += (key_char_input[i][0] - 'A' + 10) * 16;
        else if (key_char_input[i][0] >= 'a' && key_char_input[i][0] <= 'f')
            key_input[i] += (key_char_input[i][0] - 'a' + 10) * 16;
        else if (key_char_input[i][0] >= '0' && key_char_input[i][0] <= '9')
            key_input[i] += (key_char_input[i][0] - '0') * 16;

        if (key_char_input[i][1] >= 'A' && key_char_input[i][1] <= 'F')
            key_input[i] += (key_char_input[i][1] - 'A' + 10);
        else if (key_char_input[i][1] >= 'a' && key_char_input[i][1] <= 'f')
            key_input[i] += (key_char_input[i][1] - 'a' + 10);
        else if (key_char_input[i][1] >= '0' && key_char_input[i][1] <= '9')
            key_input[i] += (key_char_input[i][1] - '0');
    }




    Encode_File_Operate(Plaintext_Name, Ciphertext_Name, key_input);

    //在此处也可以调用解密函数
    Decrypt_File_Operate(Ciphertext_Name, Decrypted_text_Name, key_input);

    
    return 0;


}