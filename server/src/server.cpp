#include "server.hpp"
#include <iostream>

Server::Server(asio::io_context& io_context, int port)
    : acceptor_(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
    start_accept();
}

void Server::broadcast_message(const std::string& message) {
    std::lock_guard<std::mutex> lock(clients_mutex_);
    for (auto& client : clients_) {
        client->sendMessage(message);
    }
}

void Server::start_accept()
{
    auto socket = std::make_shared<asio::ip::tcp::socket>(acceptor_.get_io_context());
    acceptor_.async_accept(*socket, [this, socket](const asio::error_code& error) {
        if (!error) {
            std::cout << "New client connected" << std::endl;
            auto client = std::make_shared<Client>(socket);
            {
                std::lock_guard<std::mutex> lock(clients_mutex_);
                clients_.push_back(client);
            }
            client->sendMessage("Welcome to R-Type Server!");
            start_read(client);
            start_accept();
        } else {
            std::cerr << "Accept error: " << error.message() << std::endl;
        }
    });
}

void Server::start_read(std::shared_ptr<Client> client)
{
    auto buffer = std::make_shared<std::vector<char>>(1024);
    const auto& socket = client->getSocket();

    socket->async_read_some(asio::buffer(*buffer), [this, client, buffer](const asio::error_code& error, std::size_t length) {
        if (!error) {
            std::string message(buffer->begin(), buffer->begin() + length);
            std::cout << "Received: " << message << std::endl;

            start_read(client);
        } else {
            std::cerr << "Read error: " << error.message() << std::endl;
        }
    });
}

