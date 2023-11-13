#include "common.h"

int main()
{
    SOCKET sock_base[FD_SETSIZE];
    HANDLE hev_base[FD_SETSIZE];

    HANDLE hev = WSACreateEvent();
    WSAEventSelect(sock, hev, net_event);

    int index = WSAWaitForMultipleEvents(cnt, hev_base, false, INFINITE, false);
    WSANETWORKEVENTS net_events;
    WSAEnumNetworkEvents(sock_base[index], hev_base[index], &net_events);
    switch(net_events.INetworkEvents)

    closesocket(sock_base[index]);
    WSACloseEvent(hev_base[index]);
}