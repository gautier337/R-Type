/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "../include/Client.hpp"
#include <iostream>
#include <string>

#include "../include/Client.hpp"
#include <iostream>
#include <string>

void showHelp() {
    std::cout << "Usage: r-type_client [server_address] [-p port]\n"
              << "Options:\n"
              << "  -h, -help           Afficher ce message d'aide.\n"
              << "  -p port             Spécifier le port du serveur (par défaut: 8000).\n"
              << "Arguments:\n"
              << "  server_address      Adresse IP du serveur (par défaut: 127.0.0.1).\n"
              << std::endl;
}

int main(int argc, char* argv[])
{
    std::string server_address = "127.0.0.1";
    int server_port = 8000;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "-help") {
            showHelp();
            return 0;
        } else if (arg == "-p" && i + 1 < argc) {
            server_port = std::stoi(argv[++i]);
        } else {
            server_address = argv[i];
        }
    }

    Client client = Client(server_address.c_str(), server_port);
    std::cout << "Client class initiated with server IP: " << server_address
              << " and port: " << server_port << std::endl;

    client.init();
    client.run();
    return int(client.getStatus());
}
