#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 65432
#define BUFFER_SIZE 1024

int main() {
int client_fd;
struct sockaddr_in server_addr;
char buffer[BUFFER_SIZE];

// Create socket
client_fd = socket(AF_INET, SOCK_STREAM, 0);

// Set server address
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

// Connect to server
connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Connected to server.\n");

// Communicate with the server
while (1) {
printf("Enter message (type 'exit' to quit): ");
fgets(buffer, BUFFER_SIZE, stdin);
buffer[strcspn(buffer, "\n")] = 0; // Remove newline

if (strcmp(buffer, "exit") == 0) break;

send(client_fd, buffer, strlen(buffer), 0);
memset(buffer, 0, BUFFER_SIZE);
recv(client_fd, buffer, BUFFER_SIZE, 0);
printf("Server: %s\n", buffer);
}

// Close connection
close(client_fd);

return 0;
}
