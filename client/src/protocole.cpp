#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

void send_message_to_server(int sock, const char* server_address, int server_port, const char* message, char* buffer, size_t buffer_size)
{
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_address, &server_addr.sin_addr);

    sendto(sock, message, strlen(message), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    socklen_t addrlen = sizeof(server_addr);
    recvfrom(sock, buffer, buffer_size, 0, (struct sockaddr *)&server_addr, &addrlen);
}

int parse_client_id(const char* response) {
    try {
        std::string resp(response);
        size_t comma_pos = resp.find(',');
        if (comma_pos != std::string::npos) {
            return std::stoi(resp.substr(0, comma_pos));
        }
        throw std::invalid_argument("No comma found in response");
    } catch (std::exception &e) {
        std::cerr << "Erreur lors du parsing de l'ID: " << e.what() << ", response=" << response << std::endl;
        exit(1);
    }
}

int main() {
    const char* server_address = "127.0.0.1";
    int server_port = 8000;
    int client_id = 1;
    const size_t buffer_size = 4096;
    char buffer[buffer_size];

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "Erreur lors de la création du socket" << std::endl;
        return 1;
    }
    std::cout << "Client " << client_id << ": Connexion au serveur" << std::endl;
    send_message_to_server(sock, server_address, server_port, "START", buffer, buffer_size);
    std::cout << "Client " << client_id << ": Reçu '" << buffer << "' du serveur" << std::endl;
    int server_client_id = parse_client_id(buffer);
    std::cout << "Client " << client_id << ": Reçu ID '" << server_client_id << "' du serveur" << std::endl;
    send_message_to_server(sock, server_address, server_port, "QUIT", buffer, buffer_size);
    std::cout << "Client " << client_id << ": Envoi de la commande 'QUIT'" << std::endl;
    close(sock);
    std::cout << "Test terminé." << std::endl;
    return 0;
}
