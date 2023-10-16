#include <iostream>
#include <arpa/inet.h>

using namespace std;

int main()
{
    unsigned int idata = 0x12345678;
    unsigned short sdata = 0x1234;

    cout << "host : " << idata << " " << "network : " << htonl(idata) << std::endl;
    cout << "host : " << sdata << " " << "network : " << htons(sdata) << std::endl;

    return 0;
}