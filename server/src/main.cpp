#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <asio.hpp>
#include "server.hpp"
#include <fstream>

void printHelpMessage()
{
    std::cout << "Usage: [option]...\n"
              << "Options:\n"
              << "  --serverPort <port>    Definit le port du serveur (par défaut 8000).\n"
              << "  --wave <number>        Definit la vague de jeu (doit être entre 1 et 10).\n"
              << "  --solo                 Active le mode solo.\n"
              << "  -h, --help             Affiche ce message d'aide.\n";
}

int main(int argc, char* argv[])
{
    int serverPort = 8000;
    int wave = 1;
    bool solo = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            printHelpMessage();
            return 0;
        } else if (arg == "--serverPort" && i + 1 < argc) {
            serverPort = std::stoi(argv[++i]);
        } else if (arg == "--solo") {
            solo = true;
        } else if (arg == "--wave" && i + 1 < argc) {
            wave = std::stoi(argv[++i]);

            if (wave < 1 || wave > 10) {
                std::cerr << "Wave doit être entre 1 et 10." << std::endl;
                return 1;
            }
        }
    }

    try {
        asio::io_context io_context;
        Server server(io_context, serverPort, wave, solo);

        std::vector<std::thread> threads;
        for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
            threads.emplace_back([&io_context]() {
                try {
                    io_context.run();
                } catch (std::exception& e) {
                    std::cerr << "Exception: " << e.what() << "\n";

                    std::ofstream logFile("log.txt", std::ios::app);
                    if (logFile.is_open()) {
                        logFile << "Exception in thread: " << e.what() << "\n";
                        logFile.close();
                    } else {
                        std::cerr << "Unable to open log file.\n";
                    }
                }
            });
        }

        for (auto& t : threads) {
            t.join();
        }

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
