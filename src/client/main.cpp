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

int main()
{
    
    char server_Ip[40] = "";
    
   std::cout << "서버 IP : ";
   std::cin.getline(server_Ip, sizeof(server_Ip));
   
   int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   
   if(sock == -1)
   {
       return -1;
   }

   sockaddr_in servaddr = { 0 };
   
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = inet_addr(server_Ip);
   
  // PORT_NUM 상수 정의 필요
  servaddr.sin_port = htons(PORT_NUM); 

  int re = connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr));

  if(re == -1)
  {
      close(sock); //소켓 닫기
      return -1; 
  }
  
  char msg[MAX_MSG_LEN] ="";
  
 while(true)
 {
     std::cin.getline(msg, MAX_MSG_LEN); // gets_s 대신에 getline 사용
     send(sock,msg,sizeof(msg),0);
     
     if(strcmp(msg,"exit") ==0) 
     { 
         break; 
     }
     
     recv(sock,msg,sizeof(msg),0);
     
     std::cout << "수신 : " << msg << std::endl; 
 } 
 
 close(sock); //소켓 닫기
 
 return 0;

}
