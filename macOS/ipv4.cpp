#include <iostream>
#include <arpa/inet.h>

using namespace std;

int main()
{
    struct in_addr addr;
    addr.s_addr = htonl(12 << 24 | 34 << 16 | 56 << 8 | 78);
    cout << inet_ntoa(addr);

    in_addr_t naddr = inet_addr("192.168.34.0");
    uint32_t haddr = ntohl(naddr);
    
    cout 
        << ((haddr>>24) & 0xFF) 
        << "." 
        << ((haddr>>16) & 0xFF)
        << "." 
        << ((haddr>>8) & 0xFF)
        <<"." 
        << (haddr & 0xFF);

    return 0;
}
