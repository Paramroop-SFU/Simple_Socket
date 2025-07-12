#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
void client(){
    struct timeval start, end;
    int port = 53333;
    int dest = socket(AF_INET, SOCK_STREAM, 0);
    if (dest < 0) {
        perror("Socket creation failed");
        return;
    }
    struct sockaddr_in servaddr = {0};
    char buffer[300] = {0};
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    printf("L\n");
    fflush(stdout);

    // CHANGE THIS TO THE SERVER MACHINE'S ACTUAL LAN IP
    if (inet_pton(AF_INET, "207.23.164.108", &servaddr.sin_addr) <= 0) {
        perror("Invalid address");
        close(dest);
        return;
    }

    if (connect(dest, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Connection Failed");
        close(dest);
        return;
    }
    printf("Connected to server\n");
    fflush(stdout);

    char mess[] = "hello TCP";
    printf("ready to send\n");
    fflush(stdout);
    gettimeofday(&start, NULL);
    ssize_t sent = send(dest, mess, sizeof(mess), 0);


    ssize_t received = read(dest, buffer, sizeof(buffer) - 1);
    gettimeofday(&end, NULL);
    double time_spent = (end.tv_sec - start.tv_sec) * 1000.0; // sec to ms
    time_spent += (end.tv_usec - start.tv_usec) / 1000.0;     // us to ms

    printf("Time taken is %.3f ms\n", time_spent);
    
    if (received < 0) {
        perror("Read failed");
    } else {
        buffer[received] = '\0';  // Null-terminate string
        printf("Received: %s\n", buffer);
    }
    close(dest);
}
int main(){
    client();
    return 0; 
}
