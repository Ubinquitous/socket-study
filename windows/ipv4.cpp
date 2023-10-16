#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

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