#ifdef _WIN32
    #define INVALID_SOCKET (SOCKET)(~0)
    #define SOCKET_ERROR -1
#endif
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

#define MAX_PATH 300
#define MAX_MSG_LEN 256
#define PORT_NUM 10200
#define BLOG_SIZE 5