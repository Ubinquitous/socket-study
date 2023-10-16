#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

unsigned long inet_addr(const char* cip);
char *inet_ntoa(struct in_addr in);

typedef struct in_addr {
    union {
        struct { UCHAR s_b1, s_b2, s_b3, s_b4; } S_un_b;
        struct { USHORT s_w1, s_w2; } S_un_w;
        ULONG S_addr;
    } S_un;
#define s_addr      S_un.S_addr
#define s_host      S_un.S_un_b.s_b2
#define s_net       S_un.S_un_b.s_b1
#define s_imp       S_un.S_un_w.s_w2
#define s_impno     S_un.S_un_b.s_b4
#define s_lh        S_un.S_un_b.s_b3
} IN_ADDR, * PIN_ADDR, FAR* LPIN_ADDR;

int main()
{
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);

    IN_ADDR addr;
    addr.s_addr = htonl(12 << 24 | 34 << 16 | 56 << 8 | 78);
    cout << inet_ntoa(addr) << "\n";

    u_int naddr = inet_addr("192.168.34.0");
    u_int haddr = ntohl(naddr);
    cout << (haddr>>24) << "." << (u_char)(haddr>>16) << "." << (u_char)(haddr>>8) << "." << (u_char)(haddr);

    WSACleanup();
}