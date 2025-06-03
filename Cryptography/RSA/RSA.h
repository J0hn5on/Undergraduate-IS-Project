#pragma once
#include <iostream>
#include<NTL/ZZ.h>
using namespace std;
using namespace NTL;

#define BITS 512      //Ҫ��������� p , q �ı���λ���� BITS bits

void A_and_B_Generation(ZZ& b, ZZ& a, ZZ& Euler);

ZZ Encryption(ZZ& b, ZZ& n, ZZ& P);//���ܺ���

ZZ Decryption(ZZ& a, ZZ& n, ZZ& C); //���ܺ���

void KeyGeneration(ZZ& n, ZZ& b, ZZ& a);

bool Verify_Signature(ZZ Name, ZZ Signature, ZZ b, ZZ n);

int Issued_Certification(ZZ ID_Alice, ZZ n_Alice, ZZ a_Alice, ZZ b_Alice, ZZ ID_TA, ZZ n_TA, ZZ a_TA, ZZ b_TA, ZZ &s, string Certification_FileName);

bool Verify_Certification(ZZ ID_Alice, ZZ n_Alice, ZZ b_Alice, ZZ s, ZZ n_TA, ZZ b_TA);

string numberToString(ZZ num);

ZZ stringToNumber(string str);


