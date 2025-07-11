#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/types.h>
#include <arpa/inet.h>

void recieve(){
    int port = 53333;
    int dest = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr = {0};
    char buffer[300];
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    if (inet_pton(AF_INET, "142.58.10.205", &servaddr.sin_addr) <= 0) {
        perror("Invalid addres");
    }
    if (connect(dest, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Connection Failed");
    }
    char mess[] = "hello TCP";

    send(dest,mess,sizeof(mess),0);
    read(dest,buffer,sizeof(buffer));
    printf("%s\n",buffer);
    close(dest);

}

int main(){
    recieve();
    return 0; 
}