#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <asio.hpp>

const int serverPort = 8000;

std::vector<std::shared_ptr<asio::ip::tcp::socket>> clients;
std::mutex clients_mutex;

void broadcast_message(const std::string& message) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    for (auto& client : clients) {
        asio::async_write(*client, asio::buffer(message),
            [](const asio::error_code& error, std::size_t) {
                if (error) {
                    // Handle send error
                }
            }
        );
    }
}

void start_read(std::shared_ptr<asio::ip::tcp::socket> socket) {
    auto buffer = std::make_shared<std::vector<char>>(1024);
    socket->async_read_some(asio::buffer(*buffer), [socket, buffer](const asio::error_code& error, std::size_t length) {
        if (!error) {
            std::string message(buffer->begin(), buffer->begin() + length);
            std::cout << "Received: " << message << std::endl;

            start_read(socket);
        } else {
            // Handle disconnection or errors
        }
    });
}

void start_accept(asio::ip::tcp::acceptor& acceptor, asio::io_context& io_context) {
    auto socket = std::make_shared<asio::ip::tcp::socket>(io_context);
    acceptor.async_accept(*socket, [&acceptor, &io_context, socket](const asio::error_code& error) {
        if (!error) {
            std::cout << "New client connected" << std::endl;

            {
                std::lock_guard<std::mutex> lock(clients_mutex);
                clients.push_back(socket);
            }

            broadcast_message("Welcome to R-Type Server!");

            start_read(socket);
            start_accept(acceptor, io_context);
        } else {
            // Handle error
        }
    });
}

int main() {
    try {
        std::cout << "R-Type Server Starting on port " << serverPort << std::endl;

        asio::io_context io_context;
        asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), serverPort);
        asio::ip::tcp::acceptor acceptor(io_context, endpoint);

        start_accept(acceptor, io_context);

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
