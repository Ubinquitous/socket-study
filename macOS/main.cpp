#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Failed to create a socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Socket created successfully" << std::endl;

    if (close(sockfd) == -1) {
        std::cerr << "Failed to close the socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Socket closed successfully" << std::endl;

    return 0;
}
