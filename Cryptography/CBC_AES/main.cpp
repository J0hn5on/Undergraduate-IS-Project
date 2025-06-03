#include<iostream>
using namespace std;


int Encode_File_Operate(string Plaintext_Name, string Ciphertext_Name, unsigned char* key_input);
int Decrypt_File_Operate(string Decrypted_text_Name, string Plaintext_Name, unsigned char* key_input);


int main() {

	string Plaintext_Name="C:\\Users\\����\\Desktop\\13-1.jpg";
	string Ciphertext_Name="C:\\Users\\����\\Desktop\\result.txt";
    string Decrypted_text_Name = "C:\\Users\\����\\Desktop\\Decrypted.jpg";
    unsigned char key_input[16] = { 0 };
    string key_char_input[16];


    cout << "��������Ҫ���ܵ��ļ�������" << endl;
    cin >> Plaintext_Name;
    cout << "��������Ҫ���ܵõ��ĵ��ļ�������" << endl;
    cin >> Ciphertext_Name;

    //�ڴ˴�Ҳ���Ե��ý��ܺ���
    cout << "��������Ҫ���ܵõ��ĵ��ļ�������" << endl;
    cin >> Decrypted_text_Name;


    //��������
    cout << "��������Կ����16��8λ������ɣ�8λ������16�������룩" << endl;
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

    //�ڴ˴�Ҳ���Ե��ý��ܺ���
    Decrypt_File_Operate(Ciphertext_Name, Decrypted_text_Name, key_input);

    
    return 0;


}