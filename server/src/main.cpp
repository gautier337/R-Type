#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <asio.hpp>
#include "client.hpp"
#include "server.hpp"

const int serverPort = 8000;

int main()
{
    try {
        std::cout << "R-Type Server Starting..." << std::endl;

        asio::io_context io_context;
        Server server(io_context, serverPort);

        std::vector<std::thread> threads;
        for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
            threads.emplace_back([&io_context]() {
                io_context.run();
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
