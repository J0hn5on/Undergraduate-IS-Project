#pragma once
#include<iostream>
using namespace std;

#define MOD 256






unsigned char SubByte(unsigned char XY);

void ShiftRow(unsigned char Status[][4]);

int FiedldMult(int x);

void MixColumn(unsigned char Status[][4]);

void MixColumn_inverse(unsigned char Status[][4]);

void AddRoundKey(unsigned char Status[][4], unsigned char k[][4]);

void SubByte_Change(unsigned char Status[][4]);

void KeyExpansion(unsigned char key[16], unsigned char w[][4]);

void ShiftRow_inverse(unsigned char Status[][4]);

void AddRoundKey_inverse(unsigned char Status[][4], unsigned char k[][4]);

void SubByte_Change_inverse(unsigned char Status[][4]);

void Encode_128_bits_by_128_bits(unsigned char* plaintext_input, unsigned char* key_input, unsigned char* Ciphertext);

void Decrypt_128_bits_by_128_bits(unsigned char* Ciphertext_input, unsigned char* key_input, unsigned char* plaintext);

int Encode_File_Operate(string Plaintext_Name, string Ciphertext_Name, unsigned char* key_input);

int Decrypt_File_Operate(string Decrypted_text_Name, string Plaintext_Name, unsigned char* key_input);