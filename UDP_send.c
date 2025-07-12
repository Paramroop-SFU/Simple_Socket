#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/time.h>

void client(){

    //I need hostname,clientport,sending_data,destination
    struct timeval start, end;

    char hostname[] = {"207.23.164.108"};
    int clientport = 53444;
    char data[] = {"Hello UDP\n"};
    int dest = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in servaddr= {0};
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    char string_num[30];
    sprintf(string_num, "%d", clientport);
    int hostIP = getaddrinfo(hostname, string_num, &hints, &res);
    if (hostIP != 0)
    {
        perror("getaddrinfo() failed");
        exit(1);
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = ((struct sockaddr_in *)res->ai_addr)->sin_addr.s_addr;
    servaddr.sin_port = htons(clientport);
    freeaddrinfo(res);
    socklen_t len = sizeof(servaddr);
    char buffer[300] = {0};
    gettimeofday(&start, NULL);
    int message = sendto(dest, (const char *)data, strlen(data), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    if (message == -1){
    perror("failed to send");
    exit(1);
    }
    int n = recvfrom(dest, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&servaddr, &len);
    if (n == -1){
      perror("recvfrom() failed");
      exit(1);
    }
    gettimeofday(&end, NULL);
    double time_spent = (end.tv_sec - start.tv_sec) * 1000.0; 
    time_spent += (end.tv_usec - start.tv_usec) / 1000.0;     
    printf("UDP Time taken is %.3f ms\n", time_spent);

    printf("%s",buffer);
}

int main(){
    
    client();
    return 0;
}