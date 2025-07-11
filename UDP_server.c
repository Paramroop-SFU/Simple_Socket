#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/types.h>


void receive(){
    int userport = 53444;
    int dest = socket(AF_INET, SOCK_DGRAM, 0);
    char hostname[] = {"142.58.10.205"};
    
   

    struct sockaddr_in servaddr = {0};
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(userport);

    if(bind(dest, (const struct sockaddr *)&servaddr, sizeof(servaddr)))
    {
        perror("bind() failed");
        close(dest);
        exit(1);
    }
    socklen_t len = sizeof(servaddr);
    char buffer[300] = {0}; // buffer for the information
  
    // grab the information from the user
  
    int n = recvfrom(dest, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&servaddr, &len);
    if (n == -1){
      perror("recvfrom() failed");
      exit(1);
    }
    printf("%s",buffer);
    char data[] = {"Back to You UDP\n"};
    int message = sendto(dest, (const char *)data, strlen(data), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    if (message == -1){
    perror("failed to send");
    exit(1);
    }
    
}

int main(){
    receive();
    return 0;
}