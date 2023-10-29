#include <iostream>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <netdb.h>

// macOS에는 WinSock이 없어 struct를 사용하지 않아도 연결할 수 있어요

int main()
{
    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) == -1) {
        std::cerr << "Failed to get network interface information" << std::endl;
        return 1;
    }

    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr)
            continue;

        int family = ifa->ifa_addr->sa_family;
        if (family == AF_INET || family == AF_INET6) {
            std::cout << "Interface: " << ifa->ifa_name << std::endl;

            char host[NI_MAXHOST];
            int ret = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in),
                                  host, NI_MAXHOST, nullptr, 0, NI_NUMERICHOST);
            if (ret != 0) {
                std::cerr << "Failed to get IP address" << std::endl;
                continue;
            }

            std::cout << "IP Address: " << host << std::endl;
        }
    }

    freeifaddrs(ifaddr);

    return 0;
}
