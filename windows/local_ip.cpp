#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32")

IN_ADDR GetDefaultMyIP();
int main()
{
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    IN_ADDR addr;

    addr = GetDefaultMyIP();
    cout << inte_ntoa(addr) << "\n";

    WSACleanup();
    return 0;
}

IN_ADDR GetDefaultMyIP()
{
    char localhostname[MAX_PATH];
    IN_ADDR addr = { 0, };

    if(gethostname(localhostname, MAX_PATH) == SOCKET_ERROR) 
    {
        return addr;
    }
    HOSTENT* ptr = gethostbyname(localhostname);

    while(ptr && ptr->h_name)
    {
        if(ptr -> h_addrtype == PF_INET)
        {
            memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);
            break;
        }
        ptr++;
    }
    return addr;
}