#include "common.h"
#include <thread>

void ReceiveThread(SOCKET socket);

int main() {
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating client socket" << std::endl;
        return -1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(PORT_NUM);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server" << std::endl;
        closesocket(clientSocket);
        return -1;
    }

    // 클라이언트 쓰레드 시작
    std::thread(ReceiveThread, clientSocket).detach();

    char msg[MAX_MSG_LEN] = "";

    while (true) {
        std::cin.getline(msg, MAX_MSG_LEN);
        send(clientSocket, msg, sizeof(msg), 0);

        if (strcmp(msg, "exit") == 0) {
            break;
        }
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}

void ReceiveThread(SOCKET socket) {
    char buffer[MAX_MSG_LEN] = "";
    int bytesReceived;

    while ((bytesReceived = recv(socket, buffer, sizeof(buffer), 0)) > 0) {
        std::cout << "수신 : " << buffer << std::endl;
    }

    std::cout << "서버와의 연결이 끊겼습니다." << std::endl;
    closesocket(socket);
    exit(0);
}
