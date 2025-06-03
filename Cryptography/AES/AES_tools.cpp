#include<iostream>
#include<cmath>
#include "AES.h"
using namespace std;

unsigned char S_box[16][16] = {
        0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
        0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
        0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
        0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
        0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
        0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
        0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
        0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
        0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
        0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
        0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
        0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
        0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
        0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
        0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
        0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16,
};
unsigned char S_box_inverse[16][16] = {
    0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,
    0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,
    0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,
    0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,
    0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,
    0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,
    0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,
    0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,
    0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,
    0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,
    0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,
    0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
    0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,
    0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,
    0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,
    0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d,
};



int Fermat(const int n, const int k) {
    long long ans = 1;
    for (long long num = n, t = k; t; num = num * num % MOD, t >>= 1)
        if (t & 1)
            ans = ans * num % MOD;
    return (int)ans;
}
int inv(const int num) {
    return Fermat(num, MOD - 2);
}


unsigned char SubByte(unsigned char XY) {

    unsigned char X = XY / 16, Y = XY % 16;

    return S_box[X][Y];
}

unsigned char SubByte_inverse(unsigned char XY) {

    unsigned char X = XY / 16, Y = XY % 16;

    return S_box_inverse[X][Y];
}

void SubByte_Change(unsigned char Status[][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            Status[i][j] = SubByte(Status[i][j]);


}

void SubByte_Change_inverse(unsigned char Status[][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            Status[i][j] = SubByte_inverse(Status[i][j]);


}

void ShiftRow(unsigned char Status[][4]) {
    unsigned char temp[6];

    temp[0] = Status[1][0];
    temp[1] = Status[2][0];
    temp[2] = Status[2][1];
    temp[3] = Status[3][0];
    temp[4] = Status[3][1];
    temp[5] = Status[3][2];
    
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            Status[i][j] = Status[i][(j + i) % 4];
        }

    Status[1][3] = temp[0];
    Status[2][2] = temp[1];
    Status[2][3] = temp[2];
    Status[3][1] = temp[3];
    Status[3][2] = temp[4];
    Status[3][3] = temp[5];
    //循环修正

    return;
}

void ShiftRow_inverse(unsigned char Status[][4]) {
    unsigned char temp[6];

    temp[0] = Status[1][3];
    temp[1] = Status[2][3];
    temp[2] = Status[2][2];
    temp[3] = Status[3][3];
    temp[4] = Status[3][2];
    temp[5] = Status[3][1];

    for (int i = 0; i < 4; i++)
        for (int j = 3; j >=0; j--) {
            Status[i][j] = Status[i][(j - i)%4];
        }

    Status[1][0] = temp[0];
    Status[2][1] = temp[1];
    Status[2][0] = temp[2];
    Status[3][2] = temp[3];
    Status[3][1] = temp[4];
    Status[3][0] = temp[5];
    //循环修正

    return;
}


int FiedldMult(int x) {
    int t = x / 128;
    int y = (x - t * 128) * 2;
    if (t == 1)
        y = y ^ 27;
    return y;
}

void MixColumn(unsigned char Status[][4]) {
    for (int c = 0; c < 4; c++) {

        int x[4] = { 0 };
        for (int i = 0; i < 4; i++)
            x[i] = Status[i][c];

        Status[0][c] = x[1] ^ x[2] ^ x[3];
        Status[1][c] = x[0] ^ x[2] ^ x[3];
        Status[2][c] = x[0] ^ x[1] ^ x[3];
        Status[3][c] = x[1] ^ x[2] ^ x[0];

        x[0] = FiedldMult(x[0]);
        x[1] = FiedldMult(x[1]);
        x[2] = FiedldMult(x[2]);
        x[3] = FiedldMult(x[3]);

        Status[0][c] = x[1] ^ x[0] ^ Status[0][c];
        Status[1][c] = x[1] ^ x[2] ^ Status[1][c];
        Status[2][c] = x[3] ^ x[2] ^ Status[2][c];
        Status[3][c] = x[0] ^ x[3] ^ Status[3][c];
    }
}




void MixColumn_inverse(unsigned char Status[][4]) {
    for (int c = 0; c < 4; c++) {

        int x[4] = { 0 };
        for (int i = 0; i < 4; i++)
            x[i] = Status[i][c];

        Status[0][c] = x[1] ^ x[2] ^ x[3];
        Status[1][c] = x[0] ^ x[2] ^ x[3];
        Status[2][c] = x[0] ^ x[1] ^ x[3];
        Status[3][c] = x[1] ^ x[2] ^ x[0];

        x[0] = FiedldMult(x[0]);
        x[1] = FiedldMult(x[1]);
        x[2] = FiedldMult(x[2]);
        x[3] = FiedldMult(x[3]);

        Status[0][c] = x[1] ^ x[0] ^ Status[0][c];
        Status[1][c] = x[1] ^ x[2] ^ Status[1][c];
        Status[2][c] = x[3] ^ x[2] ^ Status[2][c];
        Status[3][c] = x[0] ^ x[3] ^ Status[3][c];

        x[0] = FiedldMult(x[0] ^ x[2]);
        x[1] = FiedldMult(x[1] ^ x[3]);

        Status[0][c] = Status[0][c] ^ x[0];
        Status[1][c] = Status[1][c] ^ x[1];
        Status[2][c] = Status[2][c] ^ x[0];
        Status[3][c] = Status[3][c] ^ x[1];

        x[0] = FiedldMult(x[0] ^ x[1]);

        Status[0][c] = Status[0][c] ^ x[0];
        Status[1][c] = Status[1][c] ^ x[0];
        Status[2][c] = Status[2][c] ^ x[0];
        Status[3][c] = Status[3][c] ^ x[0];
    }
}


void AddRoundKey(unsigned char Status[][4], unsigned char k[][4]) {

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            Status[i][j] ^= k[i][j];

    return;
}

void AddRoundKey_inverse(unsigned char Status[][4], unsigned char k[][4]) {

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            Status[i][j] ^= k[i][j];
    return;
}


void KeyExpansion(unsigned char key[16], unsigned char w[][4])//key:16字节  w:44个字
{
    unsigned char temp[4];
    for (int i = 0; i < 4; i++) {//第一个for循环，填充w的前4个字
        w[i][0] = key[4 * i];
        w[i][1] = key[4 * i + 1];
        w[i][2] = key[4 * i + 2];
        w[i][3] = key[4 * i + 3];
    }

    for (int i = 4; i < 44; i++)//第二个for循环，填充后面的内容
    {
        temp[0] = w[i-1][0];//保存上一个字
        temp[1] = w[i-1][1];
        temp[2] = w[i-1][2];
        temp[3] = w[i-1][3];

        if (i % 4 == 0) {

            unsigned char temp_RotWord;
            unsigned char Rc[11] = { 0,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36 };
            temp_RotWord = temp[0];

            temp[0] = SubByte(temp[1]);
            temp[1] = SubByte(temp[2]);
            temp[2] = SubByte(temp[3]);
            temp[3] = SubByte(temp_RotWord);

            temp[0] = temp[0] ^ Rc[i / 4];//对保存的上一个字进行复杂的处理
        }//如果整除4      
        w[i][0] = w[i - 4][0] ^ temp[0];
        w[i][1] = w[i - 4][1] ^ temp[1];
        w[i][2] = w[i - 4][2] ^ temp[2];
        w[i][3] = w[i - 4][3] ^ temp[3];/*将上一个字（处理或没处理过）
                               与4个字之前的字进行异或，得到当前的字*/

    }
}



void Encode_128_bits_by_128_bits(unsigned char *plaintext_input,unsigned char *key_input, unsigned char *Ciphertext) {
    

    unsigned char plaintext_matrix[4][4] = { 0 };
    unsigned char All_key_matrix[44][4] = { 0 };
    unsigned char key_matrix[4][4] = { 0 };


    //密钥编排
    KeyExpansion(key_input, All_key_matrix);


    //明文矩阵
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            plaintext_matrix[i][j] = plaintext_input[i + j * 4];



    //轮密钥0
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            key_matrix[i % 4][j] = All_key_matrix[j][i];

    AddRoundKey(plaintext_matrix, key_matrix);



    //1-9轮加密
    for (int k = 1; k <= 9; k++) {

        //轮密钥k+1
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                key_matrix[i][j] = All_key_matrix[j + 4 * k][i];

        SubByte_Change(plaintext_matrix);
        ShiftRow(plaintext_matrix);
        MixColumn(plaintext_matrix);
        AddRoundKey(plaintext_matrix, key_matrix);
    }

    //10轮加密
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            key_matrix[i][j] = All_key_matrix[j + 40][i];

    SubByte_Change(plaintext_matrix);
    ShiftRow(plaintext_matrix);
    AddRoundKey(plaintext_matrix, key_matrix);



    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            Ciphertext[i + j * 4] = plaintext_matrix[i][j];

    return;

}





void Decrypt_128_bits_by_128_bits(unsigned char* Ciphertext_input, unsigned char* key_input, unsigned char* plaintext) {

    unsigned char Ciphertext_matrix[4][4] = { 0 };
    unsigned char All_key_matrix[44][4] = { 0 };
    unsigned char key_matrix[4][4] = { 0 };


    //密钥编排
    KeyExpansion(key_input, All_key_matrix);


    //密文矩阵
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            Ciphertext_matrix[i][j] = Ciphertext_input[i + j * 4];




    //0轮解密
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            key_matrix[i][j] = All_key_matrix[j + 40][i];
    AddRoundKey_inverse(Ciphertext_matrix, key_matrix);
    ShiftRow_inverse(Ciphertext_matrix);
    SubByte_Change_inverse(Ciphertext_matrix);
    
   


    //1-9轮解密
    for (int k = 1; k <= 9; k++) {

        //轮密钥k+1
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                key_matrix[i][j] = All_key_matrix[j + 4 * (10-k)][i];
        AddRoundKey_inverse(Ciphertext_matrix, key_matrix);
        MixColumn_inverse(Ciphertext_matrix);
        ShiftRow_inverse(Ciphertext_matrix);
        SubByte_Change_inverse(Ciphertext_matrix);

        
    }


    //轮密钥10
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            key_matrix[i % 4][j] = All_key_matrix[j][i];


    AddRoundKey_inverse(Ciphertext_matrix, key_matrix);



    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            plaintext[i + j * 4] = Ciphertext_matrix[i][j];

    return;

}