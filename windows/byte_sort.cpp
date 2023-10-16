#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32")

int main()
{
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);

    unsigned int idata = 0x12345678;
    unsigned short sdata = 0x1234;

    cout << "host : " << idata << " " << "network : " << htonl(idata) << "\n";
    cout << "host : " << sdata << " " << "network : " << htons(sdata) << "\n";

    WSACleanup();
    return 0;
}