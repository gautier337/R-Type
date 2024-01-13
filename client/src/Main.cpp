/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "../include/Client.hpp"

void showHelp() {
    std::cout << "Usage: r-type_client [--ip server_address] [-p port]\n"
              << "Options:\n"
              << "  -h, -help           Show this help message.\n"
              << "  --ip server_address Specify server IP address (default: 127.0.0.1).\n"
              << "  -p port             Specify server port (default: 8000).\n"
              << std::endl;
}

static bool isValidIpAddress(const std::string &ipAddress) {
    // Regular expression for validating an IP address
    std::regex ipFormat("^(\\d{1,3})(\\.\\d{1,3}){3}$");
    
    // Check if the IP address matches the regular expression
    if (std::regex_match(ipAddress, ipFormat)) {
        std::istringstream iss(ipAddress);
        std::string byte;
        
        while (std::getline(iss, byte, '.')) {
            int num = std::stoi(byte);
            if (num < 0 || num > 255) {
                return false;
            }
        }
        return true;
    }
    return false;
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
        } else if (arg.substr(0, 4) == "--ip" && i + 1 < argc) {
            server_address = argv[++i];
            if (!isValidIpAddress(server_address)) {
                std::cerr << "Invalid IP address: " << server_address << std::endl;
                return 1;
            }
        } else if (arg.substr(0, 2) == "-p" && i + 1 < argc) {
            server_port = std::stoi(argv[++i]);
        } else {
            std::cerr << "Invalid argument: " << arg << std::endl;
            return 1;
        }
    }

    Client client = Client(server_address.c_str(), server_port);
    std::cout << "Client class initiated with server IP: " << server_address
              << " and port: " << server_port << std::endl;

    client.init();
    client.run();
    return int(client.getStatus());
}
