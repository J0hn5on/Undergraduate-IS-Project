#include<iostream>
#include<cmath>
#include "AES.h"
using namespace std;





int main() {

	string plaintext_char_input[16];
	string key_char_input[16];
	unsigned char Ciphertext[16] = { 0 };

	unsigned char plaintext_input[16] = { 0 };
	unsigned char key_input[16] = { 0 };


	//��������
    cout << "���������ģ���16��8λ������ɣ�8λ������16�������룩" << endl;
	for (int i = 0; i < 16; i++)
		cin >> plaintext_char_input[i];
    cout << "��������Կ����16��8λ������ɣ�8λ������16�������룩" << endl;
	for (int i = 0; i < 16; i++)
		cin >> key_char_input[i];

    for (int i = 0; i < 16; i++) {
        if (plaintext_char_input[i][0] >= 'A' && plaintext_char_input[i][0] <= 'F')
            plaintext_input[i] += (plaintext_char_input[i][0] - 'A' + 10) * 16;
        else if (plaintext_char_input[i][0] >= 'a' && plaintext_char_input[i][0] <= 'f')
            plaintext_input[i] += (plaintext_char_input[i][0] - 'a' + 10) * 16;
        else if (plaintext_char_input[i][0] >= '0' && plaintext_char_input[i][0] <= '9')
            plaintext_input[i] += (plaintext_char_input[i][0] - '0') * 16;

        if (plaintext_char_input[i][1] >= 'A' && plaintext_char_input[i][1] <= 'F')
            plaintext_input[i] += (plaintext_char_input[i][1] - 'A' + 10);
        else if (plaintext_char_input[i][1] >= 'a' && plaintext_char_input[i][1] <= 'f')
            plaintext_input[i] += (plaintext_char_input[i][1] - 'a' + 10);
        else if (plaintext_char_input[i][1] >= '0' && plaintext_char_input[i][1] <= '9')
            plaintext_input[i] += (plaintext_char_input[i][1] - '0');
    }


    //��Կ����

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



	//Encode_128_bits_by_128_bits(plaintext_input, key_input, Ciphertext);
    Decrypt_128_bits_by_128_bits(plaintext_input, key_input, Ciphertext);

    cout << "����Ϊ��" << endl;
	for (int i = 0; i < 16; i++)
		cout << hex << (int)Ciphertext[i]<<' ';


}