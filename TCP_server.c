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

void sendTCP(){
    int userport = 53333;
    int dest = socket(AF_INET, SOCK_STREAM, 0);
    char hostname[] = {"142.58.10.205"};
    char string_num[10];
    sprintf(string_num, "%d", userport);
    char data[] = {"Hello TCP\n"};
    char buffer[300] = {0};

    struct sockaddr_in servaddr, client_addr = {0};
    socklen_t addr_len = sizeof(client_addr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(userport);

    if (bind(dest, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
    perror("bind() failed");
    return;
}
printf("Bind successful\n");

if (listen(dest, 5) < 0) {
    perror("listen failed");
    return;
}
printf("Server ready and listening on port 53333\n");

    printf("Server ready\n");

    int client_accept = accept(dest,(struct sockaddr*)&client_addr, &addr_len);
if (client_accept < 0) {
    perror("accept failed");
    return;
}
printf("Client connected!\n");

    read(client_accept,buffer,sizeof(buffer));
    printf("%s\n",buffer);
    char message[] = {"Back to you TCP\n"};
    send(client_accept,message,sizeof(message),0);
    close(client_accept);
    close(dest);


}

int main(){
    sendTCP();
    return 0;
}