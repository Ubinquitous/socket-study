#include <iostream>
#include <arpa/inet.h>

using namespace std;

int main()
{
    struct in_addr addr;
    // 12.34.56.78
    addr.s_addr = htonl(12 << 24 | 34 << 16 | 56 << 8 | 78);

    // IPv4 주소를 문자열로 변환
    cout << inet_ntoa(addr);

    // 문자열을 IPv4 주소로 변환
    in_addr_t naddr = inet_addr("192.168.34.0");

    // 호스트 방식 바이트 정렬로 변환
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
