#pragma once
#include<iostream>
#include<string>
using namespace std;


void Generate_Kt();

int File_Operate(string Input_FileName, string Hash_Value_FileName);

string Binary(int x);


void SHA_1_PAD(unsigned char* Scattered_String, unsigned char* Padded_String, int Length, int Sum_Length);

unsigned int Ft(int t, unsigned int B, unsigned int C, unsigned int D);

unsigned int ROTLs(int n, unsigned int Before);

void SHA_1_Cal(const unsigned int M[16], unsigned int& H0, unsigned int& H1, unsigned int& H2, unsigned int& H3, unsigned int& H4);