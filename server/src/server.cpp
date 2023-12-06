#include "server.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <thread>

Server::Server(asio::io_context& io_context, int port)
    : socket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)),
      tick_timer_(io_context, std::chrono::seconds(3)) {
    start_receive();
    handle_tick({});
}

void Server::start_receive() {
    auto buffer = std::make_shared<std::array<char, 1024>>();
    auto endpoint = std::make_shared<asio::ip::udp::endpoint>();

    socket_.async_receive_from(
        asio::buffer(*buffer), *endpoint,
        [this, buffer, endpoint](const asio::error_code& error, std::size_t bytes_recvd) {
            if (!error && bytes_recvd > 0) {
                std::string message(buffer->begin(), buffer->begin() + bytes_recvd);
                handle_receive(message, *endpoint);
                start_receive();
            } else {
                std::cerr << "Receive error: " << error.message() << std::endl;
                start_receive();
            }
        }
    );
}

void Server::handle_receive(const std::string& data, const asio::ip::udp::endpoint& endpoint) {
    std::cout << "Received message: " << data << " from " << endpoint << std::endl;
    std::cout << "handle_receive called from thread: " << std::this_thread::get_id() << std::endl;

    bool isNewClient = false;
    int clientId;
    {
        std::lock_guard<std::mutex> lock(clients_mutex_);
        if (client_ids_.find(endpoint) == client_ids_.end() || data == "START") {
            clientId = client_id_counter_++;
            number_of_player_connected_++;
            client_ids_[endpoint] = clientId;
            isNewClient = true;
            std::cout << "New client added with ID: " << clientId << std::endl;
        } else {
            clientId = client_ids_[endpoint];
        }
    }

    if (isNewClient) {
        std::string welcomeMessage = std::to_string(clientId) + ", Bienvenue !";
        handle_send(welcomeMessage, endpoint);
        return;
    }

    if (data == "QUIT") {
        std::lock_guard<std::mutex> lock(clients_mutex_);
        client_ids_.erase(endpoint);
        handle_send("Goodbye", endpoint);
            number_of_player_connected_--;
        std::cout << "Client " << clientId << " disconnected, clients left: " << number_of_player_connected_ << std::endl;
    } else {
        handle_send("Received message: " + data, endpoint);   
    }
}

void Server::handle_send(const std::string& message, const asio::ip::udp::endpoint& endpoint)
{
    auto message_data = std::make_shared<std::string>(message);
    std::cout << "handle_send called from thread: " << std::this_thread::get_id() << std::endl;

    socket_.async_send_to(
        asio::buffer(*message_data), endpoint,
        [this, message_data](const asio::error_code& error, std::size_t /*bytes_sent*/) {
            if (error) {
                std::cerr << "Send error: " << error.message() << std::endl;
            } else {
                std::cout << "Sent message: " << *message_data << std::endl;
            }
        }
    );
}

void Server::handle_tick(const asio::error_code& error)
{
    if (!error) {
        tick++;
        // std::cout << "Tick: " << tick << std::endl;

        tick_timer_.expires_at(tick_timer_.expiry() + std::chrono::seconds(1));
        tick_timer_.async_wait(std::bind(&Server::handle_tick, this, std::placeholders::_1));
    } else {
        std::cerr << "Tick timer error: " << error.message() << std::endl;
    }
}
