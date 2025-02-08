// Client side C program to demonstrate interactive Socket programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[]) {
    int client_fd;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nSocket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "10.1.124.108", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/Address not supported\n");
        return -1;
    }

    if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection failed\n");
        return -1;
    }

    printf("Connected to the server.\n");

    while (1) {
        printf("Enter your message: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline
        send(client_fd, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "bye") == 0) {
            printf("Chat ended by client.\n");
            break;
        }

        memset(buffer, 0, sizeof(buffer));
        read(client_fd, buffer, sizeof(buffer) - 1);
        printf("Server: %s\n", buffer);

        if (strcmp(buffer, "bye") == 0) {
            printf("Chat ended by server.\n");
            break;
        }
    }

    close(client_fd);
    return 0;
}

