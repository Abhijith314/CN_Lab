#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 65432
#define BUFFER_SIZE 1024
int main() {
int server_fd, client_fd;
struct sockaddr_in server_addr, client_addr;
char buffer[BUFFER_SIZE];
socklen_t addr_len = sizeof(client_addr);

// Create socket
server_fd = socket(AF_INET, SOCK_STREAM, 0);

// Set server address and bind
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = INADDR_ANY;
server_addr.sin_port = htons(PORT);
bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

// Listen for a connection
listen(server_fd, 1);
printf("Server is listening on port %d...\n", PORT);

// Accept a client connection
client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    printf("Client connected.\n");

// Communicate with the client
while (1) {
memset(buffer, 0, BUFFER_SIZE);
int bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
if (bytes_received <= 0) break;

printf("Client: %s\n", buffer);
send(client_fd, buffer, strlen(buffer), 0); // Echo back
}

// Close connections
close(client_fd);
close(server_fd);

return 0;
}
