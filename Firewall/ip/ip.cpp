/*最终定稿*/

#include <unistd.h>
#include <netdb.h>  //gethostbyname
#include <arpa/inet.h>  //ntohl
#include <iostream>
using namespace std;

int get_local_ip(int& ip) {
    char hostname[128];
    int ret = gethostname(hostname, sizeof(hostname));
    if (ret == -1) {
        return -1;
    }
    struct hostent* hent;
    hent = gethostbyname(hostname);
    if (NULL == hent) {
        return -1;
    }
    //直接取h_addr_list列表中的第一个地址h_addr
    ip = ntohl(((struct in_addr*)hent->h_addr)->s_addr);
    //int i;
    //for(i=0; hent->h_addr_list[i]; i++) {
    //    uint32_t u = ntohl(((struct in_addr*)hent->h_addr_list[i])->s_addr);
    //    std::cout << u << std::endl;
    //}
    return 0;
}

int main() {


    //10.94.45.25 
    //unsigned long ii = 0l;

    //ii |= 25;
    //ii |= 45 << 8;
    //ii |= 94 << 16;
    //ii |= 10 << 24;

    //cout << ii << endl;





    int ip;
    int ret = get_local_ip(ip);
    if (ret == 0) {
        cout << ip << endl;
    }
    else {
        cerr << "wrong" << endl;
    }
    return 0;
}