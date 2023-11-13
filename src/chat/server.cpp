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
#include <vector>
#include <pthread.h>

#define MAX_MSG_LEN 256
#define PORT_NUM 10200
#define BLOG_SIZE 5
#define SERVER_IP "10.150.149.168" // 서버의 IP 주소로 변경해야 합니다.

std::vector<int> clients;
pthread_mutex_t clientsMutex = PTHREAD_MUTEX_INITIALIZER;

struct ThreadParams {
    int* clientSocket;
    int id;
};

void* ClientHandler(void* param);

int main() {
    int id = 63424;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating server socket");
        return -1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT_NUM);
    if (inet_pton(AF_INET, SERVER_IP, &(serverAddr.sin_addr)) <= 0) {
        perror("서버 IP 주소 오류");
        close(serverSocket);
        return -1;
    }

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("바인딩 오류");
        close(serverSocket);
        return -1;
    }

    if (listen(serverSocket, BLOG_SIZE) == -1) {
        perror("큐 오류");
        close(serverSocket);
        return -1;
    }

    std::cout << "서버 시작 :  " << PORT_NUM << std::endl;

    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == -1) {
            perror("클라이언트 수락 오류");
            continue;
        }

        ThreadParams params;
        params.clientSocket = &clientSocket;
        params.id = id;


        pthread_t thread;
        if (pthread_create(&thread, nullptr, ClientHandler, &params) != 0) {
            perror("클라이언트 생성 오류");
            close(clientSocket);
            continue;
        }

        {
            pthread_mutex_lock(&clientsMutex);
            clients.push_back(clientSocket);
            pthread_mutex_unlock(&clientsMutex);
        }
    }

    close(serverSocket);
    return 0;
}

void* ClientHandler(void* arg) {
    ThreadParams* params = (ThreadParams*)arg;

    int clientSocket = *(params->clientSocket);
    int id = params->id;
    char buffer[MAX_MSG_LEN] = "";
    int bytesReceived;

    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        pthread_mutex_lock(&clientsMutex);

        for (int& otherClient : clients) {
            if (otherClient != clientSocket) {
                send(otherClient, buffer, bytesReceived, 0);
            }
        }

        pthread_mutex_unlock(&clientsMutex);
    }

    pthread_mutex_lock(&clientsMutex);
    auto it = std::find(clients.begin(), clients.end(), clientSocket);
    if (it != clients.end()) {
        clients.erase(it);
    }
    pthread_mutex_unlock(&clientsMutex);

    std::cout << "클라이언트와의 연결이 끊겼습니다." << std::endl;
    close(clientSocket);
    pthread_exit(nullptr);
}
