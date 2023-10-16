#include <iostream>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

struct in_addr GetDefaultMyIP();

int main()
{
    struct in_addr addr;

    GetDefaultMyIP();

    return 0;
}

struct in_addr GetDefaultMyIP()
{
    char localhostname[sysconf(_SC_HOST_NAME_MAX)];
    struct in_addr addr;
    addr.s_addr = INADDR_NONE;

    if(gethostname(localhostname, sysconf(_SC_HOST_NAME_MAX)) == -1) 
        return addr;

    struct hostent* ptr = gethostbyname(localhostname);
        
    int i = 0;
    while(ptr && ptr->h_addr_list[i] != NULL) {
        if(ptr && ptr->h_name && ptr->h_addrtype == AF_INET) {
            struct in_addr addr;
            memcpy(&addr, ptr->h_addr_list[i], ptr->h_length);
            std::cout << inet_ntoa(addr) << std::endl;
            i++;
        }
    }

    return addr;
}
