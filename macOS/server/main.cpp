#include "common.h"

struct in_addr GetDefaultMyIP()
{
    char localhostname[MAX_PATH];
    struct in_addr addr;
    memset(&addr, 0, sizeof(addr));

    if(gethostname(localhostname, MAX_PATH) == -1)
    {
        return addr;
    }

    struct hostent* ptr = gethostbyname(localhostname);
    
    while (ptr)
    {
        if(ptr->h_addrtype == AF_INET)
        {
            memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);
            break;
        }
        
        ptr++;
    }

   return addr;
}

int SetTCPServer(short pnum, int blog)
{
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock == -1)
    {
        return -1;
    }
    
    struct sockaddr_in servaddr = { 0 };
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr = GetDefaultMyIP();
    servaddr.sin_port = htons(PORT_NUM);
    
    int re = bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));
    
    if(re == -1)
    {
        close(sock);
        return -1;
    }

     re = listen(sock, blog);

     if (re == -1)
     {
         close(sock);
         return -1;
     }
     
     std::cout << inet_ntoa(servaddr.sin_addr) << " : " << pnum << " SetUp" << std::endl;

     return sock;
}


void Dolt(int dosock)
{
    char msg[MAX_MSG_LEN] = "";
    while(recv(dosock, msg, sizeof(msg), 0) > 0)
    {
        std::cout << "recv : " << msg << std::endl;
        send(dosock, msg, sizeof(msg), 0);
    }
    close(dosock);
}

void AcceptLoop(int sock)
{
    int dosock;
    struct sockaddr_in cliaddr = { 0 };
    socklen_t len = sizeof(cliaddr);

    while(true)
    {
        dosock = accept(sock, (struct sockaddr *)&cliaddr, &len);

        if(dosock == -1)
        {
            perror("Accept 실패");
            break;
        }
        
        std::cout << inet_ntoa(cliaddr.sin_addr) << " : " << ntohs(cliaddr.sin_port) << "의 연결 요청 수락" 
                  << std::endl;

        Dolt(dosock);
    }
    
   close(sock);
}

int main()
{
   int sock = SetTCPServer(PORT_NUM, BLOG_SIZE);
   
   if(sock == -1)
   {
       perror("대기 소켓 오류");
       return 0;
   }

   AcceptLoop(sock);

   return 0;
}
