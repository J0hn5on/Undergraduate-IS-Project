#pragma once
#define HAVE_REMOTE
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MAX_PROTO_TEXT_LEN 16 // 子协议名称最大长度
#define MAX_PROTO_NUM 12      // 子协议数量

// 定义mac地址格式
typedef struct mac_address
{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
    u_char byte5;
    u_char byte6;
}mac_address;

// 定义以太网首部格式
typedef struct ethernet_header
{
    mac_address des_mac_addr;  //6byte目的地址
    mac_address src_mac_addr;  //6byte源地址
    u_short type;              //2byte类型
                               //数据及CRC
}ethernet_header;

// 定义IPv4地址结构
typedef struct ipv4_address
{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
}ip_address;

// 定义IP首部格式
typedef struct ipv4_header
{
    u_char ver_ihl;         // 4bit版本和4bit首部长度
    u_char tos;             // 8bit服务类型
    u_short tlen;           // 16bit总长度
    u_short identification; // 16bit标识号
    u_short flags_fo;       // 16bit段偏移量
    u_char ttl;             // 8bit生存时间
    u_char proto;           // 8bit协议
    u_short crc;            // 16bit首部校验和
    ipv4_address saddr;     // 32bit源ip地址
    ipv4_address daddr;     // 32bit目的地址
    u_int op_pad;           // 选项和填补位
}ip_header;

// 定义UDP首部格式
typedef struct udp_header
{
    u_short sport; // 16bit源端口
    u_short dport; // 16bit目的端口
    u_short len;   // 16bit长度
    u_short crc;   // 16bit 校验和
}udp_header;

// L2TP首部格式
typedef struct l2tp_header
{
    u_char TLxxSxOP;       // T：类型（Type），取值为“0”时表示数据消息，取值为“1”时表示控制消息。 
                           // L：长度在位标志，取值为“1”时表示报文头中存在长度字段Length。控制消息中必须为“1”。 
                           // S：顺序字段在位标志，取值为“1”时表示报文头中存在Ns和Nr字段。控制消息中必须为“1”。
                           // O：取值为“1”时表示报文头中存在offset size字段。控制消息中必须为“0”。
                           // P：优先级（Priority），只用于数据消息。控制消息中必须为“0”。
                           // x：保留位
    u_char xxxxVer;        // Ver：版本号
    u_short Length;        // 消息总长度
    u_short TunnelId;      // 隧道标识符 本地意义
    u_short SessionId;     // 会话标识符 本地意义
    u_short Ns;            // 当前消息顺序号
    u_short Nr;            // 下一控制消息顺序号，数据消息为保留字段
    u_short Offsetsize;    // 偏移值 指示载荷开始位置
    u_short Offser_pading; // 偏移量填充

}l2tp_header;