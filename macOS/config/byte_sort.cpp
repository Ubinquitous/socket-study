#include <iostream>
#include <arpa/inet.h>

using namespace std;

int main()
{
    unsigned int idata = 0x12345678;
    unsigned short sdata = 0x1234;

    // htonl => host to network (long type)
    // 4바이트 정수를 네트워크 바이트 정렬로 변환 후 출력
    cout << "host : " << idata << " " << "network : " << htonl(idata) << std::endl;
    
    // htons => host to network (short type)
    // 2바이트 정수를 네트워크 바이트 정렬로 변환 후 출력
    cout << "host : " << sdata << " " << "network : " << htons(sdata) << std::endl;

    return 0;
}