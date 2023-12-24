#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <asio.hpp>
#include "server.hpp"
#include <fstream>

const int serverPort = 8000;

int main()
{
    try {
        std::cout << "R-Type Server Starting on port " << serverPort << std::endl;

        asio::io_context io_context;
        Server server(io_context, serverPort);

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
