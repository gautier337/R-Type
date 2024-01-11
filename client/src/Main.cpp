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
    std::cout << "Usage: r-type_client [server_address] [-p port] [--wave=number]\n"
              << "Options:\n"
              << "  -h, -help           Show this help message.\n"
              << "  -p port             Specify server port (default: 8000).\n"
              << "  --wave=number       Choose a wave from 1 to 10.\n"
              << "Arguments:\n"
              << "  server_address      Server IP address (default: 127.0.0.1).\n"
              << std::endl;
}

int main(int argc, char* argv[])
{
    std::string server_address = "127.0.0.1";
    int server_port = 8000;
    int wave_number = 1;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "-help") {
            showHelp();
            return 0;
        } else if (arg == "-p" && i + 1 < argc) {
            server_port = std::stoi(argv[++i]);
        } else if (arg.substr(0, 7) == "--wave=") {
            wave_number = std::stoi(arg.substr(7));
            if (wave_number < 1 || wave_number > 10) {
                std::cerr << "Invalid wave number. Please choose a wave from 1 to 10." << std::endl;
                return 1;
            }
        } else {
            server_address = argv[i];
        }
    }

    Client client = Client(server_address.c_str(), server_port);
    std::cout << "Client class initiated with server IP: " << server_address
              << " and port: " << server_port << std::endl;

    client.init();
    client.wave = wave_number;
    client.run();
    return int(client.getStatus());
}
