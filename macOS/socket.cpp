#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cerr << "Failed to create a socket" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Socket created successfully" << endl;

    if (close(sockfd) == -1) {
        cerr << "Failed to close the socket" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Socket closed successfully" << endl;

    return 0;
}
