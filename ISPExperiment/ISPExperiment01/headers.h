#pragma once
#define HAVE_REMOTE
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MAX_PROTO_TEXT_LEN 16 // ��Э��������󳤶�
#define MAX_PROTO_NUM 12      // ��Э������

// ����mac��ַ��ʽ
typedef struct mac_address
{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
    u_char byte5;
    u_char byte6;
}mac_address;

// ������̫���ײ���ʽ
typedef struct ethernet_header
{
    mac_address des_mac_addr;  //6byteĿ�ĵ�ַ
    mac_address src_mac_addr;  //6byteԴ��ַ
    u_short type;              //2byte����
                               //���ݼ�CRC
}ethernet_header;

// ����IPv4��ַ�ṹ
typedef struct ipv4_address
{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
}ip_address;

// ����IP�ײ���ʽ
typedef struct ipv4_header
{
    u_char ver_ihl;         // 4bit�汾��4bit�ײ�����
    u_char tos;             // 8bit��������
    u_short tlen;           // 16bit�ܳ���
    u_short identification; // 16bit��ʶ��
    u_short flags_fo;       // 16bit��ƫ����
    u_char ttl;             // 8bit����ʱ��
    u_char proto;           // 8bitЭ��
    u_short crc;            // 16bit�ײ�У���
    ipv4_address saddr;     // 32bitԴip��ַ
    ipv4_address daddr;     // 32bitĿ�ĵ�ַ
    u_int op_pad;           // ѡ����λ
}ip_header;

// ����UDP�ײ���ʽ
typedef struct udp_header
{
    u_short sport; // 16bitԴ�˿�
    u_short dport; // 16bitĿ�Ķ˿�
    u_short len;   // 16bit����
    u_short crc;   // 16bit У���
}udp_header;

// L2TP�ײ���ʽ
typedef struct l2tp_header
{
    u_char TLxxSxOP;       // T�����ͣ�Type����ȡֵΪ��0��ʱ��ʾ������Ϣ��ȡֵΪ��1��ʱ��ʾ������Ϣ�� 
                           // L��������λ��־��ȡֵΪ��1��ʱ��ʾ����ͷ�д��ڳ����ֶ�Length��������Ϣ�б���Ϊ��1���� 
                           // S��˳���ֶ���λ��־��ȡֵΪ��1��ʱ��ʾ����ͷ�д���Ns��Nr�ֶΡ�������Ϣ�б���Ϊ��1����
                           // O��ȡֵΪ��1��ʱ��ʾ����ͷ�д���offset size�ֶΡ�������Ϣ�б���Ϊ��0����
                           // P�����ȼ���Priority����ֻ����������Ϣ��������Ϣ�б���Ϊ��0����
                           // x������λ
    u_char xxxxVer;        // Ver���汾��
    u_short Length;        // ��Ϣ�ܳ���
    u_short TunnelId;      // �����ʶ�� ��������
    u_short SessionId;     // �Ự��ʶ�� ��������
    u_short Ns;            // ��ǰ��Ϣ˳���
    u_short Nr;            // ��һ������Ϣ˳��ţ�������ϢΪ�����ֶ�
    u_short Offsetsize;    // ƫ��ֵ ָʾ�غɿ�ʼλ��
    u_short Offser_pading; // ƫ�������

}l2tp_header;