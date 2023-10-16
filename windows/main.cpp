#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32")

int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
int WSACleanup(void);

typedef struct WSAData {
    WORD            sVersion;
    WORD            wHighVersion;
    char            szDescription[WSADESCRIPTION_LEN + 1];
    char            szSystemStatus[WSASYS_STATUS_LEN + 1];
    unsigned short  iMaxSockets;
    unsigned short iMaxUdpDg;
    char FAR* IpVendorInfo;
} WSADATA, FAR* LPWSADATA;

using namespace std;

int main()
{
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);

    cout << "wHighVersion : " << wsadata.wHighVersion << "\n";
    cout << "wVersion : " << wsadata.wVersion << "\n";
    cout << "szDescription : " << wsadata.szDescription << "\n";
    cout << "szSystemStatus : " << wsadata.szSystemStatus << "\n";

    cout << "iMaxSocket : " << wsadata.iMaxSockets << "\n";
    cout << "iMaxUdpDg : " << wsadata.iMaxUdpDg << "\n";

    WSACleanup();
    return 0;
}
