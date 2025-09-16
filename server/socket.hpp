#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")  // Link Winsock library

// Function to handle client data
void handle_client(const char* data, int len,
                   const char* ip, int port) {
    std::cout << "Client " << ip << ":" << port
              << " sent: " << std::string(data, len) << std::endl;
}

int main() {
    WSADATA wsaData;
    SOCKET server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    int client_len = sizeof(client_addr);

    // 1. Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed, error: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // 2. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        std::cerr << "Socket failed, error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // 3. Set socket options (reuse addr/port)
    BOOL opt = TRUE;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                   (char*)&opt, sizeof(opt)) == SOCKET_ERROR) {
        std::cerr << "setsockopt failed, error: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // 4. Bind to port 8080
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
    server_addr.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&server_addr,
             sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed, error: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // 5. Listen
    if (listen(server_fd, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed, error: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on port 8080..." << std::endl;

    // 6. Accept loop
    while (true) {
        client_fd = accept(server_fd,
                           (struct sockaddr*)&client_addr,
                           &client_len);
        if (client_fd == INVALID_SOCKET) {
            std::cerr << "Accept failed, error: " << WSAGetLastError() << std::endl;
            continue;
        }

        // Convert client IP + port
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_addr.sin_addr),
                  client_ip, sizeof(client_ip));
        int client_port = ntohs(client_addr.sin_port);

        // Read data
        char buffer[1024] = {0};
        int valread = recv(client_fd, buffer, sizeof(buffer), 0);
        if (valread > 0) {
            // Pass to handler
            handle_client(buffer, valread, client_ip, client_port);

            // Echo back
            send(client_fd, buffer, valread, 0);
        }

        closesocket(client_fd); // Close this client
    }

    // Cleanup
    closesocket(server_fd);
    WSACleanup();
    return 0;
}
