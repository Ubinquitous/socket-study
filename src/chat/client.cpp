#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <sstream>
#include <random>

int getRandomPort() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(60000, 64000);

    return dis(gen);
}

#define MAX_MSG_LEN 256
#define SERVER_IP "10.150.149.168" // 서버의 IP 주소로 변경해야 합니다.

void* ReceiveThread(void* param);

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("소켓 생성 오류");
        return -1;
    }
    int PORT_NUM = 10200;

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT_NUM);
    if (inet_pton(AF_INET, SERVER_IP, &(serverAddr.sin_addr)) <= 0) {
        perror("서버 주소가 잘못되었음");
        close(clientSocket);
        return -1;
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("클라이언트 연결 실패");
        close(clientSocket);
        return -1;
    }

    pthread_t thread;
    if (pthread_create(&thread, nullptr, ReceiveThread, (void*)&clientSocket) != 0) {
        perror("클라이언트 생성 실패");
        close(clientSocket);
        return -1;
    }

    printf("연결 성공!\n");
    char msg[MAX_MSG_LEN] = "";

    while (true) {
        std::cin.getline(msg, MAX_MSG_LEN);
        send(clientSocket, msg, strlen(msg) + 1, 0); // 버퍼의 크기를 strlen(msg) + 1로 변경

        if (strcmp(msg, "exit") == 0) {
            break;
        }
    }

    pthread_cancel(thread);
    pthread_join(thread, nullptr);

    send(clientSocket, "님이 나갔습니다. ", 50, 0);
    close(clientSocket);
    return 0;
}

void* ReceiveThread(void* param) {
    int socket = *((int*)param);
    char buffer[MAX_MSG_LEN] = "";
    int bytesReceived;

    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    if (getpeername(socket, (struct sockaddr*)&clientAddr, &clientAddrLen) == -1) {
        std::cerr << "getpeername() failed" << std::endl;
        return nullptr;
    }

    while ((bytesReceived = recv(socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0'; // 추가: 버퍼를 null로 종료
        std::cout << "[" << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << "] " << buffer << std::endl;
        memset(buffer, 0, sizeof(buffer)); // 추가: 버퍼를 비움
    }

    std::cout << "서버와의 연결이 끊겼습니다." << std::endl;
    close(socket);
    pthread_exit(nullptr);
}

